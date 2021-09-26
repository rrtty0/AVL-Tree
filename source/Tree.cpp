#include "stdafx.h"
#include "Tree.h"


Tree::Tree() : root(nullptr), offset(40), maxrow(8)
{
	screen = new char*[maxrow];
	for (int i = 0; i < maxrow; ++i)
		screen[i] = new char[80];
}


Tree::Tree(int v1, ...) : Tree()
{
	int *ptr = &v1;
	while (*ptr != -1)
	{
		add(*ptr);
		++ptr;
	}
}


Tree::Tree(const Tree& tree)
{
	root = copy(tree.root);
	offset = tree.offset;
	maxrow = tree.maxrow;
	screen = new char*[maxrow];
	for (int i = 0; i < maxrow; ++i)
	{
		screen[i] = new char[80];
		for (int j = 0; j < 80; ++j)
			screen[i][j] = tree.screen[i][j];
	}
}


Tree::Tree(Tree&& tree)
{
	root = tree.root;
	tree.root = nullptr;
	maxrow = tree.maxrow;
	offset = tree.offset;
	screen = tree.screen;
	tree.screen = nullptr;
	tree.maxrow = 0;
	tree.offset = 0;
}


Tree& Tree::operator=(const Tree& tree)
{
	if (this != &tree)
	{
		root = copy(tree.root);
		offset = tree.offset;
		maxrow = tree.maxrow;
		screen = new char*[maxrow];
		for (int i = 0; i < maxrow; ++i)
		{
			screen[i] = new char[80];
			for (int j = 0; j < 80; ++j)
				screen[i][j] = tree.screen[i][j];
		}
	}

	return *this;
}


Tree& Tree::operator=(Tree&& tree)
{
	if (this != &tree)
	{
		root = tree.root;
		tree.root = nullptr;
		maxrow = tree.maxrow;
		offset = tree.offset;
		screen = tree.screen;
		tree.screen = nullptr;
		tree.maxrow = 0;
		tree.offset = 0;
	}

	return *this;
}


Tree& Tree::operator&=(const Tree& tree)
{
	Tree cur(tree);
	vector<Node*> mustRemoved;

	logicAND(root, cur, mustRemoved);

	for (int i = 0; i < mustRemoved.size(); ++i)
		remove(mustRemoved[i]->value);

	return *this;
}


void Tree::logicAND(Node* current_node, Tree& tree, vector<Node*>& mustRemoved)
{
	if (current_node != nullptr)
	{
		if (!tree.contains(current_node->value))
			mustRemoved.push_back(current_node);
		logicAND(current_node->left, tree, mustRemoved);
		logicAND(current_node->right, tree, mustRemoved);
	}
}


Tree Tree::operator&(const Tree& tree) const
{
	Tree cur(*this);
	return (cur &= tree);
}


Tree& Tree::operator|=(const Tree& tree)
{
	vector<Node*> mustAdded;

	logicOR(tree.root, mustAdded);

	for (int i = 0; i < mustAdded.size(); ++i)
		add(mustAdded[i]->value);

	return *this;
}


void Tree::logicOR(Node* current_node, vector<Node*>& mustAdded)
{
	if (current_node != nullptr)
	{
		if (!contains(current_node->value))
			mustAdded.push_back(current_node);
		logicOR(current_node->left, mustAdded);
		logicOR(current_node->right, mustAdded);
	}
}


Tree Tree::operator|(const Tree& tree) const
{
	Tree cur(*this);
	return (cur |= tree);
}


Tree& Tree::operator+=(const Tree& tree)
{
	vector<Node*> mustRemoved;
	vector<Node*> mustAdded;

	logicPLUS(tree.root, mustRemoved, mustAdded);

	for (int i = 0; i < mustRemoved.size(); ++i)
		remove(mustRemoved[i]->value);

	for (int i = 0; i < mustAdded.size(); ++i)
		add(mustAdded[i]->value);

	return *this;
}


void Tree::logicPLUS(Node* current_node, vector<Node*>& mustRemoved, vector<Node*>& mustAdded)
{
	if (current_node != nullptr)
	{
		if (contains(current_node->value))
			mustRemoved.push_back(current_node);
		else
			mustAdded.push_back(current_node);
		logicPLUS(current_node->left, mustRemoved, mustAdded);
		logicPLUS(current_node->right, mustRemoved, mustAdded);
	}
}


