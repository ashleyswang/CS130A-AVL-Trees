#include "Tree.h"
#include <iostream>
#include <string>

Tree::Tree(){
	root = nullptr;
}

Tree::~Tree(){
	delete root;
}

bool Tree::lookup(int key, int &visits){	
	Node* currentNode = root;
	while(currentNode != nullptr){
	 	visits++;

		if (key > currentNode->getKey()){
			currentNode = currentNode->getRight();
		}
		else if (key < currentNode->getKey()){
			currentNode = currentNode->getLeft();
		}
		else{
			return true;
		}
	}
	return false;
}

bool Tree::insert(int key, int &visits, int &rotations){
	// reset visits and rotations to original values
	Node* currentNode = root;
	Node* newNode = nullptr;
	
	// check for empty tree
	if(root == nullptr){
		root = new Node(key);
		return true;
	}
	while(true){
		visits++;

		// key is less than currentNode key
		if(key < currentNode->getKey()){
			// if there is a left child on current node
			if(currentNode->getLeft() != nullptr){
				currentNode = currentNode->getLeft();
			} 
			// if there is no left child
			// make current node parent of new node
			else {
				newNode = new Node(key);
				currentNode->setLeft(newNode);
				newNode->setParent(currentNode);
				break;
			}
		}

		// key is greater than currentNode key
		else if(key > currentNode->getKey()){
			// if there is a right child on current node
			if(currentNode->getRight() != nullptr){
				currentNode = currentNode-> getRight();
			}
			// if there is no left child
			// make current node parent of new node
			else{ 
				newNode = new Node(key);
				currentNode->setRight(newNode);
				newNode->setParent(currentNode);
				break;
			}
		}
		// key is already in tree
		else{
			return false;
		}
	}

	currentNode = newNode;
	while(true){
		balanceTree(currentNode, rotations);
		currentNode->setHeight();
		if(currentNode->getParent() == nullptr){
			root = currentNode;
			return true;
		} else {
			currentNode = currentNode->getParent();
		}
	}
}

void Tree::balanceTree(Node* n, int &rotations){
	// right side longer than left side
	if (n->balance() > 1){
		// right-right: single left rotation
		if (n->getRight()->balance() > 0){
			rotateLeft(n);
			rotations++;
			return;
		}
		// right-left: right-left rotation
		else{
			rotateRight(n->getRight());
			rotateLeft(n);
			rotations+=2;
			return;
		}
	} 
	// left side longer than right side
	else if (n->balance() < -1){
		// left-left: single right rotation
		if (n->getLeft()->balance() < 0){
			rotateRight(n);
			rotations++;
			return;
		}
		// left-right: left-right rotation 
		else{
			rotateLeft(n->getLeft());
			rotateRight(n);
			rotations+=2;
			return;
		}
	}
}

void Tree::rotateLeft(Node* n){
	Node* oldPivot = n;
	Node* newPivot = n->getRight();

	oldPivot->setRight(newPivot->getLeft());
	newPivot->setLeft(oldPivot);
	newPivot->setParent(oldPivot->getParent());
	oldPivot->setParent(newPivot);
	
	if(oldPivot->getRight() != nullptr){
		oldPivot->getRight()->setParent(oldPivot);
	}
	if(newPivot->getParent() != nullptr){
		if(newPivot->getParent()->getLeft() == oldPivot){
			newPivot->getParent()->setLeft(newPivot);
		} 
		if(newPivot->getParent()->getRight() == oldPivot){
			newPivot->getParent()->setRight(newPivot);
		}
	}

	oldPivot->setHeight();
	newPivot->setHeight();
}

void Tree::rotateRight(Node* n){
	Node* oldPivot = n;
	Node* newPivot = n->getLeft();

	oldPivot->setLeft(newPivot->getRight());
	newPivot->setRight(oldPivot);
	newPivot->setParent(oldPivot->getParent());
	oldPivot->setParent(newPivot);

	if(oldPivot->getLeft() != nullptr){
		oldPivot->getLeft()->setParent(oldPivot);
	}
	if(newPivot->getParent() != nullptr){
		if(newPivot->getParent()->getLeft() == oldPivot){
			newPivot->getParent()->setLeft(newPivot);
		} 
		if(newPivot->getParent()->getRight() == oldPivot){
			newPivot->getParent()->setRight(newPivot);
		}
	}

	oldPivot->setHeight();
	newPivot->setHeight();
}

void Tree::print(){
	printTree(root, 0);
}

void Tree::printTree(Node* n, int indentCounter){
	std::string indents = "";
	for(int i=0; i<indentCounter; i++){
		indents+="  ";
	}

	if(n == nullptr){
		std::cout << indents << "Null" << std::endl;
	} else if (n->getHeight() == 0){
		std::cout << indents << "Leaf(" << n->getKey() << ")" << std::endl;
	} else {
		std::cout << indents << "Node(" << n->getKey() << ", h=" << n->getHeight() 
			<< "):" << std::endl;
		printTree(n->getLeft(), indentCounter+1);
		printTree(n->getRight(), indentCounter+1);
	}
}