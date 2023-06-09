#pragma once
#ifndef COMMANDPROCESSOR_HPP
#define COMMANDPROCESSOR_HPP

#include "SystemManager.hpp"
#include <string>
#include <vector>
#include <iostream>

using namespace std;

//Work done by Michael

enum class CommandType {
	WORLD,
	IMPORT,
	QUIT,
	DEBUG,
	WHAT_IS_AT,
	WHAT_IS,
	WHAT_IS_IN,
	COMMENT
};

//Query is for each line processed. It separates each key word and eliminates the tabs.
class Query {
	bool commandTypeAssigned = false;
	CommandType type;
	vector<string> args;
	void processCommandType(string keyword);

public:
	Query(string);
	CommandType getCommandType();
	vector<string> getArgs();
};

class CommandProcessor : public ReadMessenger {
	vector<Query*> queries;

public:
	CommandProcessor(string);
	void updateContent() override;
	vector<Query*> getQueries();
};

#endif