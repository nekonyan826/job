#include"Generator.h"


Generator:: Generator(int n, int end_time,double p,int m)
{
    this->n = n;
    this->m = m;
    this->p = p;
    this->end_time = end_time;
    this->num = 0;
    this->now_time = 0;
    srand((unsigned)time( NULL ));
}

Generator::~Generator()
{
}

std::vector<Job> Generator::get_new_job()
{
    std::vector<Job> new_jobs;
    // this->now_time++;
    if(this->num >= this->n) return new_jobs;
    for(int i = 0;i<this->m;++i)
    {
        double tmp_p = (double)(rand()%(1000)/1000.0);
        // std::cout<<tmp_p<<std::endl;
        if(tmp_p < this->p)
        {
            this->num++;
            // std::cout<<this->p<<" "<<this->now_time<<" "<<this->num<<std::endl;
            int job_length = rand()%(this->end_time - this->now_time);
            Job new_job(this->num,this->now_time,job_length);
            new_jobs.push_back(new_job);
            if(this->num >= this->n) break;
        }
    }
    return new_jobs;
}
bool Generator::check()
{
    if(this->now_time>=this->end_time) return false;
    // if(this->num>=this->n) return false;
    return true;
}
int Generator::get_time()
{
    return this->now_time;
}

int Generator::get_num()
{
    return this->num;
}

void Generator:: add_time()
{
    this->now_time++;
}