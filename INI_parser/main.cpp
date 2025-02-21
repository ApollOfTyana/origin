#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cctype>

class ini_parser {
private:
    std::map<std::string, std::map<std::string, std::string>> data;

    void trim(std::string &str) { //удаляем пустые места
        
        str.erase(str.begin(), std::find_if(str.begin(), str.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        str.erase(std::find_if(str.rbegin(), str.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), str.end());
    }

    void parse_line(const std::string& line, std::string& current_section) {

        if (line.empty() || line[0] == ';') return; // comments ignore

        std::string trimmed_line = line;
        trim(trimmed_line);

        // [section]
        if (trimmed_line[0] == '[' && trimmed_line[trimmed_line.size() - 1] == ']') {
            std::string section_name = trimmed_line.substr(1, trimmed_line.size() - 2);
            trim(section_name);
            current_section = section_name;
        } else {
            // key=value
            size_t pos = trimmed_line.find('=');
            if (pos == std::string::npos) return;

            std::string key = trimmed_line.substr(0, pos);
            std::string value = trimmed_line.substr(pos + 1);

            trim(key);
            trim(value);

            data[current_section][key] = value;
        }
    }

public:
    ini_parser(const std::string &filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Could't open file: " + filename);
        }

        std::string line;
        std::string current_section = "global"; 

        while (std::getline(file, line)) {
            try {
                parse_line(line, current_section);
            } catch (const std::exception& e) {
                throw std::runtime_error("Error while parsing file: " + std::string(e.what()));
            }
        }
    }

    template <typename T>
    T get_value(const std::string &variable) const {
        // Разбиваем строку на секцию и переменную
        size_t pos = variable.find('.');
        if (pos == std::string::npos) {
            throw std::invalid_argument("Invalid variable format");
        }

        std::string section_name = variable.substr(0, pos);
        std::string key_name = variable.substr(pos + 1);

        // существование секции и ключа
        auto section_it = data.find(section_name);
        if (section_it == data.end()) {
            throw std::invalid_argument("Section not found: " + section_name);
        }

        auto key_it = section_it->second.find(key_name);
        if (key_it == section_it->second.end()) {
            // Если переменная не найдена, выводим подсказку
            std::vector<std::string> suggestions;
            for (const auto& pair : section_it->second) {
                suggestions.push_back(pair.first);
            }
            throw std::invalid_argument("Variable not found: " + key_name + ". Possible suggestions: " + join(suggestions, ", "));
        }

        // Конвертируем значение в тип T
        std::istringstream ss(key_it->second);
        T value;
        ss >> value;
        if (ss.fail()) {
            throw std::invalid_argument("Invalid value format for variable: " + key_name);
        }
        return value;
    }

private:
    
    static std::string join(const std::vector<std::string>& vec, const std::string& delimiter) {
        std::ostringstream oss;
        for (size_t i = 0; i < vec.size(); ++i) {
            if (i != 0) oss << delimiter;
            oss << vec[i];
        }
        return oss.str();
    }
};

int main() {
    try {
        ini_parser parser("CONF.ini");

       
        std::string value1 = parser.get_value<std::string>("Section1.var2");
        std::cout << "Value: " << value1 << std::endl;

        int value2 = parser.get_value<int>("Section2.var1");
        std::cout << "Value: " << value2 << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}
