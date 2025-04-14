#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

//преобразования массива PostgreSQL в std::vector<std::string>
namespace pqxx {
    template<> 
    struct string_traits<std::vector<std::string>> {
        static std::vector<std::string> from_string(std::string_view text) {
            if (text.empty() || text == "{}") return {};

            std::vector<std::string> result;
            std::string cleaned(text.substr(1, text.size()-2)); // del {}
            size_t pos = 0;
            while ((pos = cleaned.find(',')) != std::string::npos) {
                result.push_back(cleaned.substr(0, pos));
                cleaned.erase(0, pos + 1);
            }
            result.push_back(cleaned);
            return result;
        };

        static std::string to_string(const std::vector<std::string>& vec) {
            if (vec.empty()) return "{}";
            std::string result = "{" + vec[0];
            for (size_t i = 1; i < vec.size(); ++i) {
                result += "," + vec[i];
            }
            return result + "}";
        };
    };
}; 
// namespace pqxx

struct Client {
    int id;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::vector<std::string> phones;
};

class ClientManager {
public:
    ClientManager(const std::string& conn_str) : conn(conn_str) {}

    void clear_database() {
        pqxx::work txn(conn);
        try {
            // Очистка таблиц с учетом внешних ключей
            txn.exec("TRUNCATE TABLE clients, phones CASCADE");
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            txn.abort();
            throw std::runtime_error("Failed to clear database: " + std::string(e.what()));
        }
    }

    void create_tables() {
        pqxx::work txn(conn);
        txn.exec(
            "CREATE TABLE IF NOT EXISTS clients ("
            "id SERIAL PRIMARY KEY,"
            "first_name VARCHAR(50) NOT NULL,"
            "last_name VARCHAR(50) NOT NULL,"
            "email VARCHAR(100) UNIQUE NOT NULL"
            ");"
        );
        txn.exec(
            "CREATE TABLE IF NOT EXISTS phones ("
            "id SERIAL PRIMARY KEY,"
            "client_id INTEGER REFERENCES clients(id) ON DELETE CASCADE,"
            "phone_number VARCHAR(20) NOT NULL,"
            "UNIQUE (client_id, phone_number)"
            ");"
        );
        txn.commit();
    }

    int add_client(const std::string& first_name, const std::string& last_name, const std::string& email) {
        pqxx::work txn(conn);
        try {
            std::string query = "INSERT INTO clients (first_name, last_name, email) "
                               "VALUES ('" + txn.esc(first_name) + "', '" + 
                                                  txn.esc(last_name) + "', '" + 
                                                  txn.esc(email) + "') RETURNING id";
            auto res = txn.exec(query);
            txn.commit();
            return res[0][0].as<int>();
        } catch (const pqxx::sql_error& e) {
            txn.abort();
            throw std::runtime_error("Failed to add client: " + std::string(e.what()));
        }
    }

    void add_phone(int client_id, const std::string& phone_number) {
        pqxx::work txn(conn);
        try {
            std::string query = "INSERT INTO phones (client_id, phone_number) "
                               "VALUES (" + std::to_string(client_id) + ", '" + 
                                              txn.esc(phone_number) + "')";
            txn.exec(query);
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            txn.abort();
            throw std::runtime_error("Failed to add phone: " + std::string(e.what()));
        }
    }

    void update_client(int client_id, const std::string& first_name, 
                       const std::string& last_name, const std::string& email) {
        pqxx::work txn(conn);
        try {
            std::string query = "UPDATE clients SET "
                "first_name = '" + txn.esc(first_name) + "', "
                "last_name = '" + txn.esc(last_name) + "', "
                "email = '" + txn.esc(email) + "' "
                "WHERE id = " + std::to_string(client_id);
            txn.exec(query);
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            txn.abort();
            throw std::runtime_error("Failed to update client: " + std::string(e.what()));
        }
    }

    void delete_phone(int client_id, const std::string& phone_number) {
        pqxx::work txn(conn);
        try {
            std::string query = "DELETE FROM phones WHERE client_id = " + 
                std::to_string(client_id) + " AND phone_number = '" + 
                txn.esc(phone_number) + "'";
            txn.exec(query);
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            txn.abort();
            throw std::runtime_error("Failed to delete phone: " + std::string(e.what()));
        }
    }

    void delete_client(int client_id) {
        pqxx::work txn(conn);
        try {
            std::string query = "DELETE FROM clients WHERE id = " + 
                std::to_string(client_id);
            txn.exec(query);
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            txn.abort();
            throw std::runtime_error("Failed to delete client: " + std::string(e.what()));
        }
    }

