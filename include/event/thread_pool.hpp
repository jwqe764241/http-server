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
	
	std::mutex mutex;

	bool running;

public:
	thread_pool(int max_worker,int max_tasks)
		: workers(max_worker), tasks(max_tasks), running(true)
	{
		for(int i = 0; i < max_worker; ++i)
		{
			workers.push_back(std::thread(&thread_pool::processTask, this, i));
		}
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
				event& e = pool->pop_task();

				e.notify();
			}
		}
	}

	void stop()
	{
		{
			std::lock_guard<std::mutex> guard(this->mutex);
			running = false;
		}

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
		std::lock_guard<std::mutex> guard(this->mutex);
		return running;
	}

	bool is_task_empty()
	{
		std::lock_guard<std::mutex> guard(this->mutex);
		return tasks.empty();
	}

	bool is_task_full()
	{
		std::lock_guard<std::mutex> guard(this->mutex);
		return tasks.full();
	}

	void push_task(t_task task)
	{
		std::lock_guard<std::mutex> guard(this->mutex);
		tasks.enqueue(task);
	}

	t_task pop_task()
	{
		std::lock_guard<std::mutex> guard(this->mutex);
		return tasks.dequeue();
	}
};