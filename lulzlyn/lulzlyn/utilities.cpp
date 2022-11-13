#include "utilities.hpp"

#include <vector>
#include <Windows.h>

#include <atlimage.h>
#include <comdef.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

#include "nyan.hpp"

static std::vector<std::uint8_t> pattern_to_byte(const char* pattern)
{
	std::vector<std::uint8_t> bytes = std::vector<std::uint8_t>();

	char* start = const_cast<char*>(pattern);
	char* end = const_cast<char*>(pattern) + std::strlen(pattern);

	for (char* current = start; current < end; current++)
	{
		if (*current == '?')
		{
			current++;

			if (*current == '?')
			{
				current++;
			}

			bytes.push_back(-1);
		}
		else
		{
			bytes.push_back(static_cast<std::uint8_t>(std::strtoul(current, &current, 16)));
		}
	}

	return bytes;
}

std::uintptr_t* utilities::pattern_scan(const char* module_name, const char* signature)
{
	HMODULE module_handle = GetModuleHandle(module_name);

	if (!module_handle)
	{
		return nullptr;
	}

	PIMAGE_DOS_HEADER dos_header = reinterpret_cast<PIMAGE_DOS_HEADER>(module_handle);
	PIMAGE_NT_HEADERS nt_headers = reinterpret_cast<PIMAGE_NT_HEADERS>(reinterpret_cast<std::uintptr_t>(module_handle) + dos_header->e_lfanew);

	unsigned long size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	std::vector<std::uint8_t> pattern_bytes = pattern_to_byte(signature);
	std::uintptr_t* image_base = reinterpret_cast<std::uintptr_t*>(module_handle);

	std::size_t pattern_size = pattern_bytes.size();
	std::uint8_t* array_of_bytes = pattern_bytes.data();

	for (unsigned long i = 0ul; i < size_of_image - pattern_size; i++)
	{
		bool found = true;

		for (unsigned long j = 0ul; j < pattern_size; ++j)
		{
			if (image_base[i + j] != array_of_bytes[j] && array_of_bytes[j] != -1)
			{
				found = false;
				break;
			}
		}

		if (found)
		{
			return &image_base[i];
		}
	}

	return nullptr;
}

HBITMAP utilities::load_bitmap()
{
	IStream* stream = SHCreateMemStream(nyan, static_cast<UINT>(sizeof(nyan)));

	IStreamPtr sp_stream{ stream, false };

	CImage img{};
	img.Load(sp_stream);

	return img.Detach();
}