#include "square.h"

Square::Square() {
	_parent = NULL;
	G = 0;
	H = 0;
	F = 0;
}

Square::~Square() {
 	if( _parent != NULL ) {
		delete _parent;
	}
}

Square::Square( Square* parent, int GScore ) {
	_parent = parent;
	G = GScore;
	
	// Use heurestic to figured out H
	H = 10;

	F = G + H;
}
