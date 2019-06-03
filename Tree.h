#ifndef TREE_H
#define TREE_H

public class Tree{

	public: 
		// Constructor and Destructor
		Tree();
		~Tree();

		Node* insert(int key, int &visits, int &rotations);
		Node* lookup(int key, int &visits, int& rotations);
		void print();

	private:
		// Destructor helper function
		void ClearTree(Node* n);

		// Insert helper functions
		void balanceTree(Node* n, int &rotations);
		void rotateLeft(Node* n);
		void rotateRight(Node* n);

		Node* root;


};

#endif
