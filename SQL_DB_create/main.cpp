#include <iostream>
#include <pqxx/pqxx>
#include <vector>
#include <string>
#include <stdexcept>
#include <algorithm>

namespace pqxx {
    template<> 
    struct string_traits<std::vector<std::string>> {
        static std::vector<std::string> from_string(std::string_view text) {
            if (text.empty() || text == "{}") return {};
            std::string cleaned(text.substr(1, text.size()-2));
            std::vector<std::string> result;
            size_t pos;
            while ((pos = cleaned.find(',')) != std::string::npos) {
                result.push_back(cleaned.substr(0, pos));
                cleaned.erase(0, pos + 1);
            }
            result.push_back(cleaned);
            return result;
        }

        static std::string to_string(const std::vector<std::string>& vec) {
            if (vec.empty()) return "{}";
            std::string result = "{" + vec[0];
            for (size_t i = 1; i < vec.size(); ++i) {
                result += "," + vec[i];
            }
            return result + "}";
        }
    };
}

struct Client {
    int id;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::vector<std::string> phones;
};

class ClientManager {
public:
    class Exception : public std::runtime_error {
    public:
        using std::runtime_error::runtime_error;
    };

    class DatabaseError : public Exception {
    public:
        using Exception::Exception;
    };

    class ClientNotFound : public Exception {
    public:
        using Exception::Exception;
    };

    ClientManager(const std::string& conn_str) : conn(conn_str) {}

    void clear_database() {
        pqxx::work txn(conn);
        try {
            txn.exec("TRUNCATE TABLE clients, phones CASCADE");
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            throw DatabaseError("Failed to clear database: " + std::string(e.what()));
        }
    }

    void create_tables() {
        pqxx::work txn(conn);
        try {
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
        } catch (const pqxx::sql_error& e) {
            throw DatabaseError("Failed to create tables: " + std::string(e.what()));
        }
    }

    int add_client(const std::string& first_name, const std::string& last_name, const std::string& email) {
        pqxx::work txn(conn);
        try {
            auto existing = find_client_by_email(email, txn);
            if (existing) {
                throw DatabaseError("Client with email " + email + " already exists");
            }

            std::string query = "INSERT INTO clients (first_name, last_name, email) "
                               "VALUES (" + txn.quote(first_name) + ", " + 
                               txn.quote(last_name) + ", " + txn.quote(email) + ") RETURNING id";
            auto res = txn.exec(query);
            txn.commit();
            return res[0][0].as<int>();
        } catch (const pqxx::sql_error& e) {
            throw DatabaseError("Failed to add client: " + std::string(e.what()));
        }
    }

    void add_phone(int client_id, const std::string& phone_number) {
        pqxx::work txn(conn);
        try {
            if (!client_exists(client_id, txn)) {
                throw ClientNotFound("Client with ID " + std::to_string(client_id) + " not found");
            }

            std::string query = "INSERT INTO phones (client_id, phone_number) "
                               "VALUES (" + txn.quote(client_id) + ", " + txn.quote(phone_number) + ")";
            txn.exec(query);
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            throw DatabaseError("Failed to add phone: " + std::string(e.what()));
        }
    }

    void update_client(int client_id, const std::string& first_name, 
                       const std::string& last_name, const std::string& email) {
        pqxx::work txn(conn);
        try {
            if (!client_exists(client_id, txn)) {
                throw ClientNotFound("Client with ID " + std::to_string(client_id) + " not found");
            }

            std::string query = "UPDATE clients SET "
                "first_name = " + txn.quote(first_name) + ", "
                "last_name = " + txn.quote(last_name) + ", "
                "email = " + txn.quote(email) + " "
                "WHERE id = " + txn.quote(client_id);
            txn.exec(query);
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            throw DatabaseError("Failed to update client: " + std::string(e.what()));
        }
    }

    void delete_phone(int client_id, const std::string& phone_number) {
        pqxx::work txn(conn);
        try {
            if (!client_exists(client_id, txn)) {
                throw ClientNotFound("Client with ID " + std::to_string(client_id) + " not found");
            }

            std::string query = "DELETE FROM phones WHERE client_id = " + 
                txn.quote(client_id) + " AND phone_number = " + txn.quote(phone_number);
            txn.exec(query);
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            throw DatabaseError("Failed to delete phone: " + std::string(e.what()));
        }
    }

    void delete_client(int client_id) {
        pqxx::work txn(conn);
        try {
            if (!client_exists(client_id, txn)) {
                throw ClientNotFound("Client with ID " + std::to_string(client_id) + " not found");
            }

            std::string query = "DELETE FROM clients WHERE id = " + txn.quote(client_id);
            txn.exec(query);
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            throw DatabaseError("Failed to delete client: " + std::string(e.what()));
        }
    }

