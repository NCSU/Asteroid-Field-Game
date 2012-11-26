/*
 * Timer.cpp
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#include "SDL/SDL.h"

#include "Timer.h"

Timer::Timer() {
	// TODO Auto-generated constructor stub
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

Timer::~Timer() {
	// TODO Auto-generated destructor stub
}

void Timer::start() {
	started = true;
	paused = false;

	startTicks = SDL_GetTicks();
}

void Timer::stop() {
	started = false;
	paused = false;
}

int Timer::getTicks() {
	if(started) {
		if(paused) {
			//Return the number of ticks when the timer was paused.
			return pausedTicks;
		}
		else {
			//Return the current time minus the start time
			return SDL_GetTicks() - startTicks;
		}
	}
	//If the timer not running.
	return 0;
}

void Timer::pause() {
	//If the timer is running.
    if(started && !paused) {
    	paused = true;
    	//Calculate the paused ticks
    	pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause() {
	//If the timer is paused
	if(paused) { //Unpause the timer
		paused = false;
		//Reset the starting ticks
		startTicks = SDL_GetTicks() - pausedTicks;
		//Reset the paused ticks
		pausedTicks = 0;
	}
}

bool Timer::isStarted() {
	return started;
}

bool Timer::isPaused() {
	return paused;
}
