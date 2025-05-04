#include <iostream>
#include <iomanip>
#include <vector>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;
int client_count = 0;
int max_client;

void client() {
    while (true) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::lock_guard<std::mutex> lock(mtx);
        if(client_count < max_client) {
            client_count++;
            std::cout << "Client added. Total: " << client_count << std::endl;
        } else {
            break;
        }
    }
}

void operatoros() {
    while(true) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        std::lock_guard<std::mutex> lock(mtx);
        if(client_count > 0) {
            client_count--;
            std::cout << "Operator in work. Total: " <<  client_count << std::endl;
        } else {
            break;
        }
    }
}

// Второе задание

void sum_vectors(const std::vector<int>& a, const std::vector<int>& b, std::vector<int>& result, size_t start, size_t end) {
    for (size_t i = start; i < end; ++i) {
        result[i] = a[i] + b[i];
    }
}

int main(int argc, char* argv[]) {

// //Первое задание

    if(argc !=2 ) {
        std::cerr << argv[0] << " <max_client>" << std::endl;
        return 1;
    }
    max_client = std::stoi(argv[1]);

    std::thread t1(client);
    std::thread t2(operatoros);

    t1.join();
    t2.join();

// Второе задание

std::vector<size_t> sizes = {1000, 10000, 100000, 1000000};
    std::vector<int> threads_counts = {1, 2, 4, 8, 16};

    std::cout << "Количество аппаратных ядер - " << std::thread::hardware_concurrency() << std::endl;

    double l = 0;
    std::cout << "\n" << std::setw(18) << "";
    for (auto size : sizes) {
        std::cout << std::setw(17-l) << size;
        l+=0.3;
    }
    std::cout << "\n";


    for (int threads : threads_counts) {
        std::cout << std::setw(15) << threads << " потоков";
        for (size_t size : sizes) {
            std::vector<int> a(size, 1), b(size, 2), result(size);

            auto start = std::chrono::high_resolution_clock::now();

            std::vector<std::thread> workers;
            size_t chunk = size / threads;
            size_t rem = size % threads;

            for (int i = 0; i < threads; ++i) {
                size_t start_idx = i * chunk;
                size_t end_idx = start_idx + chunk + (i == threads - 1 ? rem : 0);
                workers.emplace_back(sum_vectors, std::cref(a), std::cref(b), std::ref(result), start_idx, end_idx);
            }

            for (auto& t : workers) t.join();

            auto duration = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start).count();
            std::cout << std::fixed << std::setprecision(6) << std::setw(15) << duration;
        }
        std::cout << "\n";
    }
    return 0;
}
