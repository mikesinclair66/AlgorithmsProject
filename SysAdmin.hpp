#pragma once
#ifndef TEXT_MESSENGER_HPP
#define TEXT_MESSENGER_HPP

#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>

using namespace std;

/*
	Parent components to use at the disposal of the database, command processor, and logger modules
	-Michael
*/
class TextMessenger {
protected:
	string fileName;
	vector<string> content;
	virtual void updateContent();
	
public:
	TextMessenger(string);
};

class ReadMessenger : public TextMessenger {
protected:
	//reads data into content
	void updateContent() override;

public:
	ReadMessenger(string);
};

class WriteMessenger : public TextMessenger {
protected:
	//writes data out from content
	void updateContent() override;

public:
	WriteMessenger(string);
};

#endif