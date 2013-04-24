#include "../Math/Maths.h"
#include "tile.h"

class Node
{
public:
	tile t;
	Node *n;
	int c;
	int s;

	Node();
	Node(tile,Node*, int, int);
	~Node();

	int cost(){ return c + s; };
};