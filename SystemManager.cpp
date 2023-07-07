#include "SystemManager.hpp"

TextMessenger::TextMessenger(string fileName) {
	this->fileName = fileName;
}

void TextMessenger::updateContent() {}

vector<string> TextMessenger::getContent() { return content; }

ReadMessenger::ReadMessenger(string fileName) : TextMessenger(fileName) {}

void ReadMessenger::updateContent() {
	TextMessenger::updateContent();
	string textLine;

	ifstream reader(fileName);
	while (getline(reader, textLine))
		content.push_back(textLine);

	reader.close();
}

WriteMessenger::WriteMessenger(string fileName) : TextMessenger(fileName) {}

void WriteMessenger::updateContent() {
	TextMessenger::updateContent();
	ofstream writer(fileName);

	if (!writer)
		throw invalid_argument(fileName + " could not be opened.");
	for (string line : content)
		writer << line << endl;

	writer.close();
}