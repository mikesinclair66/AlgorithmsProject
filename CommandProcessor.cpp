#include "CommandProcessor.hpp"

Query::Query(string line) {
	if (line.at(0) == ';') {
		type = CommandType::COMMENT;
		args.push_back(line);
		return;
	}

	//should have separate loop for the keyword enum and remaining args
	string keyword = "";
	for(char c : line)
		if (c == '\t') {
			if (!commandTypeAssigned) {
				commandTypeAssigned = true;
				processCommandType(keyword);
			}
			else
				args.push_back(keyword);
			keyword = "";
		}
		else
			keyword += c;

	//if the command type has been processed, we can assume the last word is an argument
	if (commandTypeAssigned)
		args.push_back(keyword);
	else
		processCommandType(keyword);
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

CommandType Query::getCommandType() {
	return type;
}

vector<string> Query::getArgs() {
	return args;
}

CommandProcessor::CommandProcessor(string fileName) : ReadMessenger(fileName) {}

void CommandProcessor::updateContent() {
	ReadMessenger::updateContent();
	for (string line : content) {
		if(line.at(0) != '\n' && line.at(0) != ';')
			queries.push_back(new Query(line));
	}
}

vector<Query*> CommandProcessor::getQueries() {
	return queries;
}