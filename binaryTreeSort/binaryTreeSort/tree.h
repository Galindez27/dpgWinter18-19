#pragma once
#include <string>
#include <vector>
#include <stack>

using namespace std;
class Branch {
public:
	// Left signifies all those less than this, right is greater than this
	Branch* left;
	Branch* right;
	Branch* parent;
	signed short int value;
	signed short int times;

	bool color; //B = False, R = True;
	bool root;

	Branch();
	Branch(signed short int);

	// Tree Operations
	Branch* rotateRight();
	Branch* rotateLeft();


	//~Branch();
};

class RBtree {
private:
	Branch* rootNode;
	signed short int depth;
	signed short int nodes;
	signed short int numInput;
	void balance(Branch*);
	void traverse(Branch*, stack<signed short int>*, bool*);

public:
	void insert(signed short int);
	stack<signed short int>* genStack(bool);
	RBtree(signed short int);
	signed short int getDepth();
	signed short int getNodes();
};

