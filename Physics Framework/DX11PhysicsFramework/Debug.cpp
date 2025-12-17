#include "Debug.h"


void Debug::PrintNumber(int _number)
{
	static int x = _number;

	char sz[1024] = { 0 };

	sprintf_s(sz, "the number is %d \n", x);

	OutputDebugStringA(sz);

	x++;
}