#include "QuickSort.hpp"
#include "Utils.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
#include <windows.h>
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    const size_t N = 5'000'000;
    std::vector<int> data(N);
    std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<> dist(0, 1'000'000);
    for (auto &x : data)
        x = dist(gen);
    auto data_copy = data;
    ThreadPool pool;
    auto t1 = now();
    auto fut = quicksort_async(pool, data, 0, static_cast<int>(data.size()) - 1);
    fut.wait();
    auto t2 = now();
    std::cout << "Быстрая сортировка с пулом потоков: "
              << elapsed_seconds(t1, t2) << " сек\n";
    t1 = now();
    std::sort(data_copy.begin(), data_copy.end());
    t2 = now();
    std::cout << "std::sort в одном потоке: "
              << elapsed_seconds(t1, t2) << " сек\n";
    std::cout << "Проверка сортировки: "
              << (std::is_sorted(data.begin(), data.end()) ? "ОК" : "ОШИБКА")
              << "\n";

    return 0;
}
