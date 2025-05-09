#include "merge_sort.hpp"
#include <vector>
#include <future>
#include <atomic>
#include <thread>
static const unsigned int MAX_THREADS = std::thread::hardware_concurrency() > 0
                                            ? std::thread::hardware_concurrency()
                                            : 2;
static std::atomic<int> active_threads{0};
namespace
{
    void merge(int *arr, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;
        std::vector<int> L(n1), R(n2);
        for (int i = 0; i < n1; ++i)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; ++j)
            R[j] = arr[mid + 1 + j];
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
                arr[k++] = L[i++];
            else
                arr[k++] = R[j++];
        }
        while (i < n1)
            arr[k++] = L[i++];
        while (j < n2)
            arr[k++] = R[j++];
    }
    void parallelMergeSortImpl(int *arr, int left, int right)
    {
        if (left >= right)
            return;
        int mid = left + (right - left) / 2;
        bool spawn = active_threads.load() < static_cast<int>(MAX_THREADS);
        std::future<void> left_future;
        if (spawn)
        {
            active_threads.fetch_add(1);
            left_future = std::async(std::launch::async, [=, &arr]()
                                     {
parallelMergeSortImpl(arr, left, mid);
active_threads.fetch_sub(1); });
        }
        else
        {
            parallelMergeSortImpl(arr, left, mid);
        }
        parallelMergeSortImpl(arr, mid + 1, right);
        if (spawn)
            left_future.get();
        merge(arr, left, mid, right);
    }
}
void parallelMergeSort(int *arr, int n)
{
    parallelMergeSortImpl(arr, 0, n - 1);
}
void sequentialMergeSort(int *arr, int n)
{
    if (n <= 1)
        return;
    int mid = n / 2;
    sequentialMergeSort(arr, mid);
    sequentialMergeSort(arr + mid, n - mid);
    merge(arr, 0, mid - 1, n - 1);
}