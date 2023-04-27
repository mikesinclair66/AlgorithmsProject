#include "CommandProcessor.hpp"

using namespace finalProject;

CommandProcessor::CommandProcessor(string fileName) {
	string textLine;

	ifstream reader(fileName);
	while (getline(reader, textLine)) {
        vector<string> entryList = splitEntry(textLine, "\t");
	}

	reader.close();
}

vector<string> CommandProcessor::splitEntry(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}