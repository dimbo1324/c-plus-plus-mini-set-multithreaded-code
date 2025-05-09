#include <iostream>
#include "FineGrainedQueue.hpp"
#include <windows.h>
int main()
{
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    FineGrainedQueue queue(10);
    for (int i = 1; i <= 5; ++i)
    {
        queue.insertIntoMiddle(10 + i, i);
    }
    std::cout << "Перед вставкой:" << std::endl;
    queue.print();
    queue.insertIntoMiddle(99, 3);
    std::cout << "После вставки на позицию 3:" << std::endl;
    queue.print();
    queue.insertIntoMiddle(77, 100);
    std::cout << "После вставки на большую позицию:" << std::endl;
    queue.print();
    return 0;
}