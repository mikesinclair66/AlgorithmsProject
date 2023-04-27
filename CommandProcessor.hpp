#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "GISRecord.hpp"

using namespace std;

namespace finalProject {
	vector<GISRecord> records;

	class CommandProcessor {
		vector<string> splitEntry(string, string);

	public:
		CommandProcessor(string);
	};
}