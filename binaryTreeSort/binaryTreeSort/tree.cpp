#include "pch.h"

Leaf::Leaf() {
	left = NULL;
	right = NULL;
	parent = NULL;
	value = SHRT_MIN;
}

Leaf::Leaf(signed short int val) {
	left = NULL;
	right = NULL;
	parent = NULL;
	value = val;
}

Leaf* Leaf::rotateLeft() {
	/*Perform a left rotation rooted at this leaf. Returns
	the pivot leaf. See https://en.wikipedia.org/wiki/Tree_rotation for a better
	diagram/explanation*/
	Leaf* piv = this->right; 
	this->right = piv->left;
	piv->left = this;
	return piv;
}

Leaf* Leaf::rotateRight() {
	/*Perform a right rotation rooted at this leaf. Returns
	the pivot leaf.	See https://en.wikipedia.org/wiki/Tree_rotation for a better
	diagram/explanation*/
	Leaf* piv = this->left;
	this->left = piv->right;
	piv->right = this;
	return piv;
}




//Leaf::~Leaf() {
	//TODO add true RB deleting to maintain balance
//}

RBtree::RBtree(signed short int r) {
	root = new Leaf(r);
}

RBtree::