#ifndef NODE_H
#define NODE_H

public class Node{

	public: 
		
		int visits=0;
		int rotations=0;

		// Constructors
		Node(int key){
			this->key = key;
			parent = nullptr;
			leftChild = nullptr;
			rightChild = nullptr;
		};

		// Accessors
		int getKey(){ return key; };
		Node* getParent(){ return parent; };
		Node* getLeft(){ return leftChild; };
		Node* getRight(){ return rightChild; };
		int getHeight(){ 
			if (this == nullptr){
				return -1;
			} else {
				return height; 
			}
		};
		int balance(){
			return rightChild->getHeight() - leftChild->getHeight();
		};

		// Modifier
		void setKey(int key){ this->key = key; };
		void setParent(Node* parent){ this->parent = parent; };
		void setLeft(Node* leftChild){ this->leftChild = leftChild; };
		void setRight(Node* rightChild){ this-> rightChild = rightChild; };
		void increaseHeight(){ height++; };
		void decreaseHeight(){ height--; };
		void setHeight(int height){ this->height = height; };


	private:
		int key;
		Node* parent;
		Node* leftChild;
		Node* rightChild;
		int height;

};

#endif
