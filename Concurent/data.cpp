#include "data.h"

Data::Data(int v) : value(v) {}

void swap_lock(Data& a, Data& b) {
    std::lock(a.mtx, b.mtx);
    std::lock_guard<std::mutex> lock_a(a.mtx, std::adopt_lock);
    std::lock_guard<std::mutex> lock_b(b.mtx, std::adopt_lock);
    std::swap(a.value, b.value);
}

void swap_scoped(Data& a, Data& b) {
    std::unique_lock<std::mutex> lock_a(a.mtx, std::defer_lock);
    std::unique_lock<std::mutex> lock_b(b.mtx, std::defer_lock);
    std::lock(lock_a, lock_b);
    std::swap(a.value, b.value);
};

void swap_unique(Data& a, Data& b){
    std::unique_lock<std::mutex> lock1(a.mtx);
    std::unique_lock<std::mutex> lock2(b.mtx);
    std::swap(a.value, b.value);
}