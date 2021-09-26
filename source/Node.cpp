#include "Node.h"


Node::Node() : left(nullptr), right(nullptr), height(1)
{
}


Node::Node(int v) : left(nullptr), right(nullptr), height(1), value(v)
{
}


Node::~Node()
{
	if (left)
		delete left;
	if (right)
		delete right;
}
