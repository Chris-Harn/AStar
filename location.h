#ifndef LOCATION_H
#define LOCATION_H

#include "defines.h"

class Location {
public:
						Location();
						Location( Uint8 xLoc, Uint8 yLoc );
						~Location();
	Uint8				x;
	Uint8				y;
};

#endif
