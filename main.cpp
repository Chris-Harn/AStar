#include "defines.h"
#include "graphics.h"
#include "timer.h"
#include "square.h"
#include "location.h"
#include "path.h"

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
	
	// SDL_ShowCursor( SDL_ENABLE );

	while( Engine.Running ) {
		TimePiece.StartTime();

		Engine.HandleInput();

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