    std::vector<Client> find_clients(const std::string& first_name = "", 
                                     const std::string& last_name = "", 
                                     const std::string& email = "", 
                                     const std::string& phone = "") {
        std::vector<Client> result;
        pqxx::work txn(conn);
        try {
            std::string where_clause;
            std::vector<std::string> conditions;

            if (!first_name.empty()) conditions.push_back("clients.first_name = " + txn.quote(first_name));
            if (!last_name.empty()) conditions.push_back("clients.last_name = " + txn.quote(last_name));
            if (!email.empty()) conditions.push_back("clients.email = " + txn.quote(email));
            if (!phone.empty()) conditions.push_back("phones.phone_number = " + txn.quote(phone));

            std::string query = 
                "SELECT clients.id, clients.first_name, clients.last_name, clients.email, "
                       "COALESCE(array_agg(phones.phone_number) FILTER (WHERE phones.phone_number IS NOT NULL), '{}') AS phones "
                "FROM clients "
                "LEFT JOIN phones ON clients.id = phones.client_id ";

            if (!conditions.empty()) {
                query += "WHERE " + conditions[0];
                for (size_t i = 1; i < conditions.size(); ++i) {
                    query += " AND " + conditions[i];
                }
            }

            query += " GROUP BY clients.id";

            for (auto [id, fn, ln, em, phones_vec] : txn.query<int, std::string, std::string, std::string, std::vector<std::string>>(query)) {
                Client client{
                    id,
                    fn,
                    ln,
                    em,
                    phones_vec
                };
                client.phones.erase(
                    std::remove_if(client.phones.begin(), client.phones.end(),
                                   [](const std::string& s) { return s.empty(); }),
                    client.phones.end()
                );
                result.push_back(client);
            }
            txn.commit();
        } catch (const pqxx::sql_error& e) {
            throw DatabaseError("Failed to find clients: " + std::string(e.what()));
        }
        return result;
    }

private:
    pqxx::connection conn;

    bool client_exists(int client_id, pqxx::transaction_base& txn) {
        std::string query = "SELECT EXISTS(SELECT 1 FROM clients WHERE id = " + txn.quote(client_id) + ")";
        auto res = txn.exec(query);
        return res[0][0].as<bool>();
    }

    std::optional<Client> find_client_by_email(const std::string& email, pqxx::transaction_base& txn) {
        std::string query = "SELECT id, first_name, last_name, email FROM clients WHERE email = " + txn.quote(email);
        auto res = txn.exec(query);
        if (res.empty()) return std::nullopt;
        auto row = res[0];
        return Client{
            row["id"].as<int>(),
            row["first_name"].as<std::string>(),
            row["last_name"].as<std::string>(),
            row["email"].as<std::string>(),
            {}
        };
    }
};

int main() {
    try {
        ClientManager manager("dbname=clients_db user=postgres password=secret");
        
        std::cout << "=== ИНИЦИАЛИЗАЦИЯ ===" << std::endl;
        manager.create_tables();
        manager.clear_database();

        std::cout << "\n=== ДОБАВЛЕНИЕ КЛИЕНТОВ ===" << std::endl;
        int id1 = manager.add_client("Иван", "Петров", "ivan@example.com");
        std::cout << "Добавлен Иван Петров (ID: " << id1 << ")" << std::endl;

        int id2 = manager.add_client("John", "Doe", "john@example.com");
        std::cout << "Added John Doe (ID: " << id2 << ")" << std::endl;

        int id3 = manager.add_client("Мария", "Гarcía", "maria@example.com");
        std::cout << "Añadido María García (ID: " << id3 << ")" << std::endl;

        manager.add_phone(id1, "+79001234567");
        manager.add_phone(id2, "+1234567890");
        manager.add_phone(id3, "+34612345678");

        std::cout << "\n=== ПОИСК КЛИЕНТОВ ===" << std::endl;
        auto rus_clients = manager.find_clients("Иван");
        std::cout << "Найдено клиентов с именем Иван: " << rus_clients.size() << std::endl;

        auto eng_clients = manager.find_clients("John");
        std::cout << "Found clients named John: " << eng_clients.size() << std::endl;

        auto mixed_clients = manager.find_clients("", "Гarcía");
        std::cout << "Clientes encontrados con apellido García: " << mixed_clients.size() << std::endl;

        std::cout << "\n=== ОБНОВЛЕНИЕ ДАННЫХ ===" << std::endl;
        manager.update_client(id3, "Мария", "Гарсия-Родригес", "maria.garcia@example.com");
        std::cout << "Обновлены данные для Maria García" << std::endl;

        std::cout << "\n=== ВСЕ КЛИЕНТЫ ===" << std::endl;
        auto all_clients = manager.find_clients();
        for (const auto& client : all_clients) {
            std::cout << "ID: " << client.id << "\n"
                      << "Имя: " << client.first_name << "\n"
                      << "Фамилия: " << client.last_name << "\n"
                      << "Email: " << client.email << "\n"
                      << "Телефоны:\n";
            if (client.phones.empty()) {
                std::cout << "  Нет телефонов\n";
            } else {
                for (const auto& phone : client.phones) {
                    std::cout << "  " << phone << "\n";
                }
            }
            std::cout << "--------------------\n";
        }
    } catch (const ClientManager::ClientNotFound& e) {
        std::cerr << "Ошибка: Клиент не найден - " << e.what() << std::endl;
        return 1;
    } catch (const ClientManager::DatabaseError& e) {
        std::cerr << "Ошибка базы данных: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Стандартная ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}