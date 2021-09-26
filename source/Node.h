#pragma once
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include <iostream>
using namespace std;


class Node
{
private:
	int value;    //value at node
	Node* left;   //left child
	Node* right;  //right child
	int height;   //number of nodes at tree, where this node is root

	Node();       //constructor without arguments

public:
	Node(int);    //constructor with argument(int value)
	~Node();      //constructor without arguments


	friend class Tree;
};

