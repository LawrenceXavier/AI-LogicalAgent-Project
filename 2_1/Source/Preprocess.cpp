#include "Preprocess.h"

#include <fstream>
#include <iostream>

bool Preprocess::inLiteral(char c) {
	return (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9');
}

void Preprocess::splitIntoLiterals(std::string &prop, char delim) {
	std::string editedprop = "";
	for (int i = 0, len = prop.size(); i < len; ++i) {
		std::string s = "";

		int p = (delim == OR_OP) ? 1 : (-1);

		while (i < len && prop[i] != delim) {	
		// delim in [AND_OP, OR_OP]
			if (inLiteral(prop[i]))
				s += prop[i++];
			else	// prop[i] = NOT_OP
				p *= -1;
		}
		
		if (mpLiteral.find(s) == mpLiteral.end()) {
			int sz = mpLiteral.size();
			mpLiteral[s] = sz;
		}
		
		int val = mpLiteral[s];	
		editedprop += std::to_string(val*p);
	}
	prop = editedprop;
}

Preprocess::Preprocess(const std::string &FILE_NAME) {
	std::ifstream fi(FILE_NAME);

	std::cout << bool(fi) << std::endl;	
	
	std::string s;

	std::getline(fi, s);	// read BEGIN_KB
	std::cout << s << std::endl;

	// Read all propositions
	do {
		if (fi.eof()) break;
		std::getline(fi, s);
		std::cout << s << std::endl;
		if (s == END_KB)	// read END_KB
			break;
		else {
			propList.push_back(s);
//			splitIntoLiterals(s, OR_OP);
		}
	} while (true);

	std::getline(fi, s);
//	splitIntoLiterals(s, AND_OP);
	
	fi.close();
}
