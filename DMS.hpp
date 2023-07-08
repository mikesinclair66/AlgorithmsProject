#pragma once
#ifndef DMS_HPP
#define DMS_HPP

struct DMS {
	float lat, lon;
	DMS(float lat, float lon);
	DMS(DMS* copy);
};

#endif