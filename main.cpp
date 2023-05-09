#include"Generator.h"
#include"Platform.h"
int main()
{
	Generator generator(10,1000,0.5,2);
	Platform platform;
	while(generator.check()||platform.check())
	{
		// std::cout<<generator.get_time()<<std::endl;
		generator.add_time();
		std::vector<Job> tmp_jobs;
		if(generator.check())
			tmp_jobs = generator.get_new_job();
		platform.step(generator.get_time(),tmp_jobs);
		// for(int i = 0;i<tmp_jobs.size();++i)
		// {
		// 	std::cout<<tmp_jobs[i]<<std::endl;
		// }
	}
}