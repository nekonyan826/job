#include"Generator.h"
#include"Platform.h"
int main(int argc, const char *artv[])   
{
	// Generator generator(10,1000,0.5,2);
	// Platform platform;
	// while(generator.check()||platform.check())
	// {
	// 	// std::cout<<generator.get_time()<<std::endl;
	// 	generator.add_time();
	// 	std::vector<Job> tmp_jobs;
	// 	if(generator.check())
	// 		tmp_jobs = generator.get_new_job();
	// 	platform.step(generator.get_time(),tmp_jobs);
	// 	// for(int i = 0;i<tmp_jobs.size();++i)
	// 	// {
	// 	// 	std::cout<<tmp_jobs[i]<<std::endl;
	// 	// }
	// }
	Platform platform;
	while (true)
	{
		int now_time,m;
		std::vector<Job> tmp_jobs;
		std::cin>>now_time>>m;
		// std::cout<<"ok";
		for(int i=0;i<m;++i)
		{
			int num,s,t;
			std::cin>>num>>s>>t;
			Job new_job(num,s,t);
			tmp_jobs.push_back(new_job);
			// std::cout<<num<<" "<<s<<" "<<t<<std::endl;
		} 
		platform.step(now_time,tmp_jobs);
		// std::cout<<"ok";
		platform.print();

		// for(int i = 0;i<tmp_jobs.size();++i)
		// {
		// 	std::cout<<tmp_jobs[i]<<std::endl;
		// }
		std::cout<<"ok";
		
	}
	
}