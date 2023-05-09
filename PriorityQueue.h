#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

template <typename T>
class PriorityQueue
{
private:
    /* data */
public:
    PriorityQueue(/* args */);
    ~PriorityQueue();
    void update_priority();
    bool empty();
    T top();
    void pop();
    void push(const T& it);
    void size();
};

#endif
