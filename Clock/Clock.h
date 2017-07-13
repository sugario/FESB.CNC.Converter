#pragma once

#include <chrono>

class Clock {
public:
	Clock();

	void Start(void);
	double ElapsedSeconds(void);

private:
	std::chrono::time_point<std::chrono::system_clock> StartTime;
};
