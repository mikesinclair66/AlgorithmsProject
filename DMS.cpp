#include "DMS.hpp"

DMS::DMS(float lat, float lon) {
	this->lat = lat;
	this->lon = lon;
}

DMS::DMS(DMS* copy) {
	lat = copy->lat;
	lon = copy->lon;
}