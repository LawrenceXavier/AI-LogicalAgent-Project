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

class CNF {
private:
	std::set< Proposition > propList;
	std::map< std::string, int > mpLiteral;
	std::vector< std::string > mpStr;

	Proposition splitIntoLiterals(const std::string &prop, char delim);
public:
	CNF(const std::string &FILE_NAME);
	void printOut(std::ofstream &fo) const;
	int resolve();

	friend void RobinsonResolution(CNF cnf, const std::string &FILE_NAME);
};


#endif

