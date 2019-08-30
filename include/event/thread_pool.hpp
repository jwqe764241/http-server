#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "circular_queue.hpp"
#include "event.hpp"
#include "utils/logger.hpp"

/*
	thread pool
	process task with mant thread

	TODO: make container threadsafe
*/
template <typename t_task>
class thread_pool
{
private:
	std::vector<std::thread> workers;
	circular_queue<t_task> tasks;
	
	std::mutex task_mutex;
	std::mutex pool_mutex;

	bool running;

private:
	void join_all()
	{
		for(std::thread& worker : workers)
		{
			if(worker.joinable())
				worker.join();
		}
	}

public:
	thread_pool(int max_worker,int max_task)
		: workers(max_worker), tasks(max_task), running(true)
	{
		for(int i = 0; i < max_worker; ++i)
		{
			workers.push_back(std::thread(&thread_pool::processTask, this));
		}
	}

	virtual ~thread_pool()
	{
		stop();
	}

	static void processTask(thread_pool* pool)
	{
		logger logger(std::cout);

		while(pool->is_running())
		{
			try
			{
				if(!pool->is_task_empty())
				{
					auto task = pool->pop_task();

					if (task != nullptr)
						task->notify();
				}
			}
			catch (const std::exception& e)
			{
				logger.error(e.what());
			}
			
		}
	}

	void stop()
	{
		std::lock_guard<std::mutex> guard(this->task_mutex);
		running = false;

		join_all();
	}

	bool is_running()
	{
		std::lock_guard<std::mutex> guard(this->pool_mutex);
		return running;
	}

	bool is_task_empty()
	{
		std::lock_guard<std::mutex> guard(this->task_mutex);
		return tasks.empty();
	}

	bool is_task_full()
	{
		std::lock_guard<std::mutex> guard(this->task_mutex);
		return tasks.full();
	}

	void push_task(t_task task)
	{
		std::lock_guard<std::mutex> guard(this->task_mutex);
		
		try
		{
			tasks.enqueue(task);
		}
		catch (const std::exception& e)
		{
			throw e;
		}
	}

	t_task pop_task()
	{
		std::lock_guard<std::mutex> guard(this->task_mutex);
		try
		{
			return tasks.dequeue();
		}
		catch (const std::exception& e)
		{
			throw e;
		}
	}

	size_t get_worker_count()
	{
		return workers.size();
	}

	size_t get_max_task_count()
	{
		return tasks.size();
	}
};