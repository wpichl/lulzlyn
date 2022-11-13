#include "hooks.hpp"
#include "logger.hpp"
#include "utilities.hpp"
#include "minhook/MinHook.h"

HBITMAP hooks::screenshot::nyanmap = nullptr;

hooks::screenshot::function_t screenshot_original = nullptr;
hooks::bitblit::function_t bitblit_original = nullptr;

bool hooks::initialize()
{
	if (MH_Initialize() != MH_OK)
	{
		logger::log(logger::log_type::FAILURE, "failed to initialize minhook");
		return false;
	}
	else
	{
		logger::log(logger::log_type::ALERT, "initialized minhook");
	}

	std::uint8_t* screenshot_target = utilities::pattern_scan(NULL, "41 57 41 56 41 54 56 57 53 48 83 EC ? 48 8B 05 ? ? ? ? 48 31 E0 48 89 44 24 ? 0F 28 05");

	hooks::screenshot::nyanmap = utilities::load_bitmap();

	if (!screenshot_target)
	{
		logger::log(logger::log_type::FAILURE, "failed to find signature");
		return false;
	}
	else
	{
		logger::log(logger::log_type::ALERT, "found signature");
	}

	if (MH_CreateHook(screenshot_target, &hooks::screenshot::hook, reinterpret_cast<void**>(&screenshot_original)) != MH_OK)
	{
		logger::log(logger::log_type::FAILURE, "failed to create screenshot hook");
		return false;
	}
	else
	{
		logger::log(logger::log_type::ALERT, "created screenshot hook");
	}

	if (MH_CreateHook(BitBlt, &hooks::bitblit::hook, reinterpret_cast<void**>(&bitblit_original)) != MH_OK)
	{
		logger::log(logger::log_type::FAILURE, "failed to create bitblt hook");
		return false;
	}
	else
	{
		logger::log(logger::log_type::ALERT, "created bitblt hook");
	}

	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
	{
		logger::log(logger::log_type::FAILURE, "failed to enable hooks");
		return false;
	}
	else
	{
		logger::log(logger::log_type::ALERT, "enabled hooks");
	}

	return true;
}

void hooks::release()
{
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);

	logger::log(logger::log_type::ALERT, "released hooks");
}

HBITMAP __fastcall hooks::screenshot::hook(HGDIOBJ unused)
{
	if (!hooks::screenshot::nyanmap)
	{
		return screenshot_original(unused);
	}

	logger::log(logger::log_type::ALERT, "denying screenshot request");

	return hooks::screenshot::nyanmap;
}

BOOL __stdcall hooks::bitblit::hook(HDC hdc, int x, int y, int cx, int cy, HDC hdc_src, int x1, int y1, DWORD rop)
{
	logger::log(logger::log_type::ALERT, "denying bitblt request");

	return FALSE;
}