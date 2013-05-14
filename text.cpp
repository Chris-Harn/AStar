#include "text.h"

Text::Text() {
	TTF_Init();
	font = TTF_OpenFont( "arial.ttf", 12 );
	foregroundColor = { 255, 255, 255 };
	backgroundColor = { 0, 0, 255 };
}

/*
void 	Text::drawText() {
	textSurface = TTF_Render_Text_Shaded( font, " ", foregroundColor, backgroundColor );
	textLocation = { 10, 10, 0, 0, };
	SDL_BlitSurface( textSurface, NULL, screen, &textLocation );	
}
*/

Text::~Text() {
	TTF_CloseFont( font );
	SDL_FreeSurface( textSurface );
	TTF_Quit();
}
