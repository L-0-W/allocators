#include "LinearAllocator.h"
#include "Allocator.h"

#include <iostream>

int main()
{
	char buffer[90];
	LinearAllocator la{ 90, buffer};


	auto abcd = allocator::allocateArray<int>(la, 8);
	auto age = allocator::allocateNew<int>(la);

	abcd[0] = 5;
	*age = 25;


	std::cout << "Endereço: "  << abcd << "\n" << "Valor: " << abcd[0] << "\n";
	std::cout << "Endereço: " << age << "\n" << "Valor: " << *age << "\n";



	return 0;
}