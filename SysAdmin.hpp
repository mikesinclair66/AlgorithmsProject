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
	Work done by Michael
*/
class TextMessenger {
protected:
	string fileName;
	vector<string> content;
	
public:
	TextMessenger(string);
	virtual void updateContent();
	vector<string> getContent();
};

class ReadMessenger : public TextMessenger {
public:
	ReadMessenger(string);

	//reads data into content
	virtual void updateContent() override;
};

class WriteMessenger : public TextMessenger {
public:
	WriteMessenger(string);

	//writes data out from content
	virtual void updateContent() override;
};

#endif