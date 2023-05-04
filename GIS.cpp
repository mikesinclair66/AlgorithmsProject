#include <iostream>
#include <string>
#include "CommandProcessor.hpp"

using namespace std;

/*
	CMake project build process - Michael Sinclair
*/

int main(int argc, char* argv[]) {
	if (argc == 4) {
		string db = argv[1], cmd = argv[2], log = argv[3];
		cout << "Reading " << cmd << endl;
		CommandProcessor cp("../" + cmd);
		cp.updateContent();
		cp.printWords();
		return 0;
	}
	else {
		cerr << "The run file must be executed with three arguments: <database> <commands> <logger>" << endl;
		return -1;
	}
}