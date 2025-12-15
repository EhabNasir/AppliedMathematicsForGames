#include "Timer.h"

Timer::Timer()
{
	m_lastFrame = std::chrono::steady_clock::now();
}

float Timer::GetDeltaTime()
{
	auto now = std::chrono::steady_clock::now();
	std::chrono::duration<float> delta = now - m_lastFrame;

	float deltaTime = delta.count();

	return deltaTime;
}

void Timer::Tick()
{
	m_lastFrame = std::chrono::steady_clock::now();
}