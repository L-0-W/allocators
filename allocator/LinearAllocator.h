#pragma once

#include "Allocator.h"
#include <cstddef>

class LinearAllocator : public Allocator
{
public:
	LinearAllocator(size_t size, std::byte* start) ;
	~LinearAllocator() noexcept;

	std::byte* allocate(size_t size, uint8_t alignment) override;
	void deallocate(std::byte* p) override;
	void clear() noexcept;

private:

	LinearAllocator(const LinearAllocator&) = delete;
	LinearAllocator& operator=(const LinearAllocator&) = delete;


	std::byte* _current_pos;
};