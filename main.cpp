#include "defines.h"
#include "graphics.h"
#include "timer.h"
#include "square.h"

int main( int argc, char **argv ) {
	// Setup graphics engine
	Graphics Engine;
	Engine.Init( WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_CAPTION );
	Engine.SetBackgroundColor( 225, 225, 225 );

	// Setup timers
	Timer TimePiece;
	TimePiece.SetFrameRate( FRAMERATE );

	Timer FPSTimer;
	FPSTimer.SetFrameRate( 1 );
	FPSTimer.StartTime();

	int frame = 0;
	int currentFPS = 0;
	
	SDL_Event event;
	SDL_ShowCursor( SDL_ENABLE );

	while( Engine.Running ) {
		TimePiece.StartTime();
		
		if( SDL_PollEvent( &event ) ) {
			if( event.type == SDL_QUIT ) {
				Engine.Running = false;
			}

			if( event.type == SDL_MOUSEBUTTONDOWN ) {
				if( event.button.button == SDL_BUTTON_LEFT ) {	
					Engine.MouseLeftDown( event.button.x, event.button.y );	
				}
				else if( event.button.button == SDL_BUTTON_RIGHT ) {
					Engine.MouseRightDown();
				}
			}

			if( event.type == SDL_MOUSEBUTTONUP ) {
				if( event.button.button == SDL_BUTTON_LEFT ) {

				}
			}
	
			if( event.type == SDL_KEYUP ) {
				if( event.key.keysym.sym == SDLK_ESCAPE ) {
					Engine.Running = false;
				}
			}
		}




		if( FPSTimer.IsItTime() ) {
			currentFPS = (int) ( frame / ( FPSTimer.GetTicks() / 1000.f ) ); 
			FPSTimer.StartTime();
			frame = 0;
		}
				
		++frame;		
		Engine.ClearScene();	
		Engine.DrawBoard();
		Engine.ShowFPS( currentFPS );
		Engine.DrawScene();

		/*
		// Cap the frame rate
		if( TimePiece.DelayTime() ) {
			TimePiece.Delay();
		}
		*/
	}
		
	return 0;
}	
