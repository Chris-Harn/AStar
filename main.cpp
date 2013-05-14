#include "defines.h"

SDL_Surface* g_Window = NULL;	// Window Surface
SDL_Event g_Event;				// SDL event for input
int g_Timer;					// Timer

void Init();
void Shutdown();

int main( int argc, char **argv ) {
	Init();

	// Start the fps counter
	int frame = 0;
	int g_Timer = SDL_GetTicks();

	bool RUNNING = true;

	while( RUNNING ) {
		if( SDL_PollEvent( &g_Event ) ) {
			// User x'd out the window
			if( g_Event.type == SDL_QUIT ) {
				RUNNING = false;
			}
		}

		++frame;
		// Calculate and show the frame rate
		if( SDL_GetTicks() - g_Timer > 1000 ) {
			std::stringstream caption;

			caption << "Average Frames Per Second: " << frame / ( g_Timer / 1000.f );
			SDL_WM_SetCaption( caption.str().c_str(), 0 );
			frame = 0;
			g_Timer = SDL_GetTicks();
		}
	}

	SDL_Flip( g_Window );
	// SDL_FillRect( g_Window, NULL, SDL_MapRGB( g_Window->format, 0, 0, 0, ) );
	
	Shutdown();

	return 0;
}

void Init() {
	SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER );

	g_Window = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	SDL_WM_SetCaption( WINDOW_CAPTION, 0 );

	g_Timer = SDL_GetTicks();
}

void Shutdown() {
	SDL_FreeSurface( g_Window );
	
	SDL_Quit();
}
