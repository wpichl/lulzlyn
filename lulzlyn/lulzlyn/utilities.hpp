#pragma once

#include <cstdint>
#include <Windows.h>

namespace utilities
{
	std::uintptr_t* pattern_scan(const char* module_name, const char* signature);
	HBITMAP load_bitmap();
}