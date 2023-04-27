#pragma once

#include <string>
#include "CommandProcessor.hpp"
#include "Logger.hpp"

using namespace std;

namespace finalProject {
	class SysAdmin {
		string fileNames[3];
		CommandProcessor* cp;
		Logger* log;

	public:
		SysAdmin(string, string, string);
	};
}