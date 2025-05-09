#pragma once
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>
#include <condition_variable>
#include <stdexcept>
class ThreadPool
{
public:
    explicit ThreadPool(size_t num_threads = std::thread::hardware_concurrency());
    ~ThreadPool();
    template <typename F, typename... Args>
    auto submit(F &&f, Args &&...args)
        -> std::future<typename std::invoke_result_t<F, Args...>>
    {
        using ReturnType = typename std::invoke_result_t<F, Args...>;
        auto task_ptr = std::make_shared<std::packaged_task<ReturnType()>>(
            std::bind(std::forward<F>(f), std::forward<Args>(args)...));
        std::future<ReturnType> res = task_ptr->get_future();
        {
            std::lock_guard<std::mutex> lock(queue_mutex);
            if (stop_flag)
                throw std::runtime_error("ThreadPool stopped");
            tasks.emplace([task_ptr]()
                          { (*task_ptr)(); });
        }
        condition.notify_one();
        return res;
    }

private:
    using Task = std::function<void()>;
    std::vector<std::thread> workers;
    std::queue<Task> tasks;
    std::mutex queue_mutex;
    std::condition_variable condition;
    bool stop_flag;
};
