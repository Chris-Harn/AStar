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
		_parent = NULL;
	}
}

Square::Square( Square* parent, int GScore, int x, int y, int xDest, int yDest ) {
	_parent = parent;
	G = GScore;

	xPos = x;
	yPos = y;
	
	// Use heurestic to figured out H
	H = EstimateDistance( xDest, yDest );

	F = G + H;
}

int Square::GetG() {
	return G;
}

int Square::GetF() {
	return F;
}

int Square::GetH() {
	return H;
}

int Square::GetX() {
	return xPos;
}

int Square::GetY() {
	return yPos;
}

void Square::UpdateDestination( int xDest, int yDest ) {
	H = EstimateDistance( xDest, yDest );
	F = G + H;
}

int Square::EstimateDistance( int xDest, int yDest ) {
	int xd, yd;
	xd = xDest - xPos;
	yd = yDest - yPos;

	// Manhattan distance
	// return( abs(xd) + abs(yd) ) * 10;

	// Euclidian Distance
	return ( (int) (sqrt( xd * xd + yd * yd ) ) * 10 );	
}

Square* Square::ReturnParent() {
	return _parent;
}
