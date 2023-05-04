#include "CommandProcessor.hpp"

Query::Query(string line) {
	string keyword = "";
	for(char c : line)
		if (c == '\t') {
			if (!commandTypeProcessed) {
				commandTypeProcessed = true;
				processCommandType(keyword);
			}
			else
				args.push_back(keyword);
			keyword = "";
		}
		else
			keyword += c;

	//if the command type has been processed, we can assume the last word is an argument
	if (commandTypeProcessed)
		args.push_back(keyword);
	else
		processCommandType(keyword);
}

void Query::printWords() {
	string line = "";
	switch (type) {
	case CommandType::WORLD:
		line = "world";
		break;
	case CommandType::IMPORT:
		line = "import";
		break;
	case CommandType::QUIT:
		line = "quit";
		break;
	case CommandType::DEBUG:
		line = "debug";
		break;
	case CommandType::WHAT_IS_AT:
		line = "what_is_at";
		break;
	case CommandType::WHAT_IS:
		line = "what_is";
		break;
	case CommandType::WHAT_IS_IN:
		line = "what_is_in";
		break;
	}

	for (string word : args)
		line += " " + word;
	cout << line << endl;
}

void Query::processCommandType(string keyword) {
	if (keyword == "world")
		type = CommandType::WORLD;
	else if (keyword == "import")
		type = CommandType::IMPORT;
	else if (keyword == "quit")
		type = CommandType::QUIT;
	else if (keyword == "debug")
		type = CommandType::DEBUG;
	else if (keyword == "what_is_at")
		type = CommandType::WHAT_IS_AT;
	else if (keyword == "what_is")
		type = CommandType::WHAT_IS;
	else if (keyword == "what_is_in")
		type = CommandType::WHAT_IS_IN;
}

CommandProcessor::CommandProcessor(string fileName) : ReadMessenger(fileName) {}

void CommandProcessor::updateContent() {
	ReadMessenger::updateContent();
	for (string line : content)
		queries.push_back(Query(line));
}

void CommandProcessor::printWords() {
	for (Query query : queries)
		query.printWords();
}