#include "CNF.h"

#define INPUT_FILE_NAME "input.txt"
#define OUTPUT_FILE_NAME "1512203.txt"

int main(int argc, char* argv[]) {
	CNF Data(INPUT_FILE_NAME);
	RobinsonResolution(Data, OUTPUT_FILE_NAME);
	// Data.printOut(OUTPUT_FILE_NAME);
	return 0;
}
