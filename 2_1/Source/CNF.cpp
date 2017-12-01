#include "CNF.h"
#include "Proposition.h"


Element::Element() {
	p = new Proposition();	// an empty proposition
	prio = 0;
}


Element&	Element::operator += (int literal) {
	(*p) += literal;
	return *this;
}

	
Element		Element::operator & (const Element &other) const {
	Element res;
	res.p = new Proposition((*(this->p)) & (*(other.p)));
	res.prio = 0;
	return res;
}

	
bool		Element::operator < (const Element &other) const {
	if (this->prio != other.prio)
		return this->prio < other.prio;
	return (*(this->p)) < (*(other.p));
}


bool 		Element::isTrue() const {
	return this->p->isTrue();
}


bool 		Element::isFalse() const {
	return this->p->isFalse();
}


void		Element::assignPriority(int pr) {
	prio = pr;
}	


void 		Element::printOut(std::ofstream &fo, const std::vector< std::string > &mpStr) const {
	this->p->printOut(fo, mpStr);
}	

void		ListProposition::addProp(const Element &e) {
	staticList.insert(e.p);
}


bool		ListProposition::propExist(const Element &e) {
	return staticList.find(e.p) != staticList.end();
}


ListProposition::~ListProposition() {
	for (StatIt it = staticList.begin(); it != staticList.end(); ++it) 
		delete (*it);
	staticList.clear();
}


void 		CNF::addProp(const Element &e) {
	propList.insert(e);
	LP.addProp(e);
}


bool		CNF::propExist(const Element &e) {
	return LP.propExist(e);
}


Element 	CNF::splitIntoLiterals(const std::string &prop, char delim) {
	Element P;
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
	addProp(splitIntoLiterals(s, AND_OP));
	
	fi.close();
}


void 		CNF::printOut(std::ofstream &fo) const {
	bool flag = false;
	for (SIter it = propList.begin(); it != propList.end(); ++it) {
		if (flag) 
			fo << ',';
		else
			flag = true;
		it->printOut(fo, mpStr);
		
	}
	fo << std::endl;
}


int 		CNF::resolve(unsigned int prio) {
	for (SIter it = propList.begin(); it != propList.end(); ++it) {
		SIter jt = it;
		++jt;
		
		for (; jt != propList.end(); ++jt) {
			Element u = *it, v = *jt;
			Element c = u&v;
			if (c.isTrue())
				continue;

			if (propExist(c))
				continue;

			propList.erase(u); propList.erase(v);
			
			addProp(c);
			
			u.assignPriority(prio); v.assignPriority(prio);
			
			propList.insert(u); propList.insert(v);

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
