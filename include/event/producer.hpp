#pragma once

#include <mutex>
#include <iostream>
#include <condition_variable>

#include <event/circular_queue.hpp>


template<typename T>
class producer
{
private:
	circular_queue<T> queue;
	std::mutex m;
	std::condition_variable cond_var;
	bool done = false;
	bool notified = false;

public:
	producer(int size)
		: queue(size)
	{
	}

	~producer()
	{
	}

	void push(T value)
	{
		std::unique_lock<std::mutex> lock(m);
		
		try
		{
			queue.enqueue(value);
		}
		catch (const std::exception & e)
		{
			//full 상태가 아닐때까지 notify 하여 꺼내가도록 함
			while (queue.full())
			{
				lock.unlock();
				notified = true;
				cond_var.notify_one();
				lock.lock();
			}
			queue.enqueue(value);
		}
		notified = true;
		cond_var.notify_one();
	}

	template<typename C> void consume(C consumer)
	{
		std::unique_lock<std::mutex> lock(m);

		while (!done)
		{
			cond_var.wait(lock, [&] { return notified || done; });

			while (!queue.empty())
			{
				consumer(queue.dequeue());
			}

			notified = false;
		}
	}

	void close()
	{
		done = true;
		notified = true;
		cond_var.notify_all();
	}

	bool empty()
	{
		return queue.empty();
	}

	bool full()
	{
		return queue.full();
	}

	size_t size()
	{
		return queue.get_size();
	}
};

