#ifndef PROPOSITION_INCLUDED
#define PROPOSITION_INCLUDED

#include <set>
#include <string>
#include <iterator>
#include <fstream>
#include <vector>

class Proposition {
private:
	std::set<int>	S;		// if S is empty, then the proposition is False

public:
	Proposition();

	Proposition&	operator += (int literal);
	Proposition	operator & (const Proposition &other) const;
	bool		operator < (const Proposition &other) const;
	
	bool		isTrue() const;
	bool 		isFalse() const;

	void 		printOut(std::ofstream &fo, const std::vector< std::string > &mpStr) const;
};

#endif
