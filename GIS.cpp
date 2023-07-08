#include <iostream>
#include <string>
#include "SystemManager.hpp"
#include "CommandProcessor.hpp"
#include "PRQuadTree.hpp"
#include "Storage.hpp"

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

		WriteMessenger logger("../" + log);
		ReadMessenger* fileImporter;
		Storage storage("../" + db);

		for (Query* query : cp.getQueries())
			if (query != nullptr) {
				CommandType type = query->getCommandType();
				vector<string> args = query->getArgs();

				switch (query->getCommandType()) {
				case CommandType::WORLD:
					computeWorldCommand(args[3], args[1], args[2], args[0]);
					logger.println("Defined world space at (N=" + args[3] + ", E=" + args[1]
						+ ", S=" + args[2] + ", W=" + args[0] + ")");
					logger.updateContent();
					break;
				case CommandType::IMPORT:
					fileImporter = new ReadMessenger("../" + args[0]);
					fileImporter->updateContent();

					for (int i = 1; i < fileImporter->getContent().size(); i++)
						storage.println(fileImporter->getContent()[i]);
					storage.updateContent();
					logger.println("Imported " + args[0] + " into local storage.");
					logger.updateContent();
					break;
				case CommandType::QUIT:
					return 0;
					break;
				case CommandType::DEBUG:

					break;
				case CommandType::WHAT_IS_AT:

					break;
				case CommandType::WHAT_IS:

					break;
				case CommandType::WHAT_IS_IN:

					break;
				case CommandType::COMMENT:
					logger.println(query->getArgs()[0]);
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
		stoi(north.substr(0, north.length() - 1)),
		stoi(east.substr(0, east.length() - 1)),
		stoi(south.substr(0, south.length() - 1)),
		stoi(west.substr(0, west.length() - 1))
	);
}