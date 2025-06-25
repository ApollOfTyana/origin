#include <iostream>
#include <chrono>
#include <thread>

#include "thread_pool.h"

// Тестовая функция
void print_task(int id) {
    std::cout << "Tasl " << id << " in thread " << std::this_thread::get_id() << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

int main() {
    thread_pool pool(std::thread::hardware_concurrency());

    int id = 0;
    for (int i = 0; i < 10; ++i) {
        pool.submit(print_task, id++);
        pool.submit(print_task, id++);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    return 0;
}