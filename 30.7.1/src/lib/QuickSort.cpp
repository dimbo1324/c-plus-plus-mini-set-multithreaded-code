#include "QuickSort.hpp"
#include <algorithm>
template <typename T>
void quicksort_sync(std::vector<T> &arr, int left, int right)
{
    if (left >= right)
        return;
    T pivot = arr[(left + right) / 2];
    int i = left, j = right;
    while (i <= j)
    {
        while (arr[i] < pivot)
            ++i;
        while (arr[j] > pivot)
            --j;
        if (i <= j)
            std::swap(arr[i++], arr[j--]);
    }
    if (left < j)
        quicksort_sync(arr, left, j);
    if (i < right)
        quicksort_sync(arr, i, right);
}
template void quicksort_sync<int>(std::vector<int> &, int, int);
template <typename T>
std::future<void> quicksort_async(
    ThreadPool &pool,
    std::vector<T> &arr,
    int left,
    int right,
    std::shared_ptr<std::atomic<size_t>> counter,
    std::shared_ptr<std::promise<void>> promise_ptr)
{
    bool root = false;
    if (!promise_ptr)
    {
        root = true;
        promise_ptr = std::make_shared<std::promise<void>>();
        counter = std::make_shared<std::atomic<size_t>>(1);
    }
    auto fut = promise_ptr->get_future();
    auto task = [&pool, &arr, left, right, counter, promise_ptr]()
    {
        auto finish = [counter, promise_ptr]()
        {
            if (--(*counter) == 0)
                promise_ptr->set_value();
        };
        const int ASYNC_THRESHOLD = 100000;
        if (left < right)
        {
            T pivot = arr[(left + right) / 2];
            int i = left, j = right;
            while (i <= j)
            {
                while (arr[i] < pivot)
                    ++i;
                while (arr[j] > pivot)
                    --j;
                if (i <= j)
                    std::swap(arr[i++], arr[j--]);
            }
            if (left < j)
            {
                int len = j - left + 1;
                if (len > ASYNC_THRESHOLD)
                {
                    ++(*counter);
                    pool.submit(quicksort_async<T>,
                                std::ref(pool), std::ref(arr),
                                left, j, counter, promise_ptr);
                }
                else
                {
                    quicksort_sync(arr, left, j);
                }
            }
            if (i < right)
            {
                int len = right - i + 1;
                if (len > ASYNC_THRESHOLD)
                {
                    ++(*counter);
                    pool.submit(quicksort_async<T>,
                                std::ref(pool), std::ref(arr),
                                i, right, counter, promise_ptr);
                }
                else
                {
                    quicksort_sync(arr, i, right);
                }
            }
        }
        finish();
    };
    pool.submit(task);
    return root ? fut : std::future<void>();
}
template std::future<void> quicksort_async<int>(
    ThreadPool &, std::vector<int> &, int, int,
    std::shared_ptr<std::atomic<size_t>>,
    std::shared_ptr<std::promise<void>>);
