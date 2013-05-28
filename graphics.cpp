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
	printf("\nClosing out the program.\n");
	for( int x = 0; x < MOUSE_BOX_WIDTH; x++ ) {
		for( int y = 0; y < MOUSE_BOX_HEIGHT; y++ ) {
			if( pt_grid[ x ][ y ] != NULL ) {
				printf("Attempting to delete pt_grid x: %d, y: %d\n", x, y );
				delete pt_grid[ x ][ y ];
				pt_grid[ x ][ y ] = NULL;
			}
		} 
	}

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
	SDL_ShowCursor( SDL_ENABLE );	

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

void Graphics::DrawText( std::string text, int value, Sint16 x, Sint16 y ) {
	SDL_Color textColor = { 0, 0, 0 };

	std::ostringstream textToBeDrawn;
	textToBeDrawn << text << value; 

	SDL_Surface* textSurface = TTF_RenderText_Solid( font, textToBeDrawn.str().c_str(), textColor );

	SDL_Rect location = { x, y, 0, 0 };

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

	// Draw open, closed, and blocked squares
	// empty = 0, open = 1, closed = 2, blocked = 3	
	for( int x = 0; x < MOUSE_BOX_WIDTH; x++ ) {
		for( int y = 0; y < MOUSE_BOX_HEIGHT; y++ ) {
			if( grid[ x ][ y ] == 3 ) {
				boxRGBA( Window, ( x * BOX_WIDTH ) + 5, ( y * BOX_HEIGHT ) + 5, ( x * BOX_WIDTH ) + BOX_WIDTH + 5, ( y * BOX_HEIGHT ) + BOX_HEIGHT + 5, 60, 60, 60, 255 );
			}
			else if( grid[ x ][ y ] >= 1 ) {
				boxRGBA( Window, ( x * BOX_WIDTH ) + 5, ( y * BOX_HEIGHT ) + 5, ( x * BOX_WIDTH ) + BOX_WIDTH + 5, ( y * BOX_HEIGHT ) + BOX_HEIGHT + 5, 210, 210, 210, 255 );
				DrawText( "F: ", pt_grid[ x ][ y ]->GetF(), ( x * BOX_WIDTH ) + 5, ( y * BOX_HEIGHT ) + 5 );
			}
		}
	}
	
	// Draw the Current Square - Green
	if( pt_grid[ currentX ][ currentY ] != NULL ) {
		boxRGBA( Window, ( currentX * BOX_WIDTH ) + 5, ( currentY * BOX_HEIGHT ) + 5, ( currentX * BOX_WIDTH ) + BOX_WIDTH + 5, ( currentY * BOX_HEIGHT ) + BOX_HEIGHT + 5, 60, 255, 60, 255 );
		DrawText( "F: ", pt_grid[ currentX ][ currentY ]->GetF(), ( currentX * BOX_WIDTH ) + 5, ( currentY * BOX_HEIGHT ) + 5 );
	}
	else {
		boxRGBA( Window, ( currentX * BOX_WIDTH ) + 5, ( currentY * BOX_HEIGHT ) + 5, ( currentX * BOX_WIDTH ) + BOX_WIDTH + 5, ( currentY * BOX_HEIGHT ) + BOX_HEIGHT + 5, 60, 255, 60, 255 );
	}
	
	// Draw the lines
	for( int i = 0; i <= MOUSE_BOX_WIDTH; i++ ) {
		lineRGBA( Window, ( i * BOX_WIDTH ) + 5, 0, ( i * BOX_WIDTH ) + 5, 360, 0, 230, 230, 255 );
	}

	for( int i = 0; i <= MOUSE_BOX_HEIGHT; i++ ) {
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

	if( x != currentX || y != currentY ) {
		printf("\nWent down findPath.\n\n");
		FindPath( currentX, currentY, x, y );
	}
	else {
		printf("\n");
		printf("Selected x and y. Plus the starting square.\n");
		printf("x = %d and y = %d\nCurrentX = %d\tCurrentY = %d\n", x, y, currentX, currentY );
		
	}
}
	
void Graphics::MouseRightDown() {
	printf("\nclearing grid and pt_grid.\n");
	for( int x = 0; x < MOUSE_BOX_WIDTH; x++ ) {
		for( int y = 0; y < MOUSE_BOX_HEIGHT; y++ ) {
			grid[ x ][ y ] = 0;
			if( pt_grid[ x ][ y ] != NULL ) {
				printf("Attempting to delete pt_grid x: %d, y: %d\n", x, y );
				delete pt_grid[ x ][ y ];
				pt_grid[ x ][ y ] = NULL;
			}
		} 
	}
	grid[3][1] = 3;	
	grid[3][2] = 3;	
	grid[3][3] = 3;	

	currentX = X_Start;
	currentY = Y_Start;
		
	printf("Finished resetting the simulation.\n");	
}

void Graphics::FindPath( int xInit, int yInit, int xDest, int yDest ) {
	MouseRightDown();

	currentX = xInit;
	currentY = yInit;

	// place holder for finding the lowest open node
	int lowestF = 1000;
	int lowestX = 0, lowestY = 0;

	// create a node containing the node_goal	
	destinationX = xDest;
	destinationY = yDest;

	// create a node containing the node_start
	// Square *node = new Square( NULL, 0, currentX, currentY, destinationX, destinationY );
	Square *node = new Square( NULL, 0, currentX, currentY, destinationX, destinationY );
	
	// put node on the openlist
	openList = 1;
	grid[currentX][currentY] = 1;	
	pt_grid[ currentX ][ currentY ] = node;

	printf("\nStarting a new A* search.\n");
	while( openList > 0 ) {
		// make	it automaticly pick the first open node
		// by giving it an unrealistic high number to beat
		lowestF = 1000;

		// get the node off the open list with the lowest F
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
		printf("Selected X:%d\tY:%d to be on lowest F:%d.\n", lowestX, lowestY, lowestF ); 

		// if current lowest node = return; Found the route		
		if( lowestX == xDest && lowestY == yDest ) {
			currentX = xDest;
			currentY = yDest;
			printf("*** Found the end. ***\n X: %d\tY: %d\n\n", lowestX, lowestY );
			return;
		}
		
		// generate more open nodes for the list in order
		// left, top left, top, top right, right, bottom right,
		// bottom, bottom left

		// left
		if( lowestX - 1 >= 0 ) {		
			if( grid[ lowestX - 1][ lowestY ] == 0 ) {
				printf("Making the left square at X:%d\tY:%d\n", lowestX - 1, lowestY );
				Square *node = new Square( NULL, 10 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX - 1, lowestY, destinationX, destinationY );	
				openList++;	
				grid[ lowestX - 1 ][ lowestY ] = 1;	
				pt_grid[ lowestX - 1 ][ lowestY ] = node;
			}
			else if( grid[ lowestX - 1 ][ lowestY ] == 1 ) {
				if( 10 + pt_grid[ lowestX ][ lowestY ]->GetG() < pt_grid[ lowestX - 1 ][ lowestY ]->GetG() ) {
					printf("Replacing the square at X:%d\tY:%d\n with a lower G Value", lowestX - 1, lowestY );
					delete pt_grid[ lowestX - 1 ][ lowestY ];
					Square *node = new Square( NULL, 10 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX - 1, lowestY, destinationX, destinationY );	
					pt_grid[ lowestX - 1 ][ lowestY ] = node;
				}
			}
		}

		// top left
		if( lowestY - 1 >= 0 && lowestX - 1 >= 0 ) {
			if( grid[ lowestX - 1][ lowestY - 1 ] == 0 ) {
				printf("Making the top left square at X:%d\tY:%d\n", lowestX - 1, lowestY - 1 );
				Square *node = new Square( NULL, 14 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX - 1, lowestY - 1, destinationX, destinationY );	
				openList++;	
				grid[ lowestX - 1 ][ lowestY - 1 ] = 1;	
				pt_grid[ lowestX - 1 ][ lowestY - 1 ] = node;
			}
			else if( grid[ lowestX - 1 ][ lowestY - 1 ] == 1 ) {
				if( 14 + pt_grid[ lowestX ][ lowestY ]->GetG() < pt_grid[ lowestX - 1 ][ lowestY - 1 ]->GetG() ) {
					printf("Replacing the square at X:%d\tY:%d\n with a lower G Value", lowestX - 1, lowestY - 1 );
					delete pt_grid[ lowestX - 1 ][ lowestY - 1 ];
					Square *node = new Square( NULL, 14 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX - 1, lowestY - 1, destinationX, destinationY );	
					pt_grid[ lowestX - 1 ][ lowestY - 1 ] = node;
				}
			}
		}

		// lower left
		if( lowestY + 1 < MOUSE_BOX_HEIGHT && lowestX - 1 >= 0 ) {
			if( grid[ lowestX - 1][ lowestY + 1 ] == 0 ) {
				printf("Making the lower left square at X:%d\tY:%d\n", lowestX - 1, lowestY + 1 );
				Square *node = new Square( NULL, 14 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX - 1, lowestY + 1, destinationX, destinationY );	
				openList++;	
				grid[ lowestX - 1 ][ lowestY + 1] = 1;	
				pt_grid[ lowestX - 1 ][ lowestY + 1] = node;
			}
			else if( grid[ lowestX - 1 ][ lowestY + 1 ] == 1 ) {
				if( 14 + pt_grid[ lowestX ][ lowestY ]->GetG() < pt_grid[ lowestX - 1 ][ lowestY + 1 ]->GetG() ) {
					printf("Replacing the square at X:%d\tY:%d\n with a lower G Value", lowestX -1, lowestY + 1 );
					delete pt_grid[ lowestX -1 ][ lowestY + 1 ];
					Square *node = new Square( NULL, 14 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX - 1, lowestY + 1, destinationX, destinationY );	
					pt_grid[ lowestX - 1 ][ lowestY + 1] = node;
				}
			}
		}

		// top
		if( lowestY - 1 >= 0 ) {
			if( grid[ lowestX ][ lowestY - 1 ] == 0 ) {
				printf("Making the top square at X:%d\tY:%d\n", lowestX, lowestY - 1 );
				Square *node = new Square( NULL, 10 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX, lowestY - 1, destinationX, destinationY );	
				openList++;	
				grid[ lowestX ][ lowestY - 1 ] = 1;	
				pt_grid[ lowestX ][ lowestY - 1 ] = node;
			}
			else if( grid[ lowestX ][ lowestY - 1 ] == 1 ) {
				if( 10 + pt_grid[ lowestX ][ lowestY ]->GetG() < pt_grid[ lowestX ][ lowestY - 1 ]->GetG() ) {
					printf("Replacing the square at X:%d\tY:%d\n with a lower G Value", lowestX, lowestY - 1 );
					delete pt_grid[ lowestX ][ lowestY - 1 ];
					Square *node = new Square( NULL, 10 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX, lowestY - 1, destinationX, destinationY );	
					pt_grid[ lowestX ][ lowestY - 1 ] = node;
				}
			}
		}

		// bottom
		if( lowestY + 1 < MOUSE_BOX_HEIGHT ) {
			if( grid[ lowestX ][ lowestY + 1 ] == 0 ) {
				printf("Making the bottom square at X:%d\tY:%d\n", lowestX, lowestY + 1 );
				Square *node = new Square( NULL, 10 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX, lowestY + 1, destinationX, destinationY );	
				openList++;	
				grid[ lowestX ][ lowestY + 1 ] = 1;	
				pt_grid[ lowestX ][ lowestY + 1 ] = node;
			}
			else if( grid[ lowestX ][ lowestY + 1 ] == 1 ) {
				if( 10 + pt_grid[ lowestX ][ lowestY ]->GetG() < pt_grid[ lowestX ][ lowestY + 1 ]->GetG() ) {
					printf("Replacing the square at X:%d\tY:%d with a lower G Value\n", lowestX, lowestY + 1 );
					delete pt_grid[ lowestX ][ lowestY + 1 ];
					Square *node = new Square( NULL, 10 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX, lowestY + 1, destinationX, destinationY );	
					pt_grid[ lowestX ][ lowestY + 1 ] = node;
				}
			}
		}

		// right
		if( lowestX + 1 < MOUSE_BOX_WIDTH ) {		
			if( grid[ lowestX + 1][ lowestY ] == 0 ) {
				printf("Making the right square at X:%d\tY:%d\n", lowestX + 1, lowestY );
				// Square *node = new Square( pt_grid[ lowestX ][ lowestY ], 10 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX + 1, lowestY, destinationX, destinationY );	
				Square *node = new Square( NULL, 10 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX + 1, lowestY, destinationX, destinationY );	
				openList++;	
				grid[ lowestX + 1 ][ lowestY ] = 1;	
				pt_grid[ lowestX + 1 ][ lowestY ] = node;
			}
			else if( grid[ lowestX + 1 ][ lowestY ] == 1 ) {
				if( 10 + pt_grid[ lowestX ][ lowestY ]->GetG() < pt_grid[ lowestX + 1 ][ lowestY ]->GetG() ) {
					printf("Replacing the square at X:%d\tY:%d with a lower G Value.\n", lowestX + 1, lowestY );
					delete pt_grid[ lowestX + 1 ][ lowestY ];
					Square *node = new Square( NULL, 10 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX + 1, lowestY, destinationX, destinationY );	
					pt_grid[ lowestX + 1 ][ lowestY ] = node;
				}
			}
		}

		// top right
		if( lowestY - 1 <= 0 && lowestX + 1 < MOUSE_BOX_HEIGHT ) {
			if( grid[ lowestX + 1][ lowestY - 1 ] == 0 ) {
				printf("Making the top right square at X:%d\tY:%d\n", lowestX + 1, lowestY - 1 );
				Square *node = new Square( NULL, 14 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX + 1, lowestY - 1, destinationX, destinationY );	
				openList++;	
				grid[ lowestX + 1 ][ lowestY - 1 ] = 1;	
				pt_grid[ lowestX + 1 ][ lowestY - 1 ] = node;
			}
			else if( grid[ lowestX + 1 ][ lowestY - 1 ] == 1 ) {
				if( 14 + pt_grid[ lowestX ][ lowestY ]->GetG() < pt_grid[ lowestX + 1 ][ lowestY - 1 ]->GetG() ) {
					printf("Replacing the square at X:%d\tY:%d with a lower G Value.\n", lowestX + 1, lowestY - 1 );
					delete pt_grid[ lowestX + 1 ][ lowestY - 1 ];
					Square *node = new Square( NULL, 14 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX + 1, lowestY - 1, destinationX, destinationY );	
					pt_grid[ lowestX + 1 ][ lowestY - 1 ] = node;
				}
			}
		}

		// lower right
		if( lowestY + 1 < MOUSE_BOX_HEIGHT && lowestX + 1 < MOUSE_BOX_WIDTH ) {
			if( grid[ lowestX + 1][ lowestY + 1 ] == 0 ) {
				printf("Making the lower right square at X:%d\tY:%d\n", lowestX + 1, lowestY + 1 );
				Square *node = new Square( NULL, 14 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX + 1, lowestY + 1, destinationX, destinationY );	
				openList++;	
				grid[ lowestX + 1 ][ lowestY + 1] = 1;	
				pt_grid[ lowestX + 1 ][ lowestY + 1] = node;
			}
			else if( grid[ lowestX + 1 ][ lowestY + 1 ] == 1 ) {
				if( 14 + pt_grid[ lowestX ][ lowestY ]->GetG() < pt_grid[ lowestX + 1 ][ lowestY + 1 ]->GetG() ) {
					printf("Replacing the square at X:%d\tY:%d with a lower G Value.\n", lowestX + 1, lowestY + 1 );
					delete pt_grid[ lowestX + 1 ][ lowestY + 1 ];
					Square *node = new Square( NULL, 14 + pt_grid[ lowestX ][ lowestY ]->GetG(), lowestX + 1, lowestY + 1, destinationX, destinationY );	
					pt_grid[ lowestX + 1 ][ lowestY + 1] = node;
				}
			}
		}

		// last... close the current node
		--openList;
		grid[ lowestX ][ lowestY ] = 2;
		printf("Removing X:%d\tY:%d from open list.\n", lowestX, lowestY );
		printf("Open list = %d\n", openList );
		printf("*******************************\n\n");
	}

	printf("\nNever found the ending node.\n");
}

void Graphics::HandleInput() {
	if( SDL_PollEvent( &event ) ) {
		if( event.type == SDL_QUIT ) {
			Running = false;
		}

		if( event.type == SDL_MOUSEBUTTONDOWN ) {
			if( event.button.button == SDL_BUTTON_LEFT ) {
				MouseLeftDown( event.button.x, event.button.y );
			}
			else if( event.button.button == SDL_BUTTON_RIGHT ) {
				MouseRightDown();
			}
		}

		if( event.type == SDL_MOUSEBUTTONUP ) {
			if( event.button.button == SDL_BUTTON_LEFT ) {
				// do nothing for now		
			}
		}

		if( event.type == SDL_KEYUP ) {
			if( event.key.keysym.sym == SDLK_ESCAPE ) {
				Running = false;
			}
		}
	}
}
