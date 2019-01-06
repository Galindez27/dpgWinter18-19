#include "pch.h"

Branch::Branch() {
	left = NULL;
	right = NULL;
	parent = NULL;
	value = SHRT_MIN;
	times = 1;
	color = false;
	root = false;
}

Branch::Branch(signed short int val) {
	left = NULL;
	right = NULL;
	parent = NULL;
	value = val;
	times = 1;
	color = false;
	root = false;
}

Branch* Branch::rotateLeft() {
	/*Perform a left rotation rooted at this Branch. Returns
	the pivot Branch. See https://en.wikipedia.org/wiki/Tree_rotation for a better
	diagram/explanation*/
	Branch* piv = this->right; 
	this->right = piv->left;
	piv->left = this;
	return piv;
}

Branch* Branch::rotateRight() {
	/*Perform a right rotation rooted at this Branch. Returns
	the pivot Branch.	See https://en.wikipedia.org/wiki/Tree_rotation for a better
	diagram/explanation*/
	Branch* piv = this->left;
	this->left = piv->right;
	piv->right = this;
	return piv;
}




//Branch::~Branch() {
	//TODO add true RB deleting to maintain balance
//}

RBtree::RBtree(signed short int r) {
	rootNode = new Branch(r);
	depth = 1;
	nodes = 1;
	numInput = 1;
}

void RBtree::balance(Branch* curNode) {

	if (curNode->root) { 
		curNode->color = false;
		return;
	}

	//Parent is black 
	else if (!curNode->parent->color) {
		return;
	}

	//Parent and Uncle are red 1 (parent is a left child)
	else if ((curNode->parent->parent->left == curNode->parent) && curNode->parent->parent->right->color) {
		curNode->parent->color = false;
		curNode->parent->parent->right->color = false;
		curNode->parent->parent->color = true;
		balance(curNode->parent->parent);
	}

	//Parent and Uncle are Red 2 (parent is a right child)
	else if ((curNode->parent->parent->right == curNode->parent) && curNode->parent->parent->left->color) {
		curNode->parent->color = false;
		curNode->parent->parent->left->color = false;
		curNode->parent->parent->color = true;
		balance(curNode->parent->parent);
	}

	//Parent is Red and Uncle is Black
	else {
		Branch* grandparent = curNode->parent->parent;
		//First, the cur node must be moved to the "outside" or edge of the grandparent tree if it is there
		//curNode is Left Right from Grandparent
		if (grandparent->left == curNode->parent && curNode == curNode->parent->right) {
			curNode->parent->rotateLeft();
			curNode = curNode->left;
		}
		
		//curNode is Right Left from Grandparent
		else if (grandparent->right == curNode->parent && curNode == curNode->parent->left) {
			curNode->parent->rotateRight();
			curNode = curNode->right;
		}

		//Now that curNode is certain to be an edge, a rotation on the parent is performend and recolor parent and gp
		if (curNode == curNode->parent->left)
			grandparent->rotateRight();
		else
			grandparent->rotateLeft();
		curNode->parent->color = false;
		grandparent->color = true;
	}
}

void RBtree::insert(signed short int val) {
	numInput++;
	Branch* current = rootNode;
	signed short int newD = 1;

	//Standard BST Insert
	while (true) {
		if (current == NULL) {
			Branch* temp = new Branch(val);
			current->color = true;
			nodes++;
			break;
		}
		else if (val < current->value) {
			current = current->left;
			newD++;
		}
		else if (val > current->value) {
			current = current->right;
			newD++;
		}
		else {
			current->times++;
			return;
		}
	}
	if (newD > depth)
		depth = newD;


	//Balance algo
	balance(current);
}

signed short int RBtree::getDepth() {
	return depth;
}
signed short int RBtree::getNodes() {
	return nodes;
 }

void RBtree::traverse(Branch* curNode, stack<signed short int>* tobuild, bool* instruct) {
	/* traverse the tree recursivley and build the stack according to the intructed way.
	True = least to greatest (all left branches first then right)
	False = greatest to least (all right branches first then left.
	I.E: if true, the last element of the stack will be the lowest value.*/
	if (!*instruct) {
		if (curNode->left != NULL) {
			traverse(curNode->left, tobuild, instruct);
		}
		for (int x = 0; x < curNode->times; x++)
			tobuild->push(curNode->value);
		if (curNode->right != NULL) {
			traverse(curNode->right, tobuild, instruct);
		}
		return;
	}
	else {
		if (curNode->right != NULL) {
			traverse(curNode->right, tobuild, instruct);
		}
		for (int x = 0; x < curNode->times; x++)
			tobuild->push(curNode->value);
		if (curNode->left != NULL) {
			traverse(curNode->left, tobuild, instruct);
		}
		return;
	}
}

stack<signed short int>* RBtree::genStack(bool leastToGreatest) {
	stack<signed short int>* toReturn = new stack<signed short int>;
	traverse(rootNode, toReturn, &leastToGreatest);
	return toReturn;
}