#pragma once

#include <vector>
#include <thread>
#include <functional>
#include <future>
#include <atomic>

#include "safe_queue.h"

class thread_pool {
private:
    std::vector<std::thread> workers_;
    safe_queue<std::function<void()>> tasks_;
    std::atomic<bool> stop_{false};

    void worker_thread() {
        while (!stop_) {
            std::function<void()> task;
            if (tasks_.pop(task)) {
                task();
            }
        }
    }

public:
    explicit thread_pool(size_t thread_count = std::thread::hardware_concurrency())
    {
        for (size_t i = 0; i < thread_count; ++i)
        {
            workers_.emplace_back([this] { worker_thread(); });
        }
    }

    ~thread_pool() {
        stop_ = true;
        tasks_.stop();
        for (auto &t : workers_)
        {
            if (t.joinable())
            {
                t.join();
            }
        }
    }

    // Submit a task returning future
    template <typename F, typename... Args>
    auto submit(F &&f, Args &&... args)
        -> std::future<typename std::invoke_result<F, Args...>::type> {

        using return_t = typename std::invoke_result<F, Args...>::type;
        auto task_ptr = std::make_shared<std::packaged_task<return_t()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));

        std::future<return_t> future = task_ptr->get_future();
        tasks_.push([task_ptr] { (*task_ptr)(); });
        return future;
    }
};