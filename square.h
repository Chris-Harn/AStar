#ifndef SQUARE_H
#define SQUARE_H

#include "defines.h"

class Square {
public:
								Square();	
								~Square();	
								Square( Square *parent, int GScore, int xInit, int yInit, int xDest, int yDest );
								// G equal distance traveled
								// H equal remaining estimated distance
								// F = G + H
	int							GetG();
	int							GetF();
	int							GetH();
	int							GetX();
	int							GetY();
	void						UpdateDestination( int xDest, int yDest );
	int							EstimateDistance( int xDest, int yDest );
	Square						*ReturnParent();
private:
	Square						*_parent; // parent Square
	int 						G; // Movement cost = parent cost + cost to move
	int							H; // Estimated cost to finish
	int							F; // G + H = total cost
	int							xPos;
	int							yPos;
};

#endif 
