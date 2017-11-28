#include "CNF.h"
#include "Proposition.h"


Proposition 	CNF::splitIntoLiterals(const std::string &prop, char delim) {
	Proposition P;
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
			mpStr.push_back(s);
		}
		
		int val = mpLiteral[s];	
		P += val*p;
	}
	return P;
}


CNF::CNF(const std::string &FILE_NAME) {
	std::ifstream fi(FILE_NAME);	
	std::string s;

	std::getline(fi, s);		// read BEGIN_KB

	// Read all propositions
	while (!fi.eof()) {
		std::getline(fi, s);
		if (s == END_KB)	// read END_KB
			break;
		propList.insert(splitIntoLiterals(s, OR_OP));
	} 

	std::getline(fi, s);
	inferred = s;
	propList.insert(splitIntoLiterals(s, AND_OP));
	
	fi.close();
}


void 		CNF::printOut(std::ofstream &fo) const {
	bool flag = false;
	for (std::set< Proposition >::iterator it = propList.begin(); it != propList.end(); ++it) {
		if (flag) 
			fo << ',';
		else
			flag = true;
		it->printOut(fo, mpStr);
		
	}
	fo << std::endl;
}


int 		CNF::resolve(unsigned int prio) {
	for (std::set< Proposition >::iterator it = propList.begin(); it != propList.end(); ++it) {
		std::set< Proposition >::iterator jt = it;
		++jt;
		
		for (; jt != propList.end(); ++jt) {
			Proposition u = *it, v = *jt;
			Proposition c = u&v;
			if (c.isTrue())
				continue;
			propList.erase(u);
			propList.erase(v);
			propList.insert(c);
			u.assignPriority(prio);
			v.assignPriority(prio);
			propList.insert(u);
			propList.insert(v);
			if (c.isFalse())
				return 1;
			return 0;
		}
	}
	return -1;
}


void 		RobinsonResolution(CNF cnf, const std::string &FILE_NAME) {
	std::ofstream fo(FILE_NAME);
	
	fo << cnf.inferred << std::endl;
	int t;
	unsigned int prio = 1;
	do 	
		cnf.printOut(fo);
	while ((t = cnf.resolve(prio)) == 0);
	if (t == 1)
		fo << "True" << std::endl;
	fo.close();
}
