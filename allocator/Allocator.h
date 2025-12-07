#pragma once
#include <cstdint>
#include <cstddef>

class Allocator 
{
public:
	Allocator(size_t size, std::byte* start) noexcept
	{
		_start = start;
		_size = size;
		_used_memory = 0;
		_num_allocations = 0;
	}

	virtual ~Allocator() 
	{
		__assume(_num_allocations == 0 && _used_memory == 0);
		_start = nullptr; _size = 0;
	}

	virtual std::byte* allocate(size_t size, std::uint8_t alignment = 4) = 0;
	virtual void deallocate(std::byte* p) = 0;
	std::byte* getStart() const { return _start; };
	size_t getSize() const { return _size; };
	size_t getUsedMemory() const { return _used_memory; };
	size_t getNumAllocations() const { return _num_allocations; };


protected:
	std::byte* _start;
	size_t _size;
	size_t _used_memory;
	size_t _num_allocations;
};

namespace allocator {

	template <class T> T* allocateNew(Allocator& allocator)
	{
		return new (allocator.allocate(sizeof(T), __alignof(T))) T;
	}
	
	template <class T> T* allocateNew(Allocator& allocator, const T& t)
	{
		return new (allocator.allocate(sizeof(T), __alignof(T))) T(t);
	}

	template <class T> void deallocateDelete(Allocator& allocator, T& object) noexcept
	{
		object.~T();
		allocator.deallocate(&object);
	}

	template <class T> T* allocateArray(Allocator& allocator, size_t length)
	{
		__assume(length != 0);

		uint8_t headerSize = sizeof(size_t) / sizeof(T);

		if (sizeof(size_t) % sizeof(T) > 0) headerSize += 1;

		T* p = ((T*)allocator.allocate(sizeof(T) * (length + headerSize), __alignof(T))) + headerSize;
		*(((size_t*)p) - 1) = length;

		for (size_t i = 0; i < length; i++)
			new (&p[i]) T;

		return p;
	}

	template <class T> void deallocateArray(Allocator& allocator, T* array) 
	{
		__assume(array != nullptr);

		size_t length = *(((size_t*)array) - 1);

		for (size_t i = 0; i < length; i++) array.~T();

		uint8_t headerSize = sizeof(size_t) / sizeof(T);
		
		if (sizeof(size_t) % sizeof(T) > 0) headerSize += 1;

		allocator.deallocate(array - headerSize);
	}
}