#include "timer.h"

Timer::Timer() {
	if( SDL_Init( SDL_INIT_TIMER ) == -1 ) {
		printf( "SDL_Init_Timer failed to initalize." );
	}
}

Timer::~Timer() { }

void Timer::StartTime() {
	timer = SDL_GetTicks();
}

int Timer::GetTime() {
	return SDL_GetTicks();
}

void Timer::SetFrameRate( int fps ) {
	if( fps <=  1 ) 
		frameRate = 1000;
	else
		frameRate = 1000 / fps;
}

bool Timer::IsItTime() {
	return ( SDL_GetTicks() - timer ) >= frameRate;
}

