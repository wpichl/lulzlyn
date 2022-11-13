#pragma once

#include <Windows.h>

namespace hooks
{
	bool initialize();
	void release();

	namespace screenshot
	{
		using function_t = HBITMAP(__fastcall*)(HGDIOBJ);
		HBITMAP __fastcall hook(HGDIOBJ unused);
		extern HBITMAP nyanmap;
	}

	namespace bitblit
	{
		using function_t = BOOL(__stdcall*)(HDC hdc, int x, int y, int cx, int cy, HDC hdc_src, int x1, int y1, DWORD rop);
		BOOL __stdcall hook(HDC hdc, int x, int y, int cx, int cy, HDC hdc_src, int x1, int y1, DWORD rop);
	}
}