#include"Platform.h"

Platform::Platform(/* args */)
{
    this->state = NOP;
}

Platform::~Platform()
{
}

void Platform::step(int now_time,std::vector<Job> now_jobs)
{
    // std::cout<<this->working_job<<std::endl;
    this->now_time = now_time;
    this->priority_queue.update_priority();
    for(int i=0;i<now_jobs.size();++i)
    {
        this->priority_queue.push(now_jobs[i]);
    }
    //首先判断系统的状态，如果状态为NOP的话，则从优先队列里面取出job进行
    //如果为IN的话，
    if(this->state == IN)
    {
        // std::cout<<this->now_time<<" "<<this->working_job.w<<std::endl;
        if(this->now_time>=this->working_job.end_time())
        {
            this->state = NOP;
            std::cout<<this->working_job<<std::endl;
        }
    }
    else
    {
        if(!this->priority_queue.empty())
        {
            // std::cout<<1<<std::endl;
            this->working_job = priority_queue.top();
            this->state = IN;
            priority_queue.pop();
        }
    }
    //把优先队列里面的东西取出，更新状态
    //把新来的job放进优先队列里面
}

bool Platform::check()
{
    if(this->priority_queue.empty()) return false;
    return true;
}