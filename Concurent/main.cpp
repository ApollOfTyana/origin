#include <atomic>
#include <iostream>
#include <mutex>
#include <iomanip>
#include <thread>
#include <chrono>
#include <vector>

#include "data.h"

std::atomic<int> client_count(0);
int max_client;

std::mutex cout_mutex;

// /////////////////////////////////////////////TASK I /////////////////////////////////////////////////////////

void client() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        if (client_count.load(std::memory_order_relaxed) < max_client) {
            client_count.fetch_add(1, std::memory_order_release);
            std::cout << "Client added. Total: " << client_count.load(std::memory_order_acquire) << std::endl;
        } else {
            break;
        }
    }
}

void operatoros() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        int current = client_count.load(std::memory_order_acquire);
        if (current > 0) {
            client_count.fetch_sub(1, std::memory_order_release);
            std::cout << "Operator in work. Total: " << client_count.load(std::memory_order_relaxed) << std::endl;
        } else {
            break;
        }
    }
}

// /////////////////////////////////////////////TASK II /////////////////////////////////////////////////////////
void worker(int id, size_t total_steps) {
    auto start = std::chrono::high_resolution_clock::now();
    std::ostringstream oss;
    oss << "Thread " << std::setw(2) << id
        << " [" << std::setw(18) << std::left << "" << "]";

    std::string bar(20, ' ');
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << oss.str() << "\r";
    }

    for (size_t i = 0; i <= 20; ++i) {
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        bar[i] = '#';
        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "\33[2K\r"; // Очистка строки
            std::cout << "Thread " << std::setw(2) << id
                      << " [" << std::setw(20) << std::left << bar << "]";
            std::cout.flush();
        }
    }

    auto duration = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "\33[2K\r";
        std::cout << "Thread " << std::setw(2) << id
                  << " [####################] Done in " << duration << "s\n";
    }
}


int main(int argc, char* argv[]) {

// /////////////////////////////////////////////TASK I /////////////////////////////////////////////////////////
    std::cout << "\t\t Task I" << std::endl;
    
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <max_client>" << std::endl;
        return 1;
    }
    max_client = std::stoi(argv[1]);

    std::thread t1(client);
    std::thread t2(operatoros);

    t1.join();
    t2.join();

// /////////////////////////////////////////////TASK II /////////////////////////////////////////////////////////

    std::cout << "\t\t Task II" << std::endl;

    const int num_threads = 4;
    const size_t steps = 100;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i + 1, steps);
    }

    for (auto& t : threads) t.join();

// /////////////////////////////////////////////TASK III /////////////////////////////////////////////////////////

    std::cout << "\t\t Task III" << std::endl;
    
    Data d1(10), d2(20);

    std::cout << "Bfr swp: data first -> " << d1.value << ", data second -> " << d2.value << "\n";
    swap_lock(d1,d2);
    swap_scoped(d1,d2);
    swap_unique(d1,d2);
    std::cout << "Afr swp: data first -> " << d1.value << ", data second -> " << d2.value << "\n";
  

    return 0;
}