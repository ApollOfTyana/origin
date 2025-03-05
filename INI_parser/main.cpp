#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <vector>


class ini_parser {
    std::unordered_map<std::string, 
        std::unordered_map<std::string, std::string>> data;

    // удаление пробелов и комментариев
    static std::string clean_line(std::string line) {
        // Удаляем комментарии
        size_t comment_pos = line.find_first_of(";#");
        if(comment_pos != std::string::npos) {
            line.erase(comment_pos);
        }
        
        // remove пробелы в начале и конце
        auto not_space = [](unsigned char c) { return !std::isspace(c); };
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), not_space));
        line.erase(std::find_if(line.rbegin(), line.rend(), not_space).base(), line.end());
        
        return line;
    }

    //  кавычки в значениях ?
    static void process_quotes(std::string& value) {
        if(value.size() >= 2 && 
           ((value.front() == '"' && value.back() == '"') ||
            (value.front() == '\'' && value.back() == '\''))) {
            value = value.substr(1, value.size()-2);
        }
    }

public:
    explicit ini_parser(const std::string& fn) {
        std::string current_section;
        std::ifstream file(fn);
        
        if(!file.is_open()) {
            throw std::runtime_error("Can't open file: " + fn);
        }

        std::string line;
        size_t line_number = 0;
        
        while(std::getline(file, line)) {
            line_number++;
            std::string cleaned = clean_line(line);
            if(cleaned.empty()) continue;

            //секции

            if(cleaned.front() == '[') {
                if(cleaned.back() != ']') {
                    throw std::runtime_error("Invalid section syntax -> line " + 
                        std::to_string(line_number));
                }
                current_section = cleaned.substr(1, cleaned.size()-2);
                current_section = clean_line(current_section);
                
                if(current_section.empty()) {
                    throw std::runtime_error("Empty section name -> line " + 
                        std::to_string(line_number));
                }
                continue;
            }

            // пары ключ и значение

            size_t delim = cleaned.find('=');
            if(delim == 0 || delim == std::string::npos) {
                throw std::runtime_error("Invalid key-value syntax -> line " + 
                    std::to_string(line_number));
            }

            std::string key = clean_line(cleaned.substr(0, delim));
            std::string value = clean_line(cleaned.substr(delim+1));
            
            process_quotes(value);
            
            if(current_section.empty()) {
                throw std::runtime_error("Value without section -> line " + 
                    std::to_string(line_number));
            }
            
            if(key.empty()) {
                throw std::runtime_error("Empty key -> line " + 
                    std::to_string(line_number));
            }

            data[current_section][key] = value;
        }
    }

    template <typename T>
    T get_value(const std::string& var) const {
        size_t dot = var.find('.');
        if(dot == std::string::npos || dot == 0 || dot == var.size()-1) {
            throw std::invalid_argument("Invalid variable format: '" + var + "'");
        }
        
        const std::string section = var.substr(0, dot);
        const std::string key = var.substr(dot+1);
        
        try {
            const auto& section_data = data.at(section);
            try {
                const std::string& value = section_data.at(key);
                
                if constexpr(std::is_same_v<T, std::string>) {
                    return value;
                }
                else if constexpr(std::is_same_v<T, bool>) {
                    static const std::unordered_map<std::string, bool> bool_map{
                        {"true", true},  {"1", true},  {"yes", true},
                        {"false", false}, {"0", false}, {"no", false}
                    };
                    
                    std::string lower_value;
                    lower_value.reserve(value.size());
                    for(char c : value) {
                        lower_value += static_cast<char>(std::tolower(c));
                    }
                    
                    auto it = bool_map.find(lower_value);
                    if(it == bool_map.end()) {
                        throw std::invalid_argument("Invalid boolean value: " + value);
                    }
                    return it->second;
                }
                else {
                    std::istringstream iss(value);
                    // число с плавающей точкой заменяем , на .
                    if constexpr(std::is_floating_point_v<T>) {
                        std::string processed = value;
                        std::replace(processed.begin(), processed.end(), ',', '.');
                        iss.str(processed);
                    }
                    
                    T result;
                    iss >> result;
                    
                    // оставшиеся symbol ?
                    if(iss.fail() || iss.peek() != EOF) {
                        throw std::invalid_argument("Conv failed for value: " + value);
                    }
                    return result;
                }
            }
            catch(const std::out_of_range&) {
                throw std::out_of_range("Key '" + key + "' not found in section '" + section + "'");
            }
        }
        catch(const std::out_of_range&) {
            throw std::out_of_range("Section '" + section + "' not found");
        }
    }
};

int main() {
    try {
        ini_parser parser("CONF.ini");
        
        std::cout << "String значение: " << parser.get_value<std::string>("Section1.name") << '\n';
        std::cout << "Double значение: " << parser.get_value<double>("Section1.var1") << '\n';
        std::cout << "Double значение: " << parser.get_value<double>("Section3.var1") << '\n';
        std::cout << "Boolean значение: " << std::boolalpha << parser.get_value<bool>("Section2.enabled") << '\n';
        std::cout << "Boolean значение: " << std::boolalpha << parser.get_value<bool>("Section3.var2") << '\n';
    } 
    catch(const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
    return 0;
}