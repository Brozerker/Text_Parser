// TextParser.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "counter.h"

string formatString(string in, string list);
string removeAt(string in, int at);
void toLowerCase(string & input);

int _tmain(int argc, _TCHAR* argv[])
{
	string whiteList = "abcdefghijklmnopqrstuvwxyz.?!";
	ifstream file;
	file.open("smallText.txt");
	vector<string> wordList;
	while (file) {
		string temp;
		file >> temp;
		//cout << temp << endl;
		wordList.push_back(formatString(temp, whiteList));
	}
	Counter counter(wordList);
	counter.count();
	counter.outputResults();
	cout << "Enter a sentence without spaces or capitilization. \nFor instance \"This is a sentence\" becomes \"thisisasentence\"" << endl;
	string toParse = "";
	getline(cin, toParse);
	counter.parse(toParse);
	cout << toParse << endl;
	system("Pause");
	return 0;
}

string formatString(string in, string list) {	
	string out;
	toLowerCase(in);
	for (int i = 0; i < in.length(); ++i) {
		for (int k = 0; k < list.length(); ++k) {
			if (in[i] == list[k]) {
				out.push_back(in[i]);
			}
		}
	}
	return out;
}

void toLowerCase(string & input) {
	for (int i = 0; i < input.length(); ++i) {
		input[i] = tolower(input[i]);
	}
}

