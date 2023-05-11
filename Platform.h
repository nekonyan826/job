#ifndef PLATFORM_H
#define PLATFORM_H
#include"Config.h"
#include"Job.h"
#include"Heap.h"
#include"MinHBLT.h"
#include<vector>
class Platform
{
private:
    /* data */
    int state; //当前状态
    Job working_job;
    int now_time; //现在第几轮了
    // std::vector<Job> buffer;
    // Heap priority_queue;
    MinHBLT priority_queue;

public:
    Platform(/* args */);
    ~Platform();
    void step(int now_time,std::vector<Job> now_jobs);
    bool check();
    void print();
};

#endif