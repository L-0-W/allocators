#pragma once

#include <cstddef>
#include <cstdlib>
#include <cstdint>
#include <iostream>

class AllocatorMy
{
protected:
	std::byte* _start;
	std::byte* _current_pos;
	size_t _size;
public:

	AllocatorMy(size_t size) : _size(size)
	{
		_start = reinterpret_cast<std::byte*>(std::malloc(size));
		_current_pos = _start;

		if (_start == nullptr) throw std::bad_alloc();
	};
	
	~AllocatorMy()
	{
		std::free(_start);
		_start = nullptr;
		_current_pos = nullptr;
		_size = 0;
	}
	
	template <typename T>
	std::byte* allocate(size_t size);

	void deallocate();

	size_t freeMemory();
};

class LinearAllocatorMy : public AllocatorMy
{
public:

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

	void deallocate()
	{
		std::cout << "Use Clear" << "\n";
	}

	size_t freeMemory()
	{
		return _size - static_cast<size_t>(_current_pos - _start);
	}
};

class StackAllocatorMy : public AllocatorMy
{
public:
	size_t _last_aloc;
	size_t aloc_amount;

	std::byte* allocate(size_t size)
	{
		if (size > this->freeMemory())
			return nullptr;

		if (aloc_amount == 0)
		{
			aloc_amount++;
			_last_aloc += size;
			return _current_pos;
		}

		_last_aloc += size;
		_current_pos += size;
	
		aloc_amount++;
		return _current_pos;
	}

	
	std::byte* marker()
	{
		return _current_pos;
	};


	void deallocate(std::byte* marker)
	{
		_current_pos = marker;
	}

	std::byte* current_pos()
	{
		return _current_pos;
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

	namespace stack
	{
		StackAllocatorMy init(size_t size)
		{
			return StackAllocatorMy{ size };
		}
	}

}
