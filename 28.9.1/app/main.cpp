#include <iostream>
#include <vector>
#include <random>
#include "merge_sort.hpp"
#include <windows.h>
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    constexpr int N = 100;
    std::vector<int> data(N);
    std::mt19937 rng(std::random_device{}());
    std::uniform_int_distribution<int> dist(0, 1000);
    for (int &x : data)
        x = dist(rng);
    std::cout << "Исходный массив:\n";
    for (int x : data)
        std::cout << x << ' ';
    std::cout << "\n\n";
    std::vector<int> arr = data;
    parallelMergeSort(arr.data(), N);
    std::cout << "Отсортированный массив:\n";
    for (int x : arr)
        std::cout << x << ' ';
    std::cout << "\n";
    return 0;
}