#pragma once
#include <string>
#include <vector>
#include <stack>

using namespace std;
class Leaf {
public:
	// Left signifies all those less than this, right is greater than this
	Leaf* left;
	Leaf* right;
	Leaf* parent;
	signed short int value;

	bool color; //B = False, R = True;

	Leaf();
	Leaf(signed short int);

	// Tree Operations
	Leaf* rotateRight();
	Leaf* rotateLeft();


	//~Leaf();
};

class RBtree {
private:
	Leaf* root;
	signed short int leaves;
	

public:
	void insert(signed short int);
	stack<signed short int> genStack(bool);
	RBtree(signed short int); 
};

