#include "node.h"

// Node class for A* search

Node::Node(){
	c = -1;
}

Node::Node(tile x, Node *next, int cost, int steps){
	t = x;
	n = next;
	c = cost;
	s = steps;
}

Node::~Node(){
	delete n;
}