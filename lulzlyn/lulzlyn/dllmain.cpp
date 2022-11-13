#include <Windows.h>
#include <thread>
#include <chrono>

#include "logger.hpp"
#include "hooks.hpp"

unsigned long __stdcall initialize(void* instance)
{
	logger::intialize("lulzlyn");

	if (!hooks::initialize())
	{
		logger::release();
		FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
		return FALSE;
	}
	 
	while (!GetAsyncKeyState(VK_END))
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	hooks::release();
	logger::release();

	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);

	return TRUE;
}

std::int32_t __stdcall DllMain(HINSTANCE instance, unsigned long call_reason, void* reserved)
{
	switch (call_reason)
	{
		case DLL_PROCESS_ATTACH:
			if (HANDLE handle = CreateThread(nullptr, NULL, initialize, instance, NULL, nullptr))
			{
				CloseHandle(handle);
			}
			break;

		case DLL_THREAD_ATTACH:

			break;

		case DLL_THREAD_DETACH:

			break;

		case DLL_PROCESS_DETACH:

			break;

		default:

			break;
	}

	return TRUE;
}