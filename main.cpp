#include "defines.h"
#include "graphics.h"
// #include "timer.h"

int main( int argc, char **argv ) {
	Graphics Engine;
	Engine.Init( WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_CAPTION );
	Engine.SetBackgroundColor( 0, 255, 255 );
	Engine.ClearScene();

	SDL_Event event;

	while( Engine.Running ) {
		if( SDL_PollEvent( &event ) ) {
			if( event.type == SDL_QUIT ) {
				Engine.Running = false;
			}
		}

		Engine.DrawScene();
	}

	return 0;
}	
