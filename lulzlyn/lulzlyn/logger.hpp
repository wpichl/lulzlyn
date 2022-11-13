#pragma once

namespace logger
{
	typedef enum
	{
		ALERT,
		WARNING,
		FAILURE
	} log_type;

	void intialize(const char* title);
	void release();

	void log(logger::log_type type, const char* message...);
}