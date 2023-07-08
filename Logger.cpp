#include "Logger.hpp"

Logger::Logger(char* filename_) : lineNum(1) {
	file.open(filename_, std::fstream::out | std::fstream::trunc);
}

void Logger::close() {
	file.close();
}


void Logger::log(string text) {
	file << text << endl;
}

void Logger::logCmdLineNum(string text) {
	log("Command " + to_string(lineNum) + ": " + text);
	lineNum++;
}