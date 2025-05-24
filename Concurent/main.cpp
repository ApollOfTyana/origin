#include <atomic>
#include <iostream>
#include <mutex>
#include <iomanip>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <condition_variable>

#include "data.h"

std::atomic<int> client_count(0);
int max_client;

std::mutex cout_mutex;
std::condition_variable cv;
bool start_flag = false;

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
std::random_device rd;
std::mt19937 gen(rd());
std::bernoulli_distribution error_dist(0.05); // 5%

void worker(int id, size_t total_steps, int num_threads) {
    auto start = std::chrono::high_resolution_clock::now();
    std::string bar(20, ' ');
    std::vector<bool> errors(20, false);

    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        std::cout << "Thread " << std::setw(2) << id << " [" << std::setw(20) << "" << "]\n";
    }

    // thread wait 
    {
        std::unique_lock<std::mutex> lock(cout_mutex);
        static int threads_started = 0;
        ++threads_started;
        if (threads_started == num_threads) {
            start_flag = true;
            cv.notify_all();
        } else {
            cv.wait(lock, []{ return start_flag; });
        }
    }

    for (size_t step = 0; step <= 20; ++step) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        
        if (step < 20) {
            if (error_dist(gen)) {
                errors[step] = true;
            }
            bar[step] = '#';
        }

        {
            std::lock_guard<std::mutex> lock(cout_mutex);
            // move on string 
            int lines_up = num_threads - id + 1; // +1 "Task II"
            std::cout << "\033[" << lines_up << "A"; // move UP
            
            // Clear string
            std::cout << "\r\033[K";
            
            // Color format string
            std::string bar_str;
            for (size_t i = 0; i < 20; ++i) {
                if (i < step) {
                    if (errors[i]) {
                        bar_str += "\033[31m#\033[0m"; // red color - Err
                    } else {
                        bar_str += "#";
                    }
                } else {
                    bar_str += " ";
                }
            }
            
            std::cout << "Thread " << std::setw(2) << id << " [" << bar_str << "]";
            std::cout << "\033[" << lines_up << "B"; // move back on pos
            std::cout.flush();
        }
    }

    auto duration = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
    {
        std::lock_guard<std::mutex> lock(cout_mutex);
        int lines_up = num_threads - id + 1;
        std::cout << "\033[" << lines_up << "A"; 
        std::cout << "\r\033[K"; 
        std::cout << "Thread " << std::setw(2) << id << " [####################] " 
                  << duration << "s\n";
        std::cout << "\033[" << lines_up << "B";
        std::cout.flush();
    }
}

// /////////////////////////////////////////////TASK III /////////////////////////////////////////////////////////

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

    const int num_threads = 14;
    const size_t steps = 100;

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        threads.emplace_back(worker, i + 1, steps, num_threads);
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