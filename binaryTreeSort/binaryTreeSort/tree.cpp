#include "pch.h"

Branch::Branch() {
	left = NULL;
	right = NULL;
	parent = NULL;
	value = SHRT_MIN;
	times = 1;
	color = false;
}

Branch::Branch(signed short int val) {
	left = NULL;
	right = NULL;
	parent = NULL;
	value = val;
	times = 1;
	color = false;
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
	root = new Branch(r);
}

void RBtree::balance(Branch*) {

}

void RBtree::insert(signed short int val) {
	numInput++;
	Branch* current = root;
	//Standard BST Insert
	while (true) {
		if (current == NULL) {
			current = new Branch(val);
			break;
		}
		else if (val < current->value) {
			current = current->left;
		}
		else if (val > current->value) {
			current = current->right;
		}
		else {
			current->times++;
			break;
		}
	}
}

