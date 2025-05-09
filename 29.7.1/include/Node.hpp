#pragma once
#include <mutex>
struct Node
{
    int value;
    Node *next;
    std::mutex node_mutex;
    explicit Node(int v) : value(v), next(nullptr) {}
};
