#include "graphics.h"

Graphics::Graphics() {
	if( SDL_Init( SDL_INIT_VIDEO ) == -1 ) {
		printf( "SDL_Init_Video failed: %s\n", SDL_GetError() );
	}

	Window = NULL;
	font = NULL;
}

Graphics::~Graphics() {
	SDL_FreeSurface( Window );
	TTF_CloseFont( font );

	TTF_Quit();
	SDL_Quit();
}

void Graphics::Init( int windowWidth, int windowHeight, const char* caption ) {
	TTF_Init();
	// Window = SDL_SetVideoMode( windowWidth, windowHeight, 8, SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_FULLSCREEN );
	Window = SDL_SetVideoMode( windowWidth, windowHeight, 8, SDL_HWSURFACE | SDL_DOUBLEBUF );
	
	if( Window == NULL ) {
		printf( "Window failed to set up correct.\n" );
	}
	
	SDL_WM_SetCaption( caption, 0 );
	
	Running = true;

	// Optimizing and testing font
	font = TTF_OpenFont( "arial.ttf", 12 );
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
	SDL_Color textColor = { 0, 0, 0 };

	std::ostringstream text;
	text << fps << " FPS ";

	SDL_Surface* textSurface = TTF_RenderText_Solid( font, text.str().c_str(), textColor );

	SDL_Rect location = { 15, 15, 0, 0 };

	SDL_BlitSurface( textSurface, NULL, Window, &location );
	
	SDL_FreeSurface( textSurface ); 	
}

void Graphics::DrawSprite( SDL_Surface* spriteSurface, int srcX, int srcY, int dstX, int dstY, int width, int height ) {
	SDL_Rect spriteRect;
	spriteRect.x = srcX;
	spriteRect.y = srcY;
	spriteRect.w = width;
	spriteRect.h = height;

	SDL_Rect drawRect;
	drawRect.x = dstX;
	drawRect.y = dstY;
	drawRect.w = width;
	drawRect.h = height;

	SDL_BlitSurface( spriteSurface, &spriteRect , Window, &drawRect );
}

void Graphics::DrawBoard() {
	for( int i = 0; i < 8; i++ ) {
		lineRGBA( Window, ( i * BOX_WIDTH ) + 5, 0, ( i * BOX_WIDTH ) + 5, 360, 0, 230, 230, 255 );
	}

	for( int i = 0; i < 6; i++ ) {
		lineRGBA( Window, 0, ( i * BOX_HEIGHT ) + 5, 430, (i * BOX_HEIGHT ) + 5, 0, 230, 230, 255 );
	}
}

void Graphics::MouseLeftDown( int x, int y ) {
	if( x < 5 || x > 425 ) {
		printf("Outside X range.\n");
		return;
	}
	else if( y < 5 || y > 355 ) {
		printf("Outside Y range.\n");
		return;
	}

	x = x / BOX_WIDTH;
	y = y /  BOX_HEIGHT;

	printf("X: %d\tY: %d\n", x, y );
}

void Graphics::MouseRightDown() {
	for( int x = 0; x < MOUSE_BOX_WIDTH; x++ ) {
		for( int y = 0; y < MOUSE_BOX_HEIGHT; y++ ) {

		}
	}

	printf("Reset the simulation.\n");
	
}
