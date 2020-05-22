#pragma once

#include <mutex>
#include <iostream>
#include <condition_variable>

#include "circular_queue.hpp"


template<typename T>
class producer
{
private:
	std::thread runner;
	circular_queue<T> queue;
	std::mutex m;
	std::condition_variable cond_var;
	bool done = false;
	bool notified = false;

public:
	producer(int size)
		: queue(size)
	{
		runner = std::thread([&]() {
			while (!done)
			{
				if (!queue.empty())
				{
					notified = true;
					cond_var.notify_one();
				}
			}
			});
	}

	~producer()
	{
	}

	void push(T value)
	{
		//lock은 어차피 circular_queue에 구현이 되어있음
		try
		{
			queue.enqueue(value);
		}
		catch (const std::exception& e)
		{
			//full 상태가 아닐때까지 notify 하여 꺼내가도록 함
			while (!done && queue.full())
			{
			}
			queue.enqueue(value);
		}
	}

	T consume()
	{
		std::unique_lock<std::mutex> lock(m);

		cond_var.wait(lock, [&] { return notified || done; });

		while (queue.empty())
		{
			if (done)
				return 0;
		}

		T value = queue.dequeue();
		notified = false;
		return std::move(value);
	}

	bool empty()
	{
		return queue.empty();
	}

	void close()
	{
		done = true;
		notified = true;
		cond_var.notify_all();
		runner.join();
	}

	bool isDone()
	{
		return done;
	}
};