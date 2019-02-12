#pragma once

#include <iostream>
#include <array>

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

	int front;
	int rear;

public:

	circular_queue(int max_size)
		: front(0), rear(0), container(max_size + 1)
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
		return container.size() - 1;
	}

	std::vector<t_type> get_container()
	{
		return container;
	}
};