#ifndef GISRecord_h
#define GISRecord_h

#include <vector>
#include <string>

using namespace std;

enum GISFields {
	FEATURE_ID,
	FEATURE_NAME,
	FEATURE_CLASS,
	STATE_ALPHA,
	STATE_NUMERIC,
	COUNTY_NAME,
	COUNTY_NUMERIC,
	PRIMARY_LAT_DMS,
	PRIM_LONG_DMS,
	PRIM_LAT_DEC,
	PRIM_LONG_DEC,
	SOURCE_LAT_DMS,
	SOURCE_LONG_DMS,
	SOURCE_LAT_DEC,
	SOURCE_LONG_DEC,
	ELEV_IN_M,
	ELEV_IN_FT,
	MAP_NAME,
	DATE_CREATED,
	DATE_EDITED
};

class GISRecord {
public:
	static string generatePrimaryKey(string featureName, string stateAlpha);

	GISRecord(string& line);

	GISRecord(string& line, int offset_);
	string toStr();
	string getPrimaryKey();
	string operator[](GISFields field);
	int getOffset();
private:
	vector<string> fields;
	string primaryKey;

	string strForm;

	int offset;

};

#endif