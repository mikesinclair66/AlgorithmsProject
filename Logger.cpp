#include "Logger.hpp"

Logger::Logger(string path) : WriteMessenger(path) {}

string Logger::getLineBreak() {
	return "-----------------------------------------------------------------------";
}

void Logger::queueLines(vector<string> lines) {
	for (string line : lines)
		WriteMessenger::println(line);
	updateContent();
}

void Logger::println(string line) {
	WriteMessenger::println(line);
	updateContent();
}