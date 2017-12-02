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
	Element();
	Element&	operator += (int literal);
	Element		operator & (const Element &other) const;
	bool		operator < (const Element &other) const;
	bool		isTrue() const;
	bool		isFalse() const;
	void		assignPriority(int pr);
	void		printOut(std::ofstream &fo, const std::vector< std::string > &mpStr) const;
};

class ListProposition {
private:
	typedef std::set< Proposition*, PComp> TStatList;
	typedef TStatList::iterator StatIt;

	TStatList	staticList;
public:
	void	addProp(Element &e); 
	bool	propExist(const Element &e);
	~ListProposition(); 
};


class CNF {
private:
	ListProposition			LP;

	typedef std::set< Element >::iterator SIter;

	std::string 			inferred;
	std::set< Element > 		propList;
	std::map< std::string, int > 	mpLiteral;
	std::vector< std::string > 	mpStr;

	void 		addProp(const Element &e);	
	bool		propExist(const Element &e);
	
	Element 	splitIntoLiterals(const std::string &prop, char delim);
public:
	CNF(const std::string &FILE_NAME);

	void		printOut(std::ofstream &fo) const;
	int 		resolve(unsigned int prio);

	friend void 	RobinsonResolution(CNF cnf, const std::string &FILE_NAME);
};


#endif

