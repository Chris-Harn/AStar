#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class Timer {
public:
							Timer();
							~Timer();
	void					StartTime(); // Start/reset timer
	int						GetTime(); // Return SDL_GetTicks
	void			 		SetFrameRate( int fps ); 
	bool					IsItTime();	 // Returns true if it has hit the framerate
private:
	int						timer; // Timer for frame rate
	int						frameRate; // frameRate = 1000 / fps
};

#endif
