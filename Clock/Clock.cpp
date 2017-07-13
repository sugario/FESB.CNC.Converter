#include "Clock.h"

Clock::Clock()
{
	this->Start();
}

void Clock::Start(void)
{
	StartTime = std::chrono::system_clock::now();
}

double Clock::ElapsedSeconds(void)
{
	std::chrono::time_point<std::chrono::system_clock> CurrentTime;
	CurrentTime = std::chrono::system_clock::now();

	std::chrono::duration<double> elapsed_seconds = CurrentTime - StartTime;

	return elapsed_seconds.count();
}
