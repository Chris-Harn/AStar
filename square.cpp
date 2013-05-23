#include "square.h"

Square::Square() {
	_parent = NULL;
	G = 0;
	H = 0;
	F = 0;
	xPos = 0;
	yPos = 0;
}

Square::~Square() {
 	if( _parent != NULL ) {
		delete _parent;
	}
}

Square::Square( Square* parent, int GScore, int x, int y ) {
	_parent = parent;
	G = GScore;

	xPos = x;
	yPos = y;
	
	// Use heurestic to figured out H
	H = 10;

	F = G + H;
}

int Square::getG() {
	return G;
}

int Square::getF() {
	return F;
}
