#ifndef SQUARE_H
#define SQUARE_H

#include "defines.h"

class Square {	
public:
								Square();
								~Square();	
private:
	Square*						_parent; // parent Square
	int 						G; // Movement cost = parent cost + cost to move
	int							H; // Estimated cost to finish
	int							F; // G + H = total cost
};

#endif 
