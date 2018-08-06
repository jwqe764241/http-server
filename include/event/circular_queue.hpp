#pragma once

#include <iostream>
#include <array>

template <typename t_type, int t_size>
class circular_queue
{
private:
	/*
		use modulo operation to check bound
		so, add one more space in container
	*/
	std::array<t_type, t_size + 1> container;

public:
	int front;
	int rear;

	circular_queue()
		: front(0), rear(0), container()
	{
	}

	~circular_queue()
	{
	}

	void enqueue(t_type element)
	{
		if(!full())
		{
			container[rear] = element;
			rear = (rear + 1) % container.size();
		}
	}

	t_type dequeue()
	{
		if(!empty())
		{
			int temp_pos = front;
			front = (front + 1) % container.size();

			return container[temp_pos];
		}
	}

	bool empty()
	{
		return front == rear;
	}

	bool full()
	{
		return ((rear + 1) % container.size()) == front;
	}

	size_t size()
	{
		/*
			return size with -1 because container size added one more
		*/
		return container.size() -1;
	}

	std::array<t_type, t_size + 1> getArray()
	{
		return container;
	}
};