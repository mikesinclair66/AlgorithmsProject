#ifndef Logger_h
#define Logger_h


#include <string>;

using namespace std;
class Logger {
public:
	Logger(char* filename_);
	void close();
	void log(string text);
	void logCmdLineNum(string text);
private:
	// keep file open since we most likely will write into it often
	fstream file;
	int lineNum;
};

#endif