    std::vector<Client> find_clients(const std::string& first_name = "", 
                                     const std::string& last_name = "", 
                                     const std::string& email = "", 
                                     const std::string& phone = "") {
        std::vector<Client> result;
        pqxx::work txn(conn);
        
        std::string where_clause;
        if (!first_name.empty()) {
            where_clause += "clients.first_name = '" + txn.esc(first_name) + "'";
        }
        if (!last_name.empty()) {
            if (!where_clause.empty()) where_clause += " AND ";
            where_clause += "clients.last_name = '" + txn.esc(last_name) + "'";
        }
        if (!email.empty()) {
            if (!where_clause.empty()) where_clause += " AND ";
            where_clause += "clients.email = '" + txn.esc(email) + "'";
        }
        if (!phone.empty()) {
            if (!where_clause.empty()) where_clause += " AND ";
            where_clause += "phones.phone_number = '" + txn.esc(phone) + "'";
        }

        std::string query = 
            "SELECT clients.id, clients.first_name, clients.last_name, clients.email, "
                   "COALESCE(array_agg(phones.phone_number) FILTER (WHERE phones.phone_number IS NOT NULL), '{}') AS phones "
            "FROM clients "
            "LEFT JOIN phones ON clients.id = phones.client_id ";
        
        if (!where_clause.empty()) {
            query += "WHERE " + where_clause + " ";
        }
        query += "GROUP BY clients.id";

        try {
            for (auto [id, fn, ln, em, phones_vec] : 
                 txn.query<int, std::string, std::string, std::string, std::vector<std::string>>(query)) {
                
                Client client{
                    id,
                    fn,
                    ln,
                    em,
                    phones_vec
                };
                
                // del empty string
                client.phones.erase(
                    std::remove_if(client.phones.begin(), client.phones.end(),
                                   [](const std::string& s) { return s.empty(); }),
                    client.phones.end()
                );
                
                result.push_back(client);
            }
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            txn.abort();
            throw std::runtime_error("Failed to find clients: " + std::string(e.what()));
        }

        return result;
    }

private:
    pqxx::connection conn;
};

int main() {
    try {
        ClientManager manager("dbname=clients_db user=postgres password=secret");

        // 1. Инициализация
        std::cout << "=== ИНИЦИАЛИЗАЦИЯ ===" << std::endl;
        manager.create_tables();
        manager.clear_database();
        
        // 2. Добавление клиентов
        std::cout << "\n=== ДОБАВЛЕНИЕ КЛИЕНТОВ ===" << std::endl;
        int id1 = manager.add_client("Иван", "Петров", "ivan@example.com");
        std::cout << "Добавлен Иван Петров (ID: " << id1 << ")" << std::endl;
        
        int id2 = manager.add_client("John", "Doe", "john@example.com");
        std::cout << "Added John Doe (ID: " << id2 << ")" << std::endl;
        
        int id3 = manager.add_client("Мария", "Гarcía", "maria@example.com");
        std::cout << "Añadido María García (ID: " << id3 << ")" << std::endl;

        // 3. Добавление телефонов
        manager.add_phone(id1, "+79001234567");
        manager.add_phone(id2, "+1234567890");
        manager.add_phone(id3, "+34612345678");

        // 4. Поиск клиентов
        std::cout << "\n=== ПОИСК КЛИЕНТОВ ===" << std::endl;
        
        // По русскому имени
        auto rus_clients = manager.find_clients("Иван", "", "");
        std::cout << "Найдено клиентов с именем Иван: " << rus_clients.size() << std::endl;
        
        // По английскому имени
        auto eng_clients = manager.find_clients("John", "", "");
        std::cout << "Found clients named John: " << eng_clients.size() << std::endl;
        
        // По мультиязычной фамилии
        auto mixed_clients = manager.find_clients("", "Гarcía", "");
        std::cout << "Clientes encontrados con apellido García: " << mixed_clients.size() << std::endl;

        // 5. Обновление данных
        std::cout << "\n=== ОБНОВЛЕНИЕ ДАННЫХ ===" << std::endl;
        manager.update_client(id3, "Мария", "Гарсия-Родригес", "maria.garcia@example.com");
        std::cout << "Обновлены данные для Maria García" << std::endl;

        // 6. Вывод всех клиентов
        std::cout << "\n=== ВСЕ КЛИЕНТЫ ===" << std::endl;
        auto all_clients = manager.find_clients();
        for (const auto& client : all_clients) {
            std::cout << "ID: " << client.id << std::endl
                      << "Имя: " << client.first_name << std::endl
                      << "Фамилия: " << client.last_name << std::endl
                      << "Email: " << client.email << std::endl
                      << "Телефоны:" << std::endl;
                      
            if (client.phones.empty()) {
                std::cout << "  Нет телефонов" << std::endl;
            } else {
                for (const auto& phone : client.phones) {
                    std::cout << "  " << phone << std::endl;
                }
            }
            std::cout << "--------------------" << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
};