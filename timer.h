#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class Timer {
public:
							Timer();
							~Timer();
	void					StartTime();
	int						GetTime();
	void					SetFrameRate( int fps );
	
private:
	bool					running;
	int						timer;
	int						frameRate;
};

#endif
