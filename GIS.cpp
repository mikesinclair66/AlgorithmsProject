#include <iostream>
#include <string>
#include "CommandProcessor.hpp"
#include "Logger.hpp"
#include "PRQuadTree.hpp"

using namespace std;
using namespace pr;

/*
	CMake project build process - Michael Sinclair
*/

QuadTree tree;

void computeWorldCommand(string north, string east, string south, string west);

int main(int argc, char* argv[]) {
	if (argc == 4) {
		string db = argv[1], cmd = argv[2], log = argv[3];
		CommandProcessor cp("../" + cmd);
		cp.updateContent();

		for (Query* query : cp.getQueries())
			if (query != nullptr) {
				CommandType type = query->getCommandType();
				vector<string> args = query->getArgs();
				query->printWords();

				switch (query->getCommandType()) {
				case CommandType::WORLD:
					computeWorldCommand(args[3], args[1], args[2], args[0]);
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

void computeWorldCommand(string north, string east, string south, string west) {
	tree.defineRegion(
		stoul(north.substr(0, north.length() - 1)),
		stoul(east.substr(0, east.length() - 1)),
		stoul(south.substr(0, south.length() - 1)),
		stoul(west.substr(0, west.length() - 1))
	);
}