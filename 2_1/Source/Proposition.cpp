#include "Proposition.h"


Proposition::Proposition() {
	
}


Proposition::Proposition(const std::string &prop_text) {
	std::string delimiter = "|";
	
	for (size_t pos = prop_text.find(delimiter); ; pos = prop_text.find(delimiter)) {
		std::string token = prop_text.substr(0, pos);
		S.insert(std::stoi(token));
		
		if (pos == std::string::npos)
			break;
	}
}


Proposition Proposition::operator & (const Proposition &other) const {
	Proposition res = *this;	
	res.S.insert(other.S.begin(), other.S.end());
	
	for (std::set<int>::iterator it = res.S.begin(); (*it) < 0 && it != res.S.end(); ++it) {
		if (res.S.find(-(*it)) != res.S.end()) {
			res.S.erase(-(*it));
			res.S.erase(*it);
			break;
		}
	}

	for (std::set<int>::iterator it = res.S.begin(); (*it) < 0 && it != res.S.end(); ++it) {
		if (res.S.find(-(*it)) != res.S.end()) {
			res.S.clear();
			break;
		}
	}
	return res;
} 
