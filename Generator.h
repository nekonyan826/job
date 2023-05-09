#ifndef GENERATOR_H
#define GENERATOR_H
#include"Job.h"
#include<vector>
class  Generator
{
private:
    /* data */
    int n; //作业个数
    int m; // 一轮最多注入多少作业
    int end_time; //最后一个作业到达的最终时间
    int now_time;//当前时间
    int num; //当前作业
    double p; //产生作业的概率

public:
    Generator(int n, int end_time,double p,int m);
    ~Generator();
    std::vector<Job> get_new_job();
    int get_time();
    int get_num();
    void add_time();
    bool check();
};



#endif
