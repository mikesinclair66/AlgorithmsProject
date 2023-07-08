#include <iostream>
#include <string>
#include <chrono>
#include <ctime>
#include "SystemManager.hpp"
#include "CommandProcessor.hpp"
#include "PRQuadTree.hpp"
#include "Storage.hpp"
#include "Logger.hpp"

using namespace std;
using namespace pr;

/*
	CMake project build process - Michael Sinclair
*/

QuadTree tree;

void computeWorldCommand(string north, string east, string south, string west, Logger& logger);
string getSystemTime();

int main(int argc, char* argv[]) {
	if (argc == 4) {
		string db = argv[1], cmd = argv[2], log = argv[3];
		CommandProcessor cp("../" + cmd);
		cp.updateContent();

		Logger logger("../" + log);
		logger.queueLines(vector<string> {
			"Course project for COMP 8042",
			"Student participants: (Michael Sinclair, A01050793), Nam",
			"Beginning of GIS program log:",
			"database: " + db + ", commands: " + cmd + ", log: " + log,
			"Program ran at " + getSystemTime()
		});

		ReadMessenger* fileImporter;
		Storage storage("../" + db);

		for (Query* query : cp.getQueries())
			if (query != nullptr) {
				CommandType type = query->getCommandType();
				vector<string> args = query->getArgs();

				switch (query->getCommandType()) {
				case CommandType::WORLD:
					computeWorldCommand(args[3], args[1], args[2], args[0], logger);
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

		logger.println("Program run at " + getSystemTime());
		logger.updateContent();

		return 0;
	}
	else {
		cerr << "The run file must be executed with three arguments: <database> <commands> <logger>" << endl;
		return -1;
	}
}

void computeWorldCommand(string north, string east, string south, string west, Logger& logger) {
	signed int northI, eastI, southI, westI;
	northI = stoi(north.substr(0, north.length())) * (north.at(north.length() - 1) == 'S' ? -1 : 1);
	eastI = stoi(east.substr(0, east.length())) * (east.at(east.length() - 1) == 'W' ? -1 : 1);
	southI = stoi(south.substr(0, south.length())) * (south.at(south.length() - 1) == 'S' ? -1 : 1);
	westI = stoi(west.substr(0, west.length())) * (west.at(west.length() - 1) == 'W' ? -1 : 1);

	tree.defineRegion(northI, eastI, southI, westI);
	logger.queueLines(vector<string>{
		logger.getLineBreak(),
		"World boundaries are set to:",
		'\t' + to_string(northI),
		"    " + to_string(westI) + '\t' + to_string(eastI),
		'\t' + to_string(southI),
		logger.getLineBreak()
	});
}

string getSystemTime() {
	auto end = chrono::system_clock::now();
	time_t end_time = chrono::system_clock::to_time_t(end);
	return ctime(&end_time);
}