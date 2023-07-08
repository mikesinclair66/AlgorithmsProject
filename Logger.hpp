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
	fstream file;
	int lineNum;
};

#endif