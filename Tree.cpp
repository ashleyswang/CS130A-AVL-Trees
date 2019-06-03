#include "Tree.h"

Tree::Tree(){
	root = nullptr;
}

Tree::~Tree(){
	ClearTree(root);
}

void Tree::ClearTree(Node* n){
	if(n != nullptr){
		ClearTree(n->getLeft());
		ClearTree(n->getRight());
		delete n;
	}
}

bool Tree::lookup(int key, int &visits, int &rotations){	
	// check for empty tree
	if(root == nullptr){
		return false;
	} else {
		Node* currentNode = root;
		while(currentNode->getKey() != key || currentNode != nullptr){
			if (key > currentNode->getKey()){
				currentNode = currentNode->getRight();
				visits++;
			}
			if (key < currentNode->getKey()){
				currentNode = currentNode->getLeft();
				visits++;
			}
		}
		if(currentNode != nullptr){
			return true;
		} else {
			return false;
		}
	}
}

void Tree::insert(int key, int &visits, int &rotations){
	int tempVisits = visits;
	int tempRotations = rotations;
	// if node does not exists return out
	if(this->lookup(key, visits, rotations)){
		return;
	} 
	// else insert node
	else {
		// reset visits and rotations to original values
		visits = tempVisits;
		rotations = tempRotations;
		Node* newNode = new Node(key);
		Node* currentNode = root;
		Node* unbalanced = nullptr;
		// check for empty tree
		if(root == nullptr){
			root = newNode;
		} else {
			while(currentNode != nullptr){
				currentNode->increaseHeight();
				
				// key is less than currentNode key
				if(key < currentNode->getKey()){
					// if there is a left child on current node
					if(currentNode->getLeft() != nullptr){
						currentNode = currentNode->getLeft();
					} 
					// if there is no left child
					// make current node parent of new node
					else {
						currentNode->setLeft(newNode);
						newNode->setParent(currentNode);
						break;
					}
				}

				// key is greater than currentNode key
				if(key > currentNode->getKey()){
					// if there is a right child on current node
					if(currentNode->getRight() != nullptr){
						currentNode = currentNode-> getRight();
					}
					// if there is no left child
					// make current node parent of new node
					else{ 
						currentNode->setRight(newNode);
						newNode->setParent(currentNode);
						break;
					}
				}

			}
		}
		// start balance at newNode's grandparent since parent cannot
		// be unbalanced since it has either 1 or 2 children 
		// (at most difference of 1)
		balanceTree(newNode->getParent()->getParent(), rotations);
	}
}

void Tree::balanceTree(Node* n, int &rotations){
	// right side longer than left side
	if (n->balance() > 1){
		// right-right: single left rotation
		if (n->getRight()->balance() > 0){
			rotateLeft(n);
			rotations++;
		}
		// right-left: right-left rotation
		if (n->getRight()->balance() < 0){
			rotateRight(n->getRight());
			rotateLeft(n);
			rotations+=2;
		}
	} 
	// left side longer than right side
	else if (n->balance() < 1){
		// left-left: single right rotation
		if (n->getLeft()->balance() < 0){
			rotateRight(n);
			rotations++;
		}
		// left-right: left-right rotation 
		if (n->getLeft()->balance() > 0){
			rotateLeft(n->getLeft());
			rotateRight(n);
			rotations+=2;
		}
	}
	if(n->getParent() != nullptr){
		balanceTree(n->getParent);
	}
}

void Tree::rotateLeft(Node* n){
	Node* oldPivot = n;
	Node* newPivot = n->getRight();

	oldPivot->setRight(newPivot->getLeft());
	newPivot->setLeft(oldPivot);
	newPivot->setParent(oldPivot->getParent())
	oldPivot->setParent(newPivot);
}

void Tree::rotateRight(Node* n){
	Node* oldPivot = n;
	Node* newPivot = n->getLeft();

	oldPivot->setLeft(newPivot->getRight());
	newPivot->setRight(oldPivot);
	newPivot->setParent(oldPivot->getParent())
	oldPivot->setParent(newPivot);
}

void Tree::print(){

}