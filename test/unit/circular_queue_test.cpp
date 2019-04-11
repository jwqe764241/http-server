#define __USE_MINGW_ANSI_STDIO 0
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "event/circular_queue.hpp"

TEST_CASE("cirqular queue i/o test", "[i/o test]")
{
	const int queue_size = 5;
	
	circular_queue<int> queue(queue_size);
	
	REQUIRE(queue.size() == queue_size);
	REQUIRE(queue.empty());
	
	queue.enqueue(1);
	queue.enqueue(2);
	queue.enqueue(3);
	
	REQUIRE_FALSE(queue.empty());
	REQUIRE_FALSE(queue.full());
	
	queue.enqueue(4);
	queue.enqueue(5);
	
	REQUIRE_FALSE(queue.empty());
	REQUIRE(queue.full());
	
	REQUIRE(queue.dequeue() == 1);
	
	REQUIRE_FALSE(queue.full());
	
	REQUIRE(queue.dequeue() == 2);
	REQUIRE(queue.dequeue() == 3);
	REQUIRE(queue.dequeue() == 4);
	REQUIRE(queue.dequeue() == 5);
	
	REQUIRE(queue.dequeue() == 0);
	
	REQUIRE(queue.empty());
	REQUIRE_FALSE(queue.full());
}