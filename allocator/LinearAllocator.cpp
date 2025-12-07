#include "LinearAllocator.h"
#include "pointer_math.h"

LinearAllocator::LinearAllocator(size_t size, std::byte* start) : Allocator(size, start), _current_pos(start) { __assume(size > 0); }

LinearAllocator::~LinearAllocator() noexcept { _current_pos = nullptr; } ;

std::byte* LinearAllocator::allocate(size_t size, uint8_t alignmnet)
{
	__assume(size != 0);

	std::uint8_t adjustement = pointer_math::alignForwardAdjustment(_current_pos, alignmnet);

	if (_used_memory + adjustement + size > _size) return nullptr;

	std::uintptr_t _current_addrs = reinterpret_cast<std::uintptr_t>(_current_pos);
	std::uintptr_t aligned_address = _current_addrs + adjustement;

	_current_pos = reinterpret_cast<std::byte*>(aligned_address + size);
	_used_memory += size + adjustement;
	_num_allocations++;

	return reinterpret_cast<std::byte*>(aligned_address);
}

void LinearAllocator::deallocate(std::byte* p) 
{
	__assume(false && "Use clear() instead");
}

void LinearAllocator::clear() noexcept
{
	_num_allocations = 0;
	_used_memory = 0;
	_current_pos = 0;
}