Tree Tree::operator+(const Tree& tree) const
{
	Tree cur(*this);
	return (cur += tree);
}


Tree::~Tree()
{
	for (int i = 0; i < maxrow; ++i)
		delete[] screen[i];
	delete[] screen;
	delete root;
}


Node* Tree::copy(Node* current_node_copy)
{
	if (current_node_copy == nullptr)
		return nullptr;

	Node* current_node = new Node(current_node_copy->value);

	current_node->left = copy(current_node_copy->left);
	current_node->right = copy(current_node_copy->right);

	return current_node;
}


void Tree::add(int value)
{
	root = add(root, value);
}


Node* Tree::add(Node* current_node, int value)
{

	if (current_node == nullptr)
		return new Node(value);

	if (value > current_node->value)
		current_node->right = add(current_node->right, value);

	if (value < current_node->value)
		current_node->left = add(current_node->left, value);

	return rebalance(current_node);
}


Node* Tree::rebalance(Node* node)
{
	changeHeight(node);

	if (getBalance(node) == 2)
	{
		if (getBalance(node->right) == -1)
			node->right = rotateRight(node->right);
		return rotateLeft(node);
	}

	if (getBalance(node) == -2)
	{
		if (getBalance(node->left) == 1)
			node->left = rotateLeft(node->left);
		return rotateRight(node);
	}

	return node;
}


int Tree::changeHeight(Node* node)
{
	int leftHeight;
	int rightHeight;

	if (node == nullptr)
		return 0;

	leftHeight = node->left ? node->left->height : 0;
	rightHeight = node->right ? node->right->height : 0;

	node->height = (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;

	return node->height;
}


int Tree::getBalance(Node* node)
{
	int leftHeight;
	int rightHeight;
	
	if (node == nullptr)
		return 0;

	leftHeight = node->left ? node->left->height : 0;
	rightHeight = node->right ? node->right->height : 0;

	return rightHeight - leftHeight;
}


Node* Tree::rotateRight(Node* node)
{
	Node* q = node->left;
	node->left = q->right;
	q->right = node;
	changeHeight(node);
	changeHeight(q);

	return q;
}

Node* Tree::rotateLeft(Node* node)
{
	Node* q = node->right;
	node->right = q->left;
	q->left = node;
	changeHeight(node);
	changeHeight(q);

	return q;
}


void Tree::clrscr()
{
	for (int i = 0; i < maxrow; ++i)
		memset(screen[i], '-', 80);
}


void Tree::outNodes(Node* v, int r, int c)
{
	if (r && c && (c < 80))
		screen[r - 1][c - 1] = '0' + v->value;
	if (r < maxrow)
	{
		if (v->left)
			outNodes(v->left, r + 1, c - (offset >> r));
		if (v->right)
			outNodes(v->right, r + 1, c + (offset >> r));
	}
}


void Tree::printTree()
{
	clrscr();
	outNodes(root, 1, offset);
	for (int i = 0; i < maxrow; ++i)
	{
		screen[i][79] = '\0';
		cout << "\n" << screen[i];
	}
	cout << "\n";

}


void Tree::remove(int value)
{
	root = remove(root, value);
}


Node* Tree::remove(Node* current_node, int value)
{
	if (current_node == nullptr)
		return nullptr;

	if (value > current_node->value)
		current_node->right = remove(current_node->right, value);
	else
		if (value < current_node->value)
			current_node->left = remove(current_node->left, value);
		else
		{
			
			if (!current_node->right)
				return current_node->left;
			Node* rightMin = findRightMin(current_node->right);
			rightMin->right = removeRightMin(current_node->right);
			rightMin->left = current_node->left;
			return rebalance(rightMin);
		}

	return rebalance(current_node);
}


Node* Tree::findRightMin(Node* node)
{
	return node->left ? findRightMin(node->left) : node;
}


Node* Tree::removeRightMin(Node* node)
{
	if (node->left == nullptr)
		return node->right;
	node->left = removeRightMin(node->left);
	return rebalance(node);
}


bool Tree::contains(int value)
{
	return contains(root, value);
}


bool Tree::contains(Node* current_node, int value)
{
	if (current_node == nullptr)
		return false;

	if (current_node->value == value)
		return true;

	if (value > current_node->value)
		return contains(current_node->right, value);
	
	if (value < current_node->value)
		return contains(current_node->left, value);

}