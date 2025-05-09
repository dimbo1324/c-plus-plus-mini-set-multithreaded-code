#include <iostream>
#include "FineGrainedQueue.hpp"
#include <windows.h>
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    constexpr int INITIAL_VALUE = 10;
    constexpr int INITIAL_COUNT = 15;
    constexpr int FIRST_INSERT_VALUE = 99;
    constexpr int FIRST_INSERT_POS = 3;
    constexpr int SECOND_INSERT_VALUE = 77;
    constexpr int SECOND_INSERT_POS = 100;
    FineGrainedQueue queue(INITIAL_VALUE);
    for (int i = 1; i <= INITIAL_COUNT; ++i)
    {
        queue.insertIntoMiddle(INITIAL_VALUE + i, i);
    }
    std::cout << "Перед вставкой:" << std::endl;
    queue.print();
    std::cout << "\nВставка первого элемента (value = " << FIRST_INSERT_VALUE
              << ", pos = " << FIRST_INSERT_POS << "):" << std::endl;
    queue.insertIntoMiddle(FIRST_INSERT_VALUE, FIRST_INSERT_POS);
    queue.print();
    std::cout << "\nВставка второго элемента (value = " << SECOND_INSERT_VALUE
              << ", pos = " << SECOND_INSERT_POS << "):" << std::endl;
    queue.insertIntoMiddle(SECOND_INSERT_VALUE, SECOND_INSERT_POS);
    queue.print();
    return 0;
}