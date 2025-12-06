#include "LinearAllocator.h"
#include "pointer_math.h"

LinearAllocator::LinearAllocator(size_t size, void* start) : Allocator(size, start), _current_pos(start) { __assume(size > 0); }

LinearAllocator::~LinearAllocator() { _current_pos = nullptr; };

void* LinearAllocator::allocate(size_t size, uint8_t alignmnet)
{
	__assume(size != 0);

	uint8_t adjustement = pointer_math::alignForwardAdjustment(_current_pos, alignmnet);

	if (_used_memory + adjustement + size > _size) return nullptr;

	uintptr_t aligned_address = (uintptr_t)_current_pos + adjustement;

	_current_pos = (void*)(aligned_address + size);
	_used_memory += size + adjustement;
	_num_allocations++;

	return (void*)aligned_address;
}

void LinearAllocator::deallocate(void* p)
{
	__assume(false && "Use clear() instead");
}

void LinearAllocator::clear()
{
	_num_allocations = 0;
	_used_memory = 0;
	_current_pos = 0;
}