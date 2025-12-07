#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <iostream>



class LinearAllocatorMy
{
private:
	std::byte* _start;
	std::byte* _current_pos;
	size_t _size;
public:

	LinearAllocatorMy(size_t size) : _size(size)
	{
		_start = reinterpret_cast<std::byte*>(std::malloc(size));
		_current_pos = _start;

		if (_start == nullptr) throw std::bad_alloc();
	}

	~LinearAllocatorMy()
	{
		std::free(_start);
		_start = nullptr;
		_current_pos = nullptr;
		_size = 0;
	}


	template <typename T>
	std::byte* allocate(T struct_, size_t size)
	{

		if ((sizeof(struct_)*size) > this->freeMemory())
			return nullptr;
		

		std::byte* allocated_adrs = _current_pos;

		_current_pos += (sizeof(struct_)*size);

		return allocated_adrs;
	}

	template <typename T>
	std::byte* allocate(size_t size)
	{
		if ((sizeof(T) * size) > this->freeMemory())
			return nullptr;

		std::byte* allocate_addrs = _current_pos;

		_current_pos += (sizeof(T) * size);
	
		
		return allocate_addrs;
	}

	void clear()
	{
		_current_pos = _start;
	}

	size_t freeMemory()
	{
		return _size - static_cast<size_t>(_current_pos - _start);
	}
};

namespace allocators 
{
	
	namespace linear
	{
		LinearAllocatorMy init(size_t size)
		{
			return LinearAllocatorMy{ size };
		}
	}
}