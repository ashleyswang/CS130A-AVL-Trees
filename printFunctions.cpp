#include "Tree.h"
#include <iostream>
#include <vector>
#include <string>
#include <utility>

using namespace std;

void printInsert(vector<int>* v, Tree* t){
	int visits=0;
	int rotations=0;
	int success=0;
	int size=v->size();

	for(int i=0; i<size; i++){

		if(t->insert(v->at(i), visits, rotations)){
			success++;
		}
	}

	cout << "Added " << success << " of " << size << " nodes." << endl;
	cout << "Visited " << visits << " (" << (double(visits)/size)
		<< ") nodes and performed " << rotations << " (" 
		<< (double(rotations)/size) << ") rotations." << endl << endl;
}

void printLookup(vector<int>* v, Tree* t){
	int visits=0;
	int success=0;
	int size=v->size();
	string found = "";

	for(int i=0; i<size; i++){

		if(t->lookup(v->at(i), visits)){
			if(found != ""){
				found += ", ";
			}
			success++;
			found += to_string(v->at(i));
		}
	}

	cout << "Found " << success << " of " << size << " nodes: [" << found << "]"<< endl;
	cout << "Visited " << visits << " (" << (double(visits)/size)
		<< ") nodes and performed 0 (0) rotations." << endl << endl;
}

// returns vector of tall leaves in tree
void findTallLeaf(Node* n, vector<Node*> &v){
	// if n is a leaf
	if(n == nullptr){
		return;
	} else if(n->getHeight() == 0){
		if(n->isTall()){
			v.push_back(n);
		}
	}
	// if not a leaf
	else {
		findTallLeaf(n->getLeft(), v);
		findTallLeaf(n->getRight(), v);
	}
}

// returns the node that will be unbalanced if we add to node n
Node* findUnbalanced(Node* n){
	// if parent is not balanced
	if(n->getParent()->balance() != 0){
		return n->getParent();
	} else {
		return findUnbalanced(n->getParent());
	}
}

string rotateTypeString(int r){
	if (r == 2){
		return "left-left";
	} else if (r == 3){
		return "right-right";
	} else if (r == 5){
		return "left-right";
	} else {
		return "right-left";
	}
}

// returns int corresponding to a certain rotation
// left-left = 2; right-right = 3; left-right = 5; right-left = 7;
// left-left & left-right = 10; right-right & right-left = 21;
int rotateType(pair<Node*, Node*> nodePair){
	Node* unbalanced = nodePair.first;
	Node* leaf = nodePair.second;

	if(unbalanced == leaf->getParent()){
		if(leaf->isLeft()){
			return 10;
		} else {
			return 21;
		}
	} else {
		// leaf node is on left side of unbalanced node
		if(leaf->getKey() < unbalanced->getKey()){
			if(leaf->getKey() < unbalanced->getLeft()->getKey())
				return 2;
			else
				return 5;
		}
		// leaf node is on right side of unbalanced node 
		else {
			if(leaf->getKey() > unbalanced->getLeft()->getKey())
				return 3;
			else
				return 7;
		}
	}
}

string getRotateRange(int r, Node* leaf, Tree* t){
	int min = -2147483648;
	int max = 2147483647;

	Node* currentNode = t->getRoot();

	while(currentNode != nullptr){

		if (leaf->getKey() > currentNode->getKey()){
			min = currentNode->getKey()+1;
			currentNode = currentNode->getRight();
		}
		else if (leaf->getKey() < currentNode->getKey()){
			max = currentNode->getKey()-1;
			currentNode = currentNode->getLeft();
		}
		else{
			// at leaf, end with left
			if(r == 2 || r == 7){
				max = currentNode->getKey()-1;
				break;
			} else {
				min = currentNode->getKey()+1;
				break;
			}
		}
	}

	if(min > max){
		return "";
	} else if(min == max){
		return to_string(min);
	} else {
		return (to_string(min) + " to " + to_string(max));
	}

}

void printRotate(int r, Tree* t){
	vector<Node*> leaves;
	findTallLeaf(t->getRoot(), leaves);
	string rotateRanges = "";
	
	// tree is balanced -> no rotations
	if(!leaves.empty()){
		// find unbalanced node for all tall leaves
		// create vector of pairs of nodes <unbalanced node, leaf node>
		// that would cause the rotation we want
		vector<pair<Node*, Node*>> unbalancedPairs;
		for(Node* n : leaves){
			pair<Node*, Node*> nodePair;
			nodePair.first = findUnbalanced(n);
			nodePair.second = n;
			
			// if rotation type for node pair matches what we want
			if(!(rotateType(nodePair)%r)){
				unbalancedPairs.push_back(nodePair);
			}
		}
		for(pair<Node*, Node*> p : unbalancedPairs){
			if (rotateRanges != ""){
				rotateRanges+=", ";
			}

			Node* leaf = p.second;
			rotateRanges += getRotateRange(r, leaf, t);
		}
	}

	if(rotateRanges == ""){
		cout << "No inserts would cause a " << rotateTypeString(r) << " rotation." << endl << endl;
	} else {
		cout << "The following inserts would cause a "<< rotateTypeString(r) << " rotation:" << endl;
		cout << rotateRanges << endl << endl;
	}

}


