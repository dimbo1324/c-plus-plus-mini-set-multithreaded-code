#include "FineGrainedQueue.hpp"
#include <iostream>
FineGrainedQueue::FineGrainedQueue(int firstValue)
{
    head = new Node(firstValue);
}
FineGrainedQueue::~FineGrainedQueue()
{
    Node *cur = head;
    while (cur)
    {
        Node *next = cur->next;
        delete cur;
        cur = next;
    }
}
void FineGrainedQueue::insertIntoMiddle(int value, int pos)
{
    head->node_mutex.lock();
    Node *prev = head;
    Node *cur = prev->next;
    if (cur)
        cur->node_mutex.lock();
    int idx = 1;
    while (cur && idx < pos)
    {
        prev->node_mutex.unlock();
        prev = cur;
        cur = cur->next;
        if (cur)
            cur->node_mutex.lock();
        ++idx;
    }
    Node *newNode = new Node(value);
    prev->next = newNode;
    newNode->next = cur;
    if (cur)
        cur->node_mutex.unlock();
    prev->node_mutex.unlock();
}
void FineGrainedQueue::print() const
{
    Node *cur = head;
    while (cur)
    {
        std::cout << cur->value << " -> ";
        cur = cur->next;
    }
    std::cout << "null" << std::endl;
}