#include <iostream>
#include <vector>

// Версия для отдельных значений
template<typename T>
T square(T value) {
    return value * value;
}

// Версия для контейнеров
template<typename Container>
void square_container(Container& container) {
    for (auto& item : container) {
        item = square(item);
    }
}
// вторая задача

template <typename T>
class Table {
public:
    // Конструктор, принимающий количество строк и столбцов
    Table(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
        data_ = new T[rows * cols];
    }

    ~Table() {
        delete[] data_;
    }

    const T* operator[](size_t row) const {
        return &(data_[row * cols_]);
    }

    T* operator[](size_t row) {
        return &(data_[row * cols_]);
    }

    size_t Size() const {
        return rows_ * cols_;
    }

private:
    size_t rows_;       
    size_t cols_;       
    T* data_;           
};

//третья задача

// Функтор для подсчёта суммы и количества чисел, делящихся на 3
class Counter {
    public:
        void operator()(int num) {
            if (num % 3 == 0) {
                sum += num;
                count++;
            }
        }
    
        int get_sum() const {
            return sum;
        }
    
        int get_count() const {
            return count;
        }
    
    private:
        static int sum;
        static int count;
    };
    
int Counter::sum = 0;
int Counter::count = 0;

int main() {
                                            //первая задача
    // Тестирование с простым числом
    int number = 4;
    std::cout << square(number) << std::endl; // Выведет 16

    // Тестирование с вектором
    std::vector<int> vector;
    vector.push_back(-1);
    vector.push_back(4);
    vector.push_back(8);

    square_container(vector);
    for (int item : vector) {
        std::cout << item << ' ';
    }
    std::cout << std::endl; // Выведет 1 16 64

                                            //вторая задача

    auto test = Table<int>(2, 3);
    test[0][0] = 4;
    std::cout << test[0][0] << std::endl; // Выводит 4
                                            
                                            //третья задача
     // Входные данные
     std::vector<int> numbers;
     numbers.push_back(4);
     numbers.push_back(1);
     numbers.push_back(3);
     numbers.push_back(6);
     numbers.push_back(25);
     numbers.push_back(54);
 
     // Применение функтора ко всем элементам вектора
     Counter counter;
     std::for_each(numbers.begin(), numbers.end(), counter);
 
     // Вывод результатов
     std::cout << "get_sum() = " << counter.get_sum() << std::endl;
     std::cout << "get_count() = " << counter.get_count() << std::endl;

    return 0;
}