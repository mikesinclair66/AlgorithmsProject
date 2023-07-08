#pragma once
#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "SystemManager.hpp"

class Logger : public WriteMessenger {
public:
	Logger(string path);
	string getLineBreak();
	void queueLines(vector<string> lines);
	void println(string line) override;
};

#endif