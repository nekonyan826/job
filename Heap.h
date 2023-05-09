#ifndef HEAP_H
#define HEAP_H
// #include"PriorityQueue.h"
#include"Job.h"
#include<vector>
// template<typename T>
class Heap
{
private:
    /* data */
    std::vector<Job> h;
    void push_down();
    void push_up();
    void swap(Job& a, Job&b);
    bool can_push(int position);
public:
    Heap(/* args */);
    ~Heap();
    void update_priority();
    bool empty();
    Job top();
    void pop();
    void push(const Job& it);
    int size();
};




#endif