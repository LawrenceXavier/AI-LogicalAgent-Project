#ifndef PROPOSITION_INCLUDED
#define PROPOSITION_INCLUDED

#include <set>
#include <string>
#include <iterator>

class Proposition {
private:
	std::set<int> S;	// if S is empty, then the proposition is True

public:
	Proposition();
	Proposition(const std::string &prop_text);

	Proposition operator & (const Proposition &other) const;
};

#endif
