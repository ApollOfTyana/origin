#pragma once

#include <mutex>
#include <utility>

class Data {

    public: 
    int value;
    mutable std::mutex mtx;

    Data(int v);
};

void swap_lock(Data& a, Data& b);
void swap_scoped(Data& a, Data& b);
void swap_unique(Data& a, Data& b);