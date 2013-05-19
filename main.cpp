#include "defines.h"
#include "graphics.h"
#include "timer.h"

int main( int argc, char **argv ) {
	// Setup graphics engine
	Graphics Engine;
	Engine.Init( WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_CAPTION );
	Engine.SetBackgroundColor( 0, 255, 255 );

	// Setup timers
	Timer TimePiece;
	TimePiece.SetFrameRate( 30 );
	TimePiece.StartTime();

	Timer FPSTimer;
	FPSTimer.SetFrameRate( 1 );
	FPSTimer.StartTime();

	int frame = 0;
	int currentFPS = 0;
	
	SDL_Event event;

	while( Engine.Running ) {
		++frame;		
	
		if( TimePiece.IsItTime() ) {
			if( SDL_PollEvent( &event ) ) {
				if( event.type == SDL_QUIT ) {
					Engine.Running = false;
				}
			}

			if( event.type == SDL_KEYUP ) {
				if( event.key.keysym.sym == SDLK_ESCAPE ) {
					Engine.Running = false;
				}
			}

			TimePiece.StartTime();
		}	
		
		if( FPSTimer.IsItTime() ) {
			currentFPS = (int) ( frame / ( FPSTimer.GetTime() / 1000.f ) ); 
			FPSTimer.StartTime();
			frame = 0;
			
			// printf("Current FPS is %i.\n", currentFPS );
			/*
			std::stringstream caption;
			caption << "Average Frames Per Second: " << currentFPS;
			SDL_WM_SetCaption( caption.str().c_str(), NULL );
			*/
		}
		
		Engine.ClearScene();
		Engine.ShowFPS( currentFPS );
		Engine.DrawScene();
	}

	return 0;
}	
