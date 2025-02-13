#include <iostream>
#include <stdexcept>

class smart_array {
public:
    // Конструктор, принимающий количество элементов
    smart_array(size_t size) : size_(0), capacity_(size), data_(new int[capacity_]) {}

    ~smart_array() {
        delete[] data_;
    }

    // Конструктор копирования
    smart_array(const smart_array& other)
        : size_(other.size_), capacity_(other.capacity_), data_(new int[capacity_])
    {
        for (size_t i = 0; i < size_; ++i) {
            data_[i] = other.data_[i];
        }
    }

    // Оператор присваивания
    smart_array& operator=(const smart_array& rhs)
    {
        if (this != &rhs) { 
            delete[] data_;
            
            size_ = rhs.size_;
            capacity_ = rhs.capacity_;
            data_ = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = rhs.data_[i];
            }
        }
        
        return *this;
    }

    // Функция добавления нового элемента в массив
    void add_element(int element) {
        if (size_ >= capacity_) {
            capacity_ *= 2;
            int* new_data = new int[capacity_];
            for (size_t i = 0; i < size_; ++i) {
                new_data[i] = data_[i];
            }
            delete[] data_;
            data_ = new_data;
        }
        data_[size_++] = element;
    }

    // Функция получения элемента по индексу
    int get_element(size_t index) const {
        if (index >= size_) {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

private:
    size_t size_;      
    size_t capacity_;  // вместимость массива
    int* data_;       
};

int main() {
    try {
        smart_array arr(5);
        arr.add_element(1);
        arr.add_element(4);
        arr.add_element(155);
        arr.add_element(14);
        arr.add_element(15);
        std::cout << arr.get_element(1) << " " << arr.get_element(0) << std::endl;
        
        smart_array new_array(2);
        new_array.add_element(44);
        new_array.add_element(34);

        arr = new_array;
        std::cout << "After assignment:" << std::endl;
        std::cout << arr.get_element(0) << " " << arr.get_element(1) << std::endl;

    }
    catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}