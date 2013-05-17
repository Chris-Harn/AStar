#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"

class Graphics {	
public:
							Graphics();
							~Graphics();
	void					Init( int windowWidth, int windowHeight, const char* caption );
	void					SetBackgroundColor( int red, int green, int blue );
	void					ClearScene();
	void					DrawScene();
	bool					Running;
private:
	SDL_Surface* 			Window;

	// Background - Clear Screen Color
	int  					bgR;
	int						bgG;
	int						bgB;
};

#endif
