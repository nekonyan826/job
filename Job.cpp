#include"Job.h"

Job::Job(){}//构造函数

Job::Job(int id, int s, int t) {
    this->id = id;
    this->s = s;
    this->t = t;
    this->p = t;
    this->w = 0;
}

bool operator < (const Job& a, const Job& b)
{ 
	if(a.p != b.p) return a.p < b.p; 
	return a.id < b.id;
}

Job& Job::operator --() {
	this->p--;
	return *this;
}
Job& Job::operator ++() {
	this->w++;
	return *this;
}

Job& Job:: operator=(const Job& a) {
	this->s = a.s;
	this->t = a.t;
	this->p = a.p;
	this->id = a.id;
    this->w = a.w;
	return *this;
}


std::ostream& operator<<(std::ostream& out, const Job& a) {
	return out << "作业" <<a.id<< "，进入时间为" << a.s << "，实施时间为" << a.t << "，优先级为" << a.p;
}

int Job::end_time()
{
    this->e = this->s + this->w + this->t;
    return this->e;
}