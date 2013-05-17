#include "graphics.h"

Graphics::Graphics() {
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_TIMER ) == -1 ) {
		printf( "SDL_Init failed: %s\n", SDL_GetError() );
	}
}

Graphics::~Graphics() {
	SDL_FreeSurface( Window );

	TTF_Quit();
	SDL_Quit();
}

void Graphics::Init( int windowWidth, int windowHeight, const char* caption ) {
	TTF_Init();
	Window = SDL_SetVideoMode( windowWidth, windowHeight, 0, SDL_HWSURFACE | SDL_DOUBLEBUF );
	
	if( Window == NULL ) {
		printf( "Window failed to set up correct.\n" );
	}
	
	SDL_WM_SetCaption( caption, 0 );
	
	printf( "Graphics were set up without issue.\n" );
	
	Running = true;
}

void Graphics::SetBackgroundColor( int red, int green, int blue ) {
	bgR = red;
	bgG = green;
	bgB = blue;
}

void Graphics::ClearScene() {
	SDL_FillRect( Window, NULL, SDL_MapRGB( Window->format, bgR, bgG, bgB ) );
}

void Graphics::DrawScene() {
	SDL_Flip( Window );
}

void Graphics::ShowFPS( int fps ) {
	TTF_Font* font = TTF_OpenFont( "arial.ttf", 12 );

	SDL_Color textColor = { 0, 0, 0 };

	SDL_Surface* textSurface = TTF_RenderText_Solid( font, "Average FPS.", textColor );

	SDL_Rect location = { 15, 15, 0, 0 };

	SDL_BlitSurface( textSurface, NULL, Window, &location );

	SDL_FreeSurface( textSurface ); 	
	TTF_CloseFont( font );
}
