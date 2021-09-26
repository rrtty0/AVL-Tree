#include "Node.h"


class Tree
{
private:
	Node * root;      //root of Tree
	int maxrow,       //max depth
		offset;       //offset from the root
	char **screen;    //screen memory

	Node* copy(Node*);                                     //make copy of this tree
	Node* add(Node*, int);                                 //add element to tree(recursion)
	Node* remove(Node*, int);                              //delete element from tree(recursion)
	bool contains(Node*, int);                             //check availability of element in Tree(recursion)
	int changeHeight(Node*);                               //change height of this node
	int getBalance(Node*);                                 //balance of this node
	Node* rebalance(Node*);                                //change balance of this node
	Node* rotateRight(Node*);                              //right turn around the node
	Node* rotateLeft(Node*);                               //left turn around the node
	Node* findRightMin(Node*);                             //find min element in right tree of deleted element
	Node* removeRightMin(Node*);                           //delete min element in right tree of deleted element
	void clrscr();                                         //array initialization to issue a tree to the screen
	void outNodes(Node* v, int r, int c);                  //output node
	void logicAND(Node*, Tree&, vector<Node*>&);           //logic AND
	void logicOR(Node*, vector<Node*>&);                   //logic OR
	void logicPLUS(Node*, vector<Node*>&, vector<Node*>&); //logic +


public:
	Tree();                             //constructor with out arguments
	Tree(vector<int> arr);              //constructor with elements
	Tree(const Tree&);                  //constructor of copy
	Tree(Tree&&);                       //constructor with move
	Tree& operator=(const Tree&);       //= with copy
	Tree& operator=(Tree&&);            //= with move
	Tree& operator&=(const Tree&);      //operator &= for Tree
	Tree operator&(const Tree&) const;  //operator & for Tree
	Tree& operator|=(const Tree&);      //operator |= for Tree
	Tree operator|(const Tree&) const;  //operator | for Tree
	Tree& operator+=(const Tree&);      //operator += for Tree(additional with mod 2)
	Tree operator+(const Tree&) const;  //operator + for Tree(additional with mod 2)
	~Tree();                            //destructor without arguments

	void add(int);                     //add element to Tree
	void remove(int);                  //delete element from table
	bool contains(int);                //check availability of element in Tree
	void printTree();                  //print Tree on screen
};

