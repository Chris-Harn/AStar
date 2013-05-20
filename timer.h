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
	bool					DelayTime(); // Returns true if it hasn't hit the framerate
	void					Delay(); // Delays the difference of DelayTime()
	Uint32					GetTicks();
private:
	Uint32					timer; // Timer for frame rate
	Uint32					frameRate; // frameRate = 1000 / fps
};

#endif
