#pragma once

#include <vector>
#include <thread>
#include <mutex>

#include "circular_queue.hpp"
#include "event.hpp"



/*
	thread pool
	process task with mant thread

	TODO: need mutex
*/
template <typename t_task>
class thread_pool
{
private:
	std::vector<std::thread> workers;
	circular_queue<t_task> tasks;
	
	bool running;

public:
	thread_pool(int max_worker,int max_tasks)
		: workers(max_worker), tasks(max_tasks), running(true)
	{
		load_worker(max_worker);
	}

	virtual ~thread_pool()
	{
		stop();
	}

	static void processTask(thread_pool* pool, int number)
	{
		while(pool->is_running())
		{
			if(!pool->is_task_empty())
			{
				event e = pool->pop_task();
				e.notify();
			}
		}
	}

	void load_worker(int max_worker)
	{
		for(int i = 0; i < max_worker; ++i)
		{
			workers.push_back(std::thread(&thread_pool::processTask, this, i));
		}
	}

	void stop()
	{
		running = false;

		join_all();
	}

	void join_all()
	{
		for(std::thread& worker : workers)
		{
			if(worker.joinable())
				worker.join();
		}
	}

	bool is_running()
	{
		return running;
	}

	bool is_task_empty()
	{
		return tasks.empty();
	}

	void push_task(t_task task)
	{
		tasks.enqueue(task);
	}

	t_task pop_task()
	{
		return tasks.dequeue();
	}
};