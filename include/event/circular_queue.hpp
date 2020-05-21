#pragma once

#include <iostream>
#include <array>
#include <exception>
#include <mutex>


/*
	circular queue
*/
template <typename t_type>
class circular_queue
{
private:
	/*
		use modulo operation to check bound
		so, add one more space in container
	*/
	std::vector<t_type> container;

	int size;
	int front;
	int rear;

	std::mutex mutex;

public:

	circular_queue(int size)
		: front(0), rear(0), size(size), container(size + 1)
	{
	}

	~circular_queue()
	{
	}

	void enqueue(t_type element)
	{
		if(!full())
		{
			std::lock_guard<std::mutex> guard(mutex);

			container[rear] = element;
			rear = (rear + 1) % container.size();
		}
		else
		{
			throw std::runtime_error("cannnot enqueue element : queue is full");
		}
	}

	t_type dequeue()
	{
		if(!empty())
		{
			std::lock_guard<std::mutex> guard(mutex);

			int temp_pos = front;
			front = (front + 1) % container.size();

			return std::move(container[temp_pos]); 
		}
		else
		{
			throw std::runtime_error("cannnot dequeue element : queue is empty");
		}
	}

	bool empty()
	{
		std::lock_guard<std::mutex> guard(mutex);

		return front == rear;
	}

	bool full()
	{
		std::lock_guard<std::mutex> guard(mutex);

		return ((rear + 1) % container.size()) == front;
	}

	int get_size()
	{
		std::lock_guard<std::mutex> guard(mutex);

		return size;
	}

	std::vector<t_type> get_container()
	{
		return container;
	}
};