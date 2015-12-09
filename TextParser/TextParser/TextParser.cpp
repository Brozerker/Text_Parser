// TextParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	ifstream file;
	file.open("text.txt");
	vector<string> vector;
	while (file) {
		string temp;
		file >> temp;
		cout << temp << endl;
		vector.push_back(temp);
	}
	cout << "vector is " << vector.size() << " words long";
	return 0;
}

void toLowerCase(string * input) {
	for (int i = 0; i < input->size(); ++i) {
		input[i] = tolower(input->at(i));
	}
}

