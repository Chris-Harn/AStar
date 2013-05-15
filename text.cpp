#include "text.h"

Text::Text() {
	TTF_Init();
	font = TTF_OpenFont( "arial.ttf", 12 );
	foregroundColor = { 255, 255, 255 };
	backgroundColor = { 0, 0, 255 };
}

Text::~Text() {
	TTF_CloseFont( font );
	SDL_FreeSurface( textSurface );
	TTF_Quit();
}

void Text::drawText( SDL_Surface* surface, std::string text, int x, int y ) {
	textSurface = TTF_Render_Text_Shaded( font, text, foregroundColor, backgroundColor );
	textLocation = { x, y, 0, 0, };
	SDL_BlitSurface( textSurface, NULL, surface, &textLocation );	
}

void Text::drawFPS( SDL_Surface* surface, float fps ) {
	textSurface = TTF_Render_Text_Shaded( font, "Average Frames Per Second: " + fps, foregroundColor, backgroundColor );
	textLocation = { 10, 10, 0, 0 };
	SDL_BlitSurface( textSurface, NULL, surface, &textLocation );
}
