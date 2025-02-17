#include <iostream>
#include <set>
#include <vector>
#include <list>
#include <algorithm>

// Функция для удаления дубликатов из вектора
std::vector<int> remove_duplicates(std::vector<int> vec) {

    std::sort(vec.begin(), vec.end());

    auto last = std::unique(vec.begin(), vec.end());

    vec.erase(last, vec.end());

    return vec;
}

// Шаблонная функция для контейнера
template <typename Container>
void print_container(const Container& container) {
    for (const auto& element : container) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

int main() {

    // 1 задание
    std::vector<int> input = {1, 1, 2, 5, 6, 1, 2, 4};
    std::vector<int> output = remove_duplicates(input);

    std::cout << "[IN]: ";
    for (int i : input) {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    std::cout << "[OUT]: ";
    for (int i : output) {
        std::cout << i << " ";
    }
    std::cout << std::endl;


    // 2 задание

    std::set<std::string> test_set = { "one", "two", "three", "four" };
    std::list<std::string> test_list = { "one", "two", "three", "four" };
    std::vector<std::string> test_vector = { "one", "two", "three", "four" };

    
    std::cout << "std::set: ";
    print_container(test_set); 

    std::cout << "std::list: ";
    print_container(test_list); 

    std::cout << "std::vector: ";
    print_container(test_vector); 

    return 0;
}