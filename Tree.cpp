#include "Tree.h"
#include <iostream>
#include <string>

using namespace std;

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

bool Tree::lookup(int key, int &visits){	
	// check for empty tree
	if(root == nullptr){
		return false;
	} else {
		Node* currentNode = root;
		while(currentNode != nullptr && currentNode->getKey() != key){
			if (key > currentNode->getKey()){
				currentNode = currentNode->getRight();
				visits++;
			}
			else if (key < currentNode->getKey()){
				currentNode = currentNode->getLeft();
				visits++;
			}
		}
		if(currentNode == nullptr){
			return false;
		}
		else{
			return true;
		}
	}
}

bool Tree::insert(int key, int &visits, int &rotations){
	// reset visits and rotations to original values
	Node* newNode = new Node(key);
	Node* currentNode = root;
	
	// check for empty tree
	if(root == nullptr){
		root = newNode;
		visits = 0;
	}
	while(currentNode != nullptr){
		visits++;

		// key is less than currentNode key
		if(key < currentNode->getKey()){
			// if there is a left child on current node
			if(currentNode->getLeft() != nullptr){
				currentNode = currentNode->getLeft();
				continue;
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
		else if(key > currentNode->getKey()){
			// if there is a right child on current node
			if(currentNode->getRight() != nullptr){
				currentNode = currentNode-> getRight();
				continue;
			}
			// if there is no left child
			// make current node parent of new node
			else{ 
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

// void Tree::rotateHeightAdjustment(Node* n){
	
// 	if(n->getLeft() != nullptr){
// 		n->getLeft()->setHeight();
// 	}
// 	if(n->getRight() != nullptr){
// 		n->getRight()->setHeight();
// 	}

// 	Node* currentNode = n;
// 	while(currentNode != nullptr){
// 		currentNode->setHeight();
		
// 		if(currentNode->getParent() != nullptr){
// 			currentNode = currentNode->getParent();
// 		} else {
// 			root = currentNode;
// 			break;
// 		}
// 	}

// }

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