#pragma once
#include <string>
#include <Windows.h>
#include <stdio.h>

class Debug
{
public:
	static void PrintNumber(int _number);

	static int VDebugPrintF(const char* _format, va_list _args)
	{
		const UINT32 maxChar = 1024;
		static char s_buffer[maxChar];

		int charsWritten = vsnprintf(s_buffer, maxChar, _format, _args);
		OutputDebugStringA(s_buffer);

		return charsWritten;
	}

	static int PrintArguments(const char* _format, ...)
	{
		va_list argList;
		va_start(argList, _format);

		int charWritten = VDebugPrintF(_format, argList);
		va_end(argList);

		return charWritten;
	}
};

