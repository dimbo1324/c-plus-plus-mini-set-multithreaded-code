#pragma once
#include <future>
#include <vector>
#include <atomic>
#include <memory>
#include "ThreadPool.hpp"
template <typename T>
void quicksort_sync(std::vector<T> &arr, int left, int right);
template <typename T>
std::future<void> quicksort_async(
    ThreadPool &pool,
    std::vector<T> &arr,
    int left,
    int right,
    std::shared_ptr<std::atomic<size_t>> counter = nullptr,
    std::shared_ptr<std::promise<void>> promise_ptr = nullptr);
