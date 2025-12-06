#pragma once

#include "Allocator.h"

class LinearAllocator : public Allocator
{
public:
	LinearAllocator(size_t size, void* start);
	~LinearAllocator();

	void* allocate(size_t size, uint8_t alignment) override;
	void deallocate(void* p) override;
	void clear();

private:

	LinearAllocator(const LinearAllocator&);

	LinearAllocator& operator=(const LinearAllocator&);
	void* _current_pos;
};