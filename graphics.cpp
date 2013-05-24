#include "graphics.h"

Graphics::Graphics() {
	if( SDL_Init( SDL_INIT_VIDEO ) == -1 ) {
		printf( "SDL_Init_Video failed: %s\n", SDL_GetError() );
	}

	Window = NULL;
	font = NULL;

	// Set up board: 0 = empty, 1 = open list, 2 = closed list, 3 = blocked
	for( int x = 0; x < MOUSE_BOX_WIDTH; x++ ) {
		for( int y = 0; y < MOUSE_BOX_HEIGHT; y++ ) {
			grid[ x ][ y ] = 0;
			pt_grid[ x ][ y ] = NULL;
		}
	}

	grid[3][1] = 3;	
	grid[3][2] = 3;	
	grid[3][3] = 3;	

	currentX = X_Start;
	currentY = Y_Start;
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
	for( int i = 0; i < MOUSE_BOX_WIDTH; i++ ) {
		lineRGBA( Window, ( i * BOX_WIDTH ) + 5, 0, ( i * BOX_WIDTH ) + 5, 360, 0, 230, 230, 255 );
	}

	for( int i = 0; i < MOUSE_BOX_HEIGHT; i++ ) {
		lineRGBA( Window, 0, ( i * BOX_HEIGHT ) + 5, 430, (i * BOX_HEIGHT ) + 5, 0, 230, 230, 255 );
	}

	// empty = 0, open = 1, closed = 2, blocked = 3	
	for( int x = 0; x < MOUSE_BOX_WIDTH; x++ ) {
		for( int y = 0; y < MOUSE_BOX_HEIGHT; y++ ) {
			if( grid[ x ][ y ] == 3 ) {
				boxRGBA( Window, ( x * BOX_WIDTH ) + 5, ( y * BOX_HEIGHT ) + 5, ( x * BOX_WIDTH ) + BOX_WIDTH + 5, ( y * BOX_HEIGHT ) + BOX_HEIGHT + 5, 60, 60, 60, 255 );
			}
		}
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

	printf("X: %d\tY: %d\tValue == %d\n", x, y, grid[x][y] );

	if( x != currentX && y != currentY ) {
		findPath( currentX, currentY, x, y );
	}
}

void Graphics::MouseRightDown() {
	for( int x = 0; x < MOUSE_BOX_WIDTH; x++ ) {
		for( int y = 0; y < MOUSE_BOX_HEIGHT; y++ ) {
			grid[ x ][ y ] = 0;
			delete pt_grid[ x ][ y ];
			pt_grid[ x ][ y ] = NULL;
		}
	}
	grid[3][1] = 3;	
	grid[3][2] = 3;	
	grid[3][3] = 3;	
	
	currentX = X_Start;
	currentY = Y_Start;
		
	printf("Reset the simulation.\n");	
}

void Graphics::findPath( int xInit, int yInit, int xDest, int yDest ) {
	currentX = xInit;
	currentY = yInit;

	for( int x = 0; x < MOUSE_BOX_WIDTH; x++ ) {
		for( int y = 0; y < MOUSE_BOX_HEIGHT; y++ ) {
			grid[ x ][ y ] = 0;
			delete pt_grid[ x ][ y ];
			pt_grid[ x ][ y ] = NULL;
		}
	}
	grid[3][1] = 3;	
	grid[3][2] = 3;	
	grid[3][3] = 3;	

	// place holder for finding the lowest open node
	int lowestF = 90;
	int lowestX = 3, lowestY = 3;

	// create a node containing the node_goal	
	destinationX = xDest;
	destinationY = yDest;

	// create a node containing the node_start
	Square *start = new Square( NULL, 0, currentX, currentY, destinationX, destinationY );
		
	// put node on the openlist
	openList = 1;	
	grid[currentX][currentY] = 1;	
	pt_grid[ currentX ][ currentY ] = start;

	while( openList > 0 ) {
		// Get the node off the open list with the lowest F
		for( int x = 0; x < MOUSE_BOX_WIDTH; x++ ) {
			for( int y = 0; y < MOUSE_BOX_HEIGHT; y++ ) {
				if( grid[ x ][ y ] == 1 ) {
					if( pt_grid[ x ][ y ]->GetF() <= lowestF ) {
						lowestF = pt_grid[ x ][ y ]->GetF();
						lowestX = pt_grid[ x ][ y ]->GetX();
						lowestY = pt_grid[ x ][ y ]->GetY();
					}
				}
			}
		}

		// if current lowest node = return; Found the route
		if( lowestX == xDest && lowestY == yDest ) {
			printf("*** Found the end. ***\n\n");
			return;
		}
		
		// generate more open nodes for the list


	
		// last... close the current node
		--openList;
		grid[ lowestX ][ lowestY ] = 2;
	}
}
