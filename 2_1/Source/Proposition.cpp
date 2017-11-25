#include "Proposition.h"

void Proposition::normalize(std::set<int> &prop) {
	for (std::set<int>::iterator it = prop.begin(); (*it) < 0 && it != prop.end(); ++it) {
		if (prop.find(-(*it)) != prop.end()) {
			prop.clear();
			return;
		}
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
	normalize(res.S);
	return res;
} 
