#pragma once
using namespace std;
#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <fstream>
#include <hash_map>

struct ngram {
	vector<string> str;
	int occurred = 1;
	ngram(string in) {
		str.push_back(in);
	}
	ngram(string in1, string in2) {
		str.push_back(in1);
		str.push_back(in2);
	}
	ngram(string in1, string in2, string in3) {
		str.push_back(in1);
		str.push_back(in2);
		str.push_back(in3);
	}
};

class Counter {
	vector<string> toParse;
	vector<string> withPunct;
	vector<ngram> unigrams;
	vector<ngram> bigrams;
	vector<ngram> trigrams;

public:
	Counter() {}
	Counter(vector<string> in) : toParse(in) {}
	void checkPunctuation(string in) {
		bool punctuation = false;
		for (int i = 0; i < in.length(); ++i) {
			if (in[i] == '.' || in[i] == '!' || in[i] == '?') {
				punctuation = true;
			}
		}
		if (punctuation) {
			withPunct.push_back(removeAt(in, in.length()-1));
			withPunct.push_back(string(1, in[in.length() - 1]));
		}
		else {
			withPunct.push_back(in);
		}
	}
	void countUnigrams() {
		for (int i = 0; i < toParse.size(); ++i) {
			int j = 0;
			checkPunctuation(toParse[i]);
			if (!contains(toParse[i])) {
				unigrams.push_back(ngram(toParse[i]));
			}
		}
	}
	void countOthers() {
		int size = withPunct.size();
		for (int i = 0; i < size; ++i) {
			string test1 = withPunct[i];
			if (i < size - 1) {
				string test2 = withPunct[i + 1];
				if (!contains(test1, test2))
					bigrams.push_back(ngram(test1, test2));
			}
			if (i < size - 2)	{
				string test2 = withPunct[i + 1];
				string test3 = withPunct[i + 2];
				if (!contains(test1, test2, test3))
					trigrams.push_back(ngram(test1, test2, test3));
			}
		}
	}
	void count() {
		countUnigrams();
		countOthers();
	}

	string removeAt(string in, int at) {
		string out;
		for (int i = 0; i < in.length(); ++i) {
			if (i != at)	out.push_back(in[i]);
		}
		return out;
	}

	bool contains(string in) {
		for (int i = 0; i < unigrams.size(); ++i) {
			if (unigrams[i].str[0] == in) {
				unigrams[i].occurred++;
				return true;
			}
		}
		return false;
	}
	bool contains(string in1, string in2) {
		for (int i = 0; i < bigrams.size(); ++i) {
			if (bigrams[i].str[0] == in1) {
				if (bigrams[i].str[1] == in2) {
					bigrams[i].occurred++;
					return true;
				}
			}
		}
		return false;
	}
	bool contains(string in1, string in2, string in3) {
		for (int i = 0; i < trigrams.size(); ++i) {
			if (trigrams[i].str[0] == in1) {
				if (trigrams[i].str[1] == in2) {
					if (trigrams[i].str[2] == in3) {
						trigrams[i].occurred++;
						return true;
					}
				}
			}
		}
		return false;
	}
 
	void displayResults() {
		for (int i = 0; i < unigrams.size(); ++i) {
			cout << unigrams[i].str[0] << "   " << unigrams[i].occurred << "   "
				<< (float)unigrams[i].occurred / unigrams.size() << endl;
		}
	}
	
	void outputUnigrams() {
		ofstream out("unigramOutput.txt");
		out.clear();
		for (int i = 0; i < unigrams.size(); i++) {
			out << unigrams[i].str[0] << "\t\t" << unigrams[i].occurred << "\t";
			out.precision(3);
			out << (float)unigrams[i].occurred / unigrams.size() << endl;
		}
	}
	void outputBigrams() {
		ofstream out("bigramOutput.txt");
		out.clear();
		for (int i = 0; i < bigrams.size(); i++) {
			out << bigrams[i].str[0] << " " << bigrams[i].str[1] << "\t\t" << bigrams[i].occurred << "\t";
			out.precision(3);
			out << (float)bigrams[i].occurred / bigrams.size() << endl;
		}
	}
	void outputTrigrams() {
		ofstream out("trigramOutput.txt");
		out.clear();
		for (int i = 0; i < trigrams.size(); i++) {
			out << trigrams[i].str[0] << " " << trigrams[i].str[1] << " " << trigrams[i].str[2] << "\t\t" << trigrams[i].occurred << "\t";
			out.precision(3);
			out << (float)trigrams[i].occurred / trigrams.size() << endl;
		}
	}
	void outputResults() {
		outputUnigrams();
		outputBigrams();
		outputTrigrams();
	}

	bool compareStrings(ngram one, string two) {
		if (one.str[0].size() != two.length())
			return false;
		for (int i = 0; i < one.str[0].size(); ++i) {
			if (one.str[0][i] != two[i])	
				return false;
		}
		return true;
	}

	void parse(string &in) {
		int iter = in.length();
		for (int i = 0; i < iter; ++i) {
			for (int j = 1; j < unigrams.size(); ++j) {
				string myS = in.substr(i, unigrams[j].str[0].size());
				if (compareStrings(unigrams[j], myS)) {
					in.insert(i + myS.size(), " ");
					i += myS.size();
					iter++;
					break;
				}
			}
		}
	}
};