#pragma once

#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

#include "producer.hpp"
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
	producer<t_task> task_producer;
	console_logger logger;
	std::mutex pool_mutex;

	bool running;

public:
	thread_pool(int max_worker,int max_task)
		: task_producer(max_task), running(true), logger(LEVEL::ALL)
	{
		for(int i = 0; i < max_worker; ++i)
		{
			workers.push_back(std::thread([&]() {
				while (!task_producer.isDone())
				{
					t_task task = task_producer.consume();

					try
					{
						task->notify();
					}
					catch (const std::runtime_error& e)
					{
						//...
					}
					catch (const std::exception& e)
					{
						this->logger.log(LEVEL::FATAL, e.what());
					}
				}
			}));
		}
	}

	virtual ~thread_pool()
	{
		stop();
	}

	void stop()
	{
		std::lock_guard<std::mutex> guard(this->pool_mutex);
		running = false;
		task_producer.close();
	}

	bool is_running()
	{
		std::lock_guard<std::mutex> guard(this->pool_mutex);
		return running;
	}

	bool is_task_empty()
	{
		return task_producer.empty();
	}

	bool is_task_full()
	{
		return task_producer.full();
	}

	void push_task(t_task task)
	{
		try
		{
			task_producer.push(task);
		}
		catch (const std::exception& e)
		{
			throw e;
		}
	}

	size_t get_max_task_count()
	{
		return task_producer.size();
	}
};