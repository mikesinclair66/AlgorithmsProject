#pragma once
#ifndef GISRECORD_HPP
#define GISRECORD_HPP

#include <string>
#include "DMS.hpp"

using namespace std;

class GISRecord {
	const string FEATURE_NAME, STATE;
	DMS* coords;
};

#endif