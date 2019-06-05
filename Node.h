#ifndef NODE_H
#define NODE_H

#include <algorithm>

class Node{

	public: 

		// Constructors
		Node(int key){
			this->key = key;
			parent = nullptr;
			leftChild = nullptr;
			rightChild = nullptr;
			height = 0;
		};

		~Node(){
			delete leftChild;
			delete rightChild;
		};

		// Accessors
		int getKey(){ return key; };
		Node* getParent(){ return parent; };
		Node* getLeft(){ return leftChild; };
		Node* getRight(){ return rightChild; };
		int getHeight(){ return height; };
		int balance(){
			int leftHeight;
			int rightHeight;

			if(leftChild == nullptr)
				leftHeight = -1;
			if(leftChild != nullptr)
				leftHeight = leftChild->getHeight();
			if(rightChild == nullptr)
				rightHeight = -1;
			if(rightChild != nullptr)
				rightHeight = rightChild->getHeight();

			return rightHeight - leftHeight;
		};

		// for avl.cpp print functions		
		bool isLeft(){
			if(key < parent->getKey()){
				return true;
			} else {
				return false;
			}
		}

		bool isTall(){

			if (parent == nullptr){
				return false;
			}

			int parentKey = parent->getKey();
			Node* sibling;

			// if only child of parent
			if(parent->getLeft()==nullptr || parent->getRight()==nullptr){
				return true;
			}

			// set sibling node
			if(key < parentKey){
				sibling = parent->getRight();
			} else {
				sibling = parent->getLeft();
			}

			// compare height with sibling
			if (height > sibling->getHeight()){
				return true;
			} else if (height < sibling->getHeight()){
				return false;
			} else {
				return parent->isTall();
			}

		}


		// Modifier
		void setKey(int key){ this->key = key; };
		void setParent(Node* parent){ this->parent = parent; };
		void setLeft(Node* leftChild){ this->leftChild = leftChild; };
		void setRight(Node* rightChild){ this-> rightChild = rightChild; };
		void increaseHeight(){ height++; };
		void setHeight(){ 
			int leftHeight;
			int rightHeight;

			if(leftChild == nullptr)
				leftHeight = -1;
			if(leftChild != nullptr)
				leftHeight = leftChild->getHeight();
			if(rightChild == nullptr)
				rightHeight = -1;
			if(rightChild != nullptr)
				rightHeight = rightChild->getHeight();

			this->height = std::max(leftHeight+1, rightHeight+1);
		};
		void setHeight(int height){ this->height = height; };


	private:
		int key;
		Node* parent;
		Node* leftChild;
		Node* rightChild;
		int height;

};

#endif
