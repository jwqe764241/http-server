#pragma once

#include <vector>
#include <thread>

class thread_group
{
private:
	std::vector<std::thread *> container;

public:
	thread_group()
	{
	}
	virtual ~thread_group()
	{
		for(auto& thread : container) 
		{
			delete thread;
		}
	};

	thread_group(const thread_group&) = delete;
	thread_group& operator=(const thread_group&) = delete;

	template<typename F>
	std::thread* create_thread(F thread_func)
	{
		std::thread* thread = new std::thread(thread_func);
		container.push_back(thread);

		return thread;
	}

	void add_thread(std::thread* thread)
	{
		container.push_back(thread);
	}

	void join_all()
	{
		for(auto& thread : container)
		{
			if(thread->joinable())
				thread->join();
		}
	}
};