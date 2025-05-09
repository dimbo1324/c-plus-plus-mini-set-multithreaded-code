#include "ThreadPool.hpp"
ThreadPool::ThreadPool(size_t num_threads)
{
    if (num_threads == 0)
        num_threads = 1;
    stop_flag = false;
    for (size_t i = 0; i < num_threads; ++i)
    {
        workers.emplace_back([this]
                             {
while (true) {
Task task;
{
std::unique_lock<std::mutex> lock(queue_mutex);
condition.wait(lock, [this] {
return stop_flag || !tasks.empty();
});
if (stop_flag && tasks.empty())
return;
task = std::move(tasks.front());
tasks.pop();
}
task();
} });
    }
}
ThreadPool::~ThreadPool()
{
    {
        std::lock_guard<std::mutex> lock(queue_mutex);
        stop_flag = true;
    }
    condition.notify_all();
    for (auto &worker : workers)
    {
        if (worker.joinable())
            worker.join();
    }
}
