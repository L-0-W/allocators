#pragma once

#include <iostream>

namespace pointer_math
{ 

inline uint8_t alignForwardAdjustment(const void* address, uint8_t alignment)
{
	uintptr_t adjustment = alignment - (reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(alignment - 1));

	if (adjustment == alignment) return 0;

	return adjustment;
}

}