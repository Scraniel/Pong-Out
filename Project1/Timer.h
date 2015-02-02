#pragma once
#include <ctime>

// A simple class that helps time events. Run startTimer() to start,
// then run endTimer() to get (in seconds)  how long it's been since
// the timer started. To reset, just run startTimer() again or run
// endTimer()
class Timer{
	std::clock_t startTime, endTime;
public:
	Timer();
	// Starts the timer
	void startTimer();
	// Returns the how long has passed since the timer started
	double currentTime();
	// Returns how long has passed since the timer started, and resets
	// the timer to 0
	double endTimer();
};

