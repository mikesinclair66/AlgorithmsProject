#include "SysAdmin.hpp"

using namespace finalProject;

SysAdmin::SysAdmin(string dbFile, string cmdFile, string logFile) {
	//init database
	cp = new CommandProcessor(cmdFile);
	log = new Logger(logFile);
}