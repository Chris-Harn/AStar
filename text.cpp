#include "text.h"	

Text::Text() {
	TTF_Init();
	font = TTF_OpenFont( "arial.ttf", 12 );
	foregroundColor = { 255, 255, 255 };
	backgroundColor = { 0, 0, 255 };
	textSurface = NULL;
	textLocation = { 10, 10, 0, 0 };
}

Text::~Text() {
	TTF_CloseFont( font );
	TTF_Quit();
	SDL_FreeSurface( textSurface );
}

void Text::drawText( SDL_Surface* surface, char* text, const short int x, const short int y ) {
	textSurface = TTF_RenderText_Shaded( font, text, foregroundColor, backgroundColor );
	textLocation = { x, y, 0, 0, };
	SDL_BlitSurface( textSurface, NULL, surface, &textLocation );	
}

void Text::drawFPS( SDL_Surface* surface, float fps ) {
	char averageFPS[40] = { "Average Frames Per Second: " };
	sprintf( averageFPS, "%d", (int) fps );
	textSurface = TTF_RenderText_Shaded( font, averageFPS, foregroundColor, backgroundColor );
	textLocation = { 10, 10, 0, 0 };
	SDL_BlitSurface( textSurface, NULL, surface, &textLocation );
}
