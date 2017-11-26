#include "Preprocess.h"

#include <fstream>


void Preprocess::splitIntoLiterals(std::string &prop, char delim) {
	std::string editedprop = "";
	for (int i = 0, len = prop.size(); i < len; ++i) {
		std::string s = "";

		int p = (delim == OR_OP) ? 1 : (-1);

		while (i < len && prop[i] != delim) 	// delim in [AND_OP, OR_OP]
			if (prop[i] != NOT_OP) 
				s += prop[i++];
			else 
				p *= -1, ++i;
		
		if (mpLiteral.find(s) == mpLiteral.end()) {
			int sz = mpLiteral.size();
			mpLiteral[s] = sz+1;
		}
		
		int val = mpLiteral[s];	
		editedprop += std::to_string(val*p)+delim;
	}

	prop = editedprop.substr(0, editedprop.length()-1);
}

Preprocess::Preprocess(const std::string &FILE_NAME) {
	std::ifstream fi(FILE_NAME);	
	std::string s;

	std::getline(fi, s);	// read BEGIN_KB

	// Read all propositions
	do {
		if (fi.eof()) break;

		std::getline(fi, s);

		if (s == END_KB) break;	// read END_KB
		
		splitIntoLiterals(s, OR_OP);
		propList.push_back(s);
	} while (true);

	std::getline(fi, s);
	splitIntoLiterals(s, AND_OP);
	propList.push_back(s);
	
	fi.close();
}
