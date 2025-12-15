#pragma once
#include <chrono>

class Timer
{
public:
	Timer();

	float GetDeltaTime();
	void Tick();

private:
	std::chrono::steady_clock::time_point m_lastFrame;
};