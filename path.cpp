#include "path.h"

Path::Path() {
	maxNodes = 10;	
	nodes = new Card*[ maxNodes ];
	numberOfNodes = 0;
}

Path::~Path() {
	for( int i = 0; i < numberOfNodes; i++ ) {
		delete nodes[ i ];
	}

	delete[] nodes;
	nodes = NULL;
}

void Path::EmptyPath() {
	return;
}

void Path::AddLocation( int x, int y ) {
	if( x < 0 || y < 0 ) {
		printf("X: %d\tY: %d was incorrectly tried to add to the Location list.\n");
		return;
	}

	if( ( numberOfNodes + 1 ) > maxNodes ) {
		maxNodes += 10;
		Location **newnodes = new Location*[ maxNodes ];
		for( int location = 0; location < numberOfNodes; location++ ) {
			newnodes[ location ] = nodes[ location ];
			delete nodes[ location ];
		}

		delete[] nodes;
		nodes = newnodes;
	}

	Location loc = new Location( x, y );
	nodes[ numberOfNodes ] = loc;
	++numberOfNodes;
}
