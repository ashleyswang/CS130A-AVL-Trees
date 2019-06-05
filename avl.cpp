#include "Tree.h"
#include "printFunctions.cpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

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
				printRotate(2, t);
			}
			else if(input == "left-right"){
				printRotate(5, t);
			}
			else if(input == "right-left"){
				printRotate(7, t);
			}
			else if(input == "right-right"){
				printRotate(3, t);
			}
		}

	}
	
	ifs.close();
	delete t;

}