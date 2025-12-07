#include "AllocatorMy.h"
#include <iostream>
#include <print>


struct ent
{
	int x{ 0 }, y{ 0 };
};

int main()
{

	LinearAllocatorMy linear_allocator = allocators::linear::init(1024);

	auto result_linear = linear_allocator.allocate<int>(1);
	auto result_linear2 = linear_allocator.allocate<int>(1);
	auto result_linear3 = linear_allocator.allocate<int>(1);


	std::println("Alocando em: {}", (void*)result_linear);
	std::println("Alocando em: {}", (void*)result_linear2);
	std::println("Alocando em: {}", (void*)result_linear3);

	std::println("Limpando...");
	linear_allocator.clear();

	auto result_linear4 = linear_allocator.allocate<int>(1);
	std::println("Alocando em: {}", (void*)result_linear4);

	return 0;
}