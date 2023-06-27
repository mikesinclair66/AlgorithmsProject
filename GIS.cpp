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
		CommandProcessor cp("../" + cmd);
		cp.updateContent();

		for (Query query : cp.getQueries()) {
			CommandType type = query.getCommandType();
			vector<string> args = query.getArgs();
			query.printWords();

			switch (query.getCommandType()) {
				case CommandType::WORLD:

					break;
				case CommandType::IMPORT:

					break;
				case CommandType::QUIT:

					break;
				case CommandType::DEBUG:

					break;
				case CommandType::WHAT_IS_AT:

					break;
				case CommandType::WHAT_IS:

					break;
				case CommandType::WHAT_IS_IN:

					break;
			}
		}

		return 0;
	}
	else {
		cerr << "The run file must be executed with three arguments: <database> <commands> <logger>" << endl;
		return -1;
	}
}