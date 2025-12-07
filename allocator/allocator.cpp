#include "AllocatorMy.h"
#include <iostream>
#include <print>
#include <cstdlib>

void* ptrs[20];

struct ent
{
	int x{ 0 }, y{ 0 };
};

int main()
{
	StackAllocatorMy allocator = allocators::stack::init(1024 * 1024);

	auto ptr = allocator.allocate(1024);
	std::cout << allocator.freeMemory() << "\n";
 
	auto marker = allocator.marker();
	
	auto ptr2 = allocator.allocate(1024);
	auto ptr3 = allocator.allocate(1024);

	std::cout << allocator.freeMemory() << "\n";

	allocator.deallocate(marker);

	std::cout << allocator.freeMemory() << "\n";


	return 0;
}