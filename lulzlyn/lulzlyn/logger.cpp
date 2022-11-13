#include "logger.hpp"

#include <Windows.h>
#include <iostream>

void logger::intialize(const char* title)
{
	AllocConsole();

	freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(0)), "conin$", "r", static_cast<_iobuf*>(__acrt_iob_func(0)));
	freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(1)), "conout$", "w", static_cast<_iobuf*>(__acrt_iob_func(1)));
	freopen_s(reinterpret_cast<_iobuf**>(__acrt_iob_func(2)), "conout$", "w", static_cast<_iobuf*>(__acrt_iob_func(2)));

	SetConsoleTitleA(title);
}

void logger::release()
{
	fclose(static_cast<_iobuf*>(__acrt_iob_func(0)));
	fclose(static_cast<_iobuf*>(__acrt_iob_func(1)));
	fclose(static_cast<_iobuf*>(__acrt_iob_func(2)));

	FreeConsole();
}

void logger::log(logger::log_type type, const char* message...)
{
	switch (type)
	{
		case logger::ALERT:
			printf("[ alert ] -> ");
			break;

		case logger::WARNING:
			printf("[ warning ] -> ");
			break;

		case logger::FAILURE:
			printf("[ failure ] -> ");
			break;

		default:
			printf("[ unknown ] -> ");
			break;
	}

	printf(message);
	printf("\n");
}