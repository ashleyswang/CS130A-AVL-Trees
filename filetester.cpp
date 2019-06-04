#include "Tree.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){

	ifstream ifs; 
	ifs.open("filetester.txt"); 

	string input;
	string input2;

	getline(ifs, input);
	getline(ifs, input2);

	string input3;
	getline(input2, input3, " ");

	cout << input << input3 << endl;
	
	ifs.close();


}