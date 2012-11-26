/*
 * Timer.h
 *
 *  Created on: 06.08.2012
 *      Author: dnb
 */

#ifndef TIMER_H_
#define TIMER_H_

class Timer {
private:
	int startTicks;
	int pausedTicks;

	bool started;
	bool paused;
public:
	Timer();
	virtual ~Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	int getTicks();

	bool isStarted();
	bool isPaused();
};

#endif /* TIMER_H_ */
