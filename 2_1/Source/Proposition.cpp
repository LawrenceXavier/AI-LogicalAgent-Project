#include "Proposition.h"


Proposition::Proposition() {
}


Proposition&	Proposition::operator += (int literal) {
	S.insert(literal);
	return *this;
}


Proposition	Proposition::operator & (const Proposition &other) const {
	Proposition res = *this;	
	res.S.insert(other.S.begin(), other.S.end());
	
	bool found = false;
	for (std::set<int>::iterator it = res.S.begin(); (*it) < 0 && it != res.S.end(); ++it) {
		if (res.S.find(-(*it)) != res.S.end()) {
			res.S.erase(-(*it));
			res.S.erase(*it);
			found = true;
			break;
		}
	}
	
	if (!found) {
		res.S.clear();
		res.S.insert(0);
		return res;
	}
	for (std::set<int>::iterator it = res.S.begin(); (*it) < 0 && it != res.S.end(); ++it) {
		if (res.S.find(-(*it)) != res.S.end()) {
			res.S.clear();
			res.S.insert(0);
			break;
		}
	}
	return res;
}


bool 		Proposition::operator < (const Proposition &other) const {
	if (this->S.size() != other.S.size())
		return this->S.size() < other.S.size();
	for (std::set<int>::iterator it = this->S.begin(), jt = other.S.begin(); it != this->S.end(); ++it, ++jt) 
		if ((*it) < (*jt))
			return true;
		else if ((*it) > (*jt))
			return false;
	return false;
}


void 		Proposition::printOut(std::ofstream &fo, const std::vector< std::string > &mpStr) const {
	bool flag = false;

	for (std::set<int>::iterator it = S.begin(); it != S.end(); ++it) {
		if (flag) 
			fo << "|";
		else
			flag = true;

		if ((*it) > 0)
			fo << mpStr[(*it)-1];
		else 
			fo << "~" << mpStr[-(*it)-1];
	}
}


bool		Proposition::isTrue() const {
	return S.find(0) != S.end();
}


bool 		Proposition::isFalse() const {
	return S.size() == 0;
}

