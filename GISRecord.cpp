#include "GISRecord.hpp"

GISRecord::GISRecord(string& line) : GISRecord(line, -1) {}
GISRecord::GISRecord(string& line, int offset_) : strForm(line), offset(offset_) {
	string field;
	/*
	istringstream lineStream(line);
	while(getline(lineStream, field, '|')) {
		fields.push_back(field);
	}
	*/

	primaryKey = GISRecord::generatePrimaryKey(fields[FEATURE_NAME], fields[STATE_ALPHA]);
}

string GISRecord::toStr() {
	return strForm;
}

string GISRecord::getPrimaryKey() {
	return primaryKey;
}

string GISRecord::generatePrimaryKey(string featureName, string stateAlpha) {
	return featureName + "-" + stateAlpha;
}

string GISRecord::operator[](GISFields field) {
	return fields[field];
}

int GISRecord::getOffset() {
	return offset;
}