#include "Timer.h"


Timer::Timer(){
	this->startTime = 0;
	this->endTime = 0;
}

void Timer::startTimer(){
	this->startTime = std::clock();
}

double Timer::currentTime(){
	double duration;

	this->endTime = std::clock();

	duration = (this->endTime - this->startTime) / (double)CLOCKS_PER_SEC;

	return duration;
}

double Timer::endTimer(){
	double duration;

	duration = this->currentTime();

	this->startTime = 0;
	this->endTime = 0;

	return duration;
}