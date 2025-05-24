#include <iostream>
#include <future>
#include <thread>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>

// FIRST TASK
// minimum find in block
template<typename T>
void selection_sort_async(std::vector<T>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        std::promise<int> p;
        auto fut = p.get_future();

        std::thread([p = std::move(p), &vec, i, n]() mutable {
            int min_idx = i;
            for (int j = i + 1; j < n; ++j)
                if (vec[j] < vec[min_idx]) min_idx = j;
            p.set_value(min_idx);
        }).detach();

        int min_index = fut.get(); 
        if (min_index != i) std::swap(vec[i], vec[min_index]);
    }
}

//SECOND TASK
template <typename RandomAccessIt, typename Function>
void parallel_for_each(RandomAccessIt first, RandomAccessIt last, const Function& f) {
    constexpr size_t threshold = 1000;
    const size_t distance = std::distance(first, last);

    if (distance <= threshold) {
        std::for_each(first, last, f);
        return;                
    }

    RandomAccessIt mid = first + distance / 2;

    auto future_left = std::async(std::launch::async, &parallel_for_each<RandomAccessIt, Function>, first, mid, std::ref(f));
    auto future_right = std::async(std::launch::async, &parallel_for_each<RandomAccessIt, Function>, mid, last, std::ref(f));

    future_left.wait();
    future_right.wait();
}

int main() {

    //FIRST TASK
    
    std::cout << "\t\t\t FIRST TASK" << std::endl;
    
    std::vector<int> data = {5, 2, 9, 1, 5, 6};
    std::cout << "Before sort: ";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n";

    selection_sort_async(data);

    std::cout << "After sort: ";
    for (int x : data) std::cout << x << " ";
    std::cout << "\n";

    //SECOND TASK

    std::cout << "\t\t\t SECOND TASK" << std::endl;
    
    std::vector<int> data2(10'000);
    std::iota(data2.begin(), data2.end(), 0); 

    int res = 0;
    auto add = [&](int x) { res += x; };

    parallel_for_each(data2.begin(), data2.end(), add);

    std::cout << "Total sum: " << res << std::endl;
    
    res = 0;
    auto diff = [&](int x) { res -= x; };

    parallel_for_each(data2.begin(), data2.end(), diff);

    std::cout << "Total difference: " << res << std::endl;

    return 0;
}