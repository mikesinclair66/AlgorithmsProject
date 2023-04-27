#include "GISRecord.hpp"

using namespace finalProject;

GISRecord::GISRecord(Command command) {
	this->command = command;
}

void GISRecord::setParams(string* params) {
	this->params = params;
}