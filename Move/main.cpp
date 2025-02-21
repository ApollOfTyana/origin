#include <iostream>
#include <vector>
#include <string>
#include <utility>  
#include <algorithm>

                                                                        //задача 1
template <typename T>
void move_vectors(std::vector<T>& from, std::vector<T>& to) {
    to = std::move(from);
}
                                                                        //задача 2

class big_integer {
private:
    
    std::string number;

    // нули впереди убираем
    void zero_rmv() {
        while (number.size() > 1 && number[0] == '0') {
            number.erase(0, 1);
        }
    }

public:
    big_integer(const std::string &N) : number(N) {
        zero_rmv();
    }

    // перемещения
    big_integer(big_integer&& other) noexcept : number(std::move(other.number)) {}

    // Перемещающий опер присвивания
    big_integer& operator=(big_integer&& other) noexcept {
        if (this != &other) {
            number = std::move(other.number);
        }
        return *this;
    }

    big_integer operator+(const big_integer& other) const {
        
        std::string n_1 = number;
        std::string n_2 = other.number;
        std::string result;
        
        int l_1 = n_1.size(), l_2 = n_2.size();
        int max_l = std::max(l_1, l_2);
        int с = 0;
    

        // наикороткое число ведущими нулями прогружаем
        n_1.insert(n_1.begin(), max_l - l_1, '0');
        n_2.insert(n_2.begin(), max_l - l_2, '0');

        for (int i = max_l - 1; i >= 0; --i) {
            int sum = (n_1[i] - '0') + (n_2[i] - '0') + с;
            result.push_back('0' + sum % 10);
            с = sum / 10;
        }

        if (с) {
            result.push_back('1');
        }

        std::reverse(result.begin(), result.end());
        
        return big_integer(result);
    }

    
    big_integer operator*(int num) const {
        if (num == 0) return big_integer("0");
        
        std::string result;
        int c = 0;
        for (int i = number.size() - 1; i >= 0; --i) {
            int prod = (number[i] - '0') * num + c;
            result.push_back('0' + prod % 10);
            c = prod / 10;
        }

        if (c) {
            result.push_back('0' + c);
        }

        std::reverse(result.begin(), result.end());
        return big_integer(result);
    }

    
    friend std::ostream& operator<<(std::ostream& os, const big_integer& n) {
        os << n.number;
        return os;
    }
};

int main() {
                                                                        //задача 1                                                                
    std::vector<std::string> one = { "test_string1", "test_string2" };
    std::vector<std::string> two;

    move_vectors(one, two);

    // Проверим результат
    std::cout << "Содержимое 'two':" << std::endl;
    for (const auto& s : two) {
        std::cout << s << std::endl;
    }

    // После перемещения вектор 'one' должен быть пустым.
    std::cout << "Содержимое 'one' после:" << std::endl;
    std::cout << "И размер 'one': " << one.size() << std::endl;  // Должен быть 0
    
                                                                        //задача 2

    big_integer num_1("114575");
    big_integer num_2("78524");
    big_integer res = num_1 + num_2;

    std::cout <<"\nРезультат сложения: "<< num_1 << "+" << num_2<< " = "<< res << std::endl; // 193099                                                                    
    return 0;
}
