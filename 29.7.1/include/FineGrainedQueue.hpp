#pragma once
#include "Node.hpp"
#include <mutex>
class FineGrainedQueue
{
private:
    Node *head;

public:
    explicit FineGrainedQueue(int firstValue);
    ~FineGrainedQueue();
    void insertIntoMiddle(int value, int pos);
    void print() const;
};
