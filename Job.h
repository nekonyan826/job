#ifndef JOB_H
#define JOB_H
#include<iostream>

class Job {
public:
	int s;//作业开始时间
    int w;//等待时间
	int t;//作业实施时间
	int p;//作业的优先级
	int id;//作业的编号
    int e;

	Job();
	Job(int id, int s, int t);
	friend bool operator < (const Job& a, const Job& b);
	Job& operator --();
    Job& operator ++();
	Job& operator =(const Job& a);
	friend std::ostream& operator<<(std::ostream& out, const Job& a);
    int end_time();
};

#endif // !JOB_H

