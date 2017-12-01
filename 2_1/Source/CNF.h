#ifndef CNF_INCLUDED
#define CNF_INCLUDED

#include <vector>
#include <set>
#include <string>
#include <map>
#include <fstream>
#include <iterator>

#include "Proposition.h"

#define OR_OP		'|'
#define AND_OP		'&'
#define NOT_OP		'~'
#define BEGIN_KB	"KB"
#define END_KB		"ENDKB"

struct PComp {
	bool operator () (const Proposition* x, const Proposition* y) const {
		return (*x) < (*y);
	}
};

class Element {
friend class ListProposition;;
private:
	Proposition* 	p;
	int 		prio;
public:	
	Element() {
		p = new Proposition();	// an empty proposition
		prio = 0;
	}

	Element&	operator += (int literal) {
		(*p) += literal;
		return *this;
	}

	
	Element		operator & (const Element &other) const {
		Element res;
		res.p = new Proposition((*(this->p)) & (*(other.p)));
		res.prio = 0;
		return res;
	}
	
	bool		operator < (const Element &other) const {
		if (this->prio != other.prio)
			return this->prio < other.prio;
		return (*(this->p)) < (*(other.p));
	}

	bool 		isTrue() const {
		return this->p->isTrue();
	}

	bool 		isFalse() const {
		return this->p->isFalse();
	}

	void		assignPriority(int pr) {
		prio = pr;
	}	

	void 		printOut(std::ofstream &fo, const std::vector< std::string > &mpStr) const {
		this->p->printOut(fo, mpStr);
	}	
};

class ListProposition {
private:
	typedef std::set< Proposition*, PComp> TStatList;
	typedef TStatList::iterator StatIt;

	TStatList	staticList;
public:
	void	addProp(const Element &e) {
		staticList.insert(e.p);
	}

	bool	propExist(const Element &e) {
		return staticList.find(e.p) != staticList.end();
	}

	~ListProposition() {
		for (StatIt it = staticList.begin(); it != staticList.end(); ++it) 
			delete (*it);
		staticList.clear();
	
	}
};


class CNF {
private:
	ListProposition			LP;

	typedef std::set< Element >::iterator SIter;

	std::string 			inferred;
	std::set< Element > 		propList;
	std::map< std::string, int > 	mpLiteral;
	std::vector< std::string > 	mpStr;

	void 		addProp(const Element &e) {
		propList.insert(e);
		LP.addProp(e);
	}

	bool		propExist(const Element &e) {
		return LP.propExist(e);
	}
	
	Element 	splitIntoLiterals(const std::string &prop, char delim);
public:
	CNF(const std::string &FILE_NAME);

	void		printOut(std::ofstream &fo) const;
	int 		resolve(unsigned int prio);

	friend void 	RobinsonResolution(CNF cnf, const std::string &FILE_NAME);
};


#endif

