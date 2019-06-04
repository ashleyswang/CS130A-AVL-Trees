#ifndef TREE_H
#define TREE_H

#include "Node.h"

class Tree{

	public: 
		// Constructor and Destructor
		Tree();
		~Tree();

		bool insert(int key, int &visits, int &rotations);
		bool lookup(int key, int &visits);
		void print();

	private:
		// Destructor helper function
		void ClearTree(Node* n);

		// Insert helper functions
		void balanceTree(Node* n, int &rotations);
		void rotateLeft(Node* n);
		void rotateRight(Node* n);
		// void rotateHeightAdjustment(Node* n);

		// Print helper function
		void printTree(Node* n, int indentCounter);
		
		Node* root;
		
};

#endif
