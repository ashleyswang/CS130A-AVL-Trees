#include "Tree.h"
#include <iostream>
#include <fstream>
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

// void printLookup(vector<int> v, Tree* t){
// 	// something here
// }

int main(int argc, char *argv[]){

	argc++;
	ifstream ifs; 
	ifs.open(argv[1]); 

	string input;
	Tree* t = new Tree();

	while (1){
		// get first user command
		getline(ifs, input, ' '); 
		if(ifs.eof()){
			break;
		}
		if(input == "#"){
			// set getline cursor to end of this line
			getline(ifs, input);
		} else if(input == "insert"){
			string insertNums;
			getline(ifs, insertNums); 

			vector<int>* v = new vector<int>();
			string temp = "";

			for(char c : insertNums){
				// if character is a space
				if (int(c) == 32){
					v->push_back(stoi(temp));
					// cout << "** PUSHBACK " << temp << " **" << endl;
					temp="";
				} 
				// assume it's a number
				else {
					temp+=c;
				} 
			}
			v->push_back(stoi(temp));
			// cout << "** PUSHBACK " << temp << " **" << endl;
			printInsert(v, t);
			delete v;

		// } else if(input == "lookup"){
		// 	string lookupNums;
		// 	getline(ifs, lookupNums); 

		// 	vector<int> v = new vector<int>();
		// 	string temp = "";

		// 	for(char c : lookupNums){
		// 		// if character is a space
		// 		if (int(c) == 32){
		// 			v.push_back(stoi(temp));
		// 			temp="";
		// 		} 
		// 		// assume it's a number
		// 		else {
		// 			temp+=c;
		// 		} 
		// 	}
		// 	printLookup(v, t);
		// 	delete v;

		} else if(input == "print"){
			getline(ifs, input);
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
			getline(ifs, input);
		}

	}
	
	ifs.close();
	delete t;

}