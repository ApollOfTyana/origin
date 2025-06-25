#pragma once

#include <queue>
#include <mutex>
#include <condition_variable>

template <typename T>
class safe_queue {
    private:
        std::queue<T> queue_;
        std::mutex mutex_;
        std::condition_variable cond_;
        bool stop_ = false;
    
    public:
        void push(T value) {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(value));
        }
        cond_.notify_one();
    }

    bool pop(T &value)  {
        std::unique_lock<std::mutex> lock(mutex_);
        cond_.wait(lock,[this] {    return stop_ || !queue_.empty(); });

        if (stop_ && queue_.empty()) {
            return false;
        }

        value = std::move(queue_.front());
        queue_.pop();

        return true;
    }

    void stop() {
        {
            std::lock_guard<std::mutex> lock(mutex_);
            stop_ = true;
        }
        cond_.notify_all();
    };
};