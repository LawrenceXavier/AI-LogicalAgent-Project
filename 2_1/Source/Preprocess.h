#ifndef PREPROCESS_INCLUDED
#define PREPROCESS_INCLUDED

#include <vector>
#include <string>
#include <map>

#define OR_OP		'|'
#define AND_OP		'&'
#define NOT_OP		'~'
#define BEGIN_KB	"KB"
#define END_KB		"ENDKB"

class Preprocess {
private:
	std::vector< std::string > propList;
	std::map< std::string, int > mpLiteral;

	void splitIntoLiterals(std::string &prop, char delim);
public:
	Preprocess(const std::string &FILE_NAME);
};

#endif

