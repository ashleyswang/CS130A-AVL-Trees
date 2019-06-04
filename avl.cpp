#include "Tree.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void printInsert(vector<int>* v, Tree* t){
	int visits=0;
	int rotations=0;
	int success=0;
	int size=v->size();

	for(int i=0; i<size; i++){

		if(t->insert(v->at(i), visits, rotations)){
			success++;
			//cout << "** AFTER INSERTION " << v->at(i) <<" **" << endl;
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

int main(int argc, char *argv[]){

	argc++;
	ifstream ifs; 
	ifs.open(argv[1]); 

	string line;
	string input;
	Tree* t = new Tree();

	while (getline(ifs, line)) {
		if(line == "" || line[0] == '#') {
			continue;
		}
		// get first user command

		istringstream iss(line);
		iss >> input;
		 
		//cout << input << endl;
		if(input == "insert"){
			int value;
			vector<int> v;
			while(iss >> value) {
				v.push_back(value);
			}

			printInsert(&v, t);

		} else if(input == "lookup"){
			int value;
			vector<int> v;
			while(iss >> value) {
				v.push_back(value);
			}

			printLookup(&v, t);

		} else if(input == "print"){
			iss >> input;
			if(input == "tree"){
				t->print();
				cout << endl;
			}
			else if(input == "left-left"){
				// some function
			}
			else if(input == "left-right"){
				// some function
			}
			else if(input == "right-left"){
				// some function
			}
			else if(input == "right-right"){
				// some function
			}
		}

	}
	
	ifs.close();
	delete t;

}