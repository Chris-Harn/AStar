#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "defines.h"
#include "squares.h"

class Graphics {	
public:
							Graphics();
							~Graphics();
	void					Init( int windowWidth, int windowHeight, const char* caption );
	void					SetBackgroundColor( int red, int green, int blue );
	void					ClearScene();
	void					DrawScene();
	void					ShowFPS( int fps );
	bool					Running;	
	void					DrawSprite( SDL_Surface* spriteSurface, int srcX, int srcY, int dstX, int dstY, int width, int height );
	void					DrawBoard();
	void					MouseLeftDown( int x, int y );
	void 					MouseRightDown();
private:
	SDL_Surface* 			Window;
	TTF_Font*				font;
	// empty = 0, open = 1, closed = 2, blocked = 3
	int						grid[MOUSE_BOX_WIDTH][MOUSE_BOX_HEIGHT];

	// Background - Clear Screen Color
	int  					bgR;
	int						bgG;
	int						bgB;
};

#endif
