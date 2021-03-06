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
	if (this->root) {
		this->root = false;
		piv->root = true;
	}
	this->right = piv->left;
	piv->left = this;
	piv->parent = this->parent;
	this->parent = piv;

	//Change the reference within the parent to the pivot
	if (piv->root)
		return piv;
	else if (piv->parent->left == this)
		piv->parent->left = piv;
	else
		piv->parent->right = piv;
	return piv;
}

Branch* Branch::rotateRight() {
	/*Perform a right rotation rooted at this Branch. Returns
	the pivot Branch.	See https://en.wikipedia.org/wiki/Tree_rotation for a better
	diagram/explanation*/

	Branch* piv = this->left;
	if (this->root) {
		this->root = false;
		piv->root = true;
	}
	this->left = piv->right;
	piv->right = this;
	piv->parent = this->parent;
	this->parent = piv;

	//Change reference within the parent to the pivot
	if (piv->root)
		return piv;
	else if (piv->parent->left == this)
		piv->parent->left = piv;
	else
		piv->parent->right = piv;
	return piv;
}




//Branch::~Branch() {
	//TODO add true RB deleting to maintain balance
//}

RBtree::RBtree(signed short int r) {
	rootNode = new Branch(r);
	rootNode->color = false;
	rootNode->root = true;
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

	//If either of the two children of the parent is NULL (and therefore a black node) the two cases below are ruled out
	else if (curNode->parent->parent->left != NULL && curNode->parent->parent->right != NULL) {
		//Parent and Uncle are red 1 (parent is a left child)
		if ((curNode->parent->parent->left == curNode->parent) && curNode->parent->parent->right->color) {
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
	Branch* last = NULL;
	signed short int newD = 1;

	//Standard BST Insert
	while (true) {
		if (current == NULL) {
			current = new Branch(val);
			current->color = true;
			current->parent = last;
			if (current->value < last->value)
				last->left = current;
			else
				last->right = current;
			nodes++;
			break;
		}
		else if (val < current->value) {
			last = current;
			current = current->left;
			newD++;
		}
		else if (val > current->value) {
			last = current;
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

signed short int RBtree::getNodes() {
	return nodes;
 }

signed short int RBtree::getInputs()
{
	return this->numInput;
}

void RBtree::traverse(Branch* curNode, stack<signed short int>* tobuild, bool* instruct) {
	/* traverse the tree recursivley and build the stack according to the intructed way.
	True = least to greatest (all left branches first then right)
	False = greatest to least (all right branches first then left.
	I.E: if true, the top element of the stack will be the lowest value.*/
	if (!*instruct) {
		if (curNode->left != NULL) {
			traverse(curNode->left, tobuild, instruct);
		}
		cout << curNode->value << " : " << curNode->times << endl;
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
		cout << curNode->value << " : " << curNode->times << endl;
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