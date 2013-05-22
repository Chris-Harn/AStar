#ifndef SQUARE_H
#define SQUARE_H

#include "defines.h"

class Square {	
public:
								Square();
								~Square();	
private:
	Square*						parent; // parent Square
	int 						G; // Movement cost = parent cost + cost to move
	int							H; // Estimated cost to finish
};

#endif 
