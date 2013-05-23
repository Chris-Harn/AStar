#ifndef SQUARE_H
#define SQUARE_H

#include "defines.h"

class Square {	
public:
								Square();
								~Square();	
								Square( Square *parent, int GScore, int x, int y );
	int							getG();
	int							getF();
	int							getX();
	int							getY();
	int							estimateDistance( int xDest, int yDest );
private:
	Square*						_parent; // parent Square
	int 						G; // Movement cost = parent cost + cost to move
	int							H; // Estimated cost to finish
	int							F; // G + H = total cost
	int							xPos;
	int							yPos;
};

#endif 
