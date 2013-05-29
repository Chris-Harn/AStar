#ifndef PATH_H
#define PATH_H

#include "location.h"

class Path {
public:
								Path();
								~Path();
	void						EmptyPath();
	void						AddLocation( int x, int y );
	
	Location					**nodes;
	int							numberOfNodes;
	int							maxNodes;
};

#endif
