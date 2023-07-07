#include "PRQuadTree.hpp"

using namespace pr;

DMS::DMS(float lat, float lon) {
	this->lat = lat;
	this->lon = lon;
}

DMS::DMS(DMS* copy) {
	lat = copy->lat;
	lon = copy->lon;
}

Region::Region(DMS* start, DMS* end) {
	this->start = start;
	this->end = end;
}

Region::~Region() {
	delete start;
	delete end;
	delete internalNode;
}

void Region::insertNode(float lat, float lon) {
	if (lat >= start->lat && lat < end->lat
		&& lon >= start->lon && lon < end->lon) {
		if (!isSplit) {
			if (internalNode == nullptr)
				internalNode = new Node(lat, lon);
			else {
				DMS halfDist((end->lat - start->lat) / 2.f, (end->lon - start->lon) / 2.f),
					halfNE(start->lat + halfDist.lat, start->lon + halfDist.lon);

				subregions.push_back(Region(new DMS(halfNE), end));//ne
				subregions.push_back(Region(new DMS(halfNE.lat, start->lon), new DMS(end->lat, halfNE.lon)));//se
				subregions.push_back(Region(start, new DMS(halfNE)));//sw
				subregions.push_back(Region(new DMS(start->lat, halfNE.lon), new DMS(halfNE.lat, end->lon)));//nw

				Node nodesInComparison[2] = {
					Node(internalNode),
					Node(lat, lon)
				};
				internalNode = nullptr;
				for (int n = 0; n < 2; n++) {
					DMS* nCoords = nodesInComparison[n].getCoords();
					testSubregionForInsert(nCoords->lat, nCoords->lon);
				}

				isSplit = true;
			}
		}
		else
			testSubregionForInsert(lat, lon);
	}
}

DMS* Region::getStartCoords() {
	return start;
}

DMS* Region::getEndCoords() {
	return end;
}

void Region::testSubregionForInsert(float lat, float lon) {
	for (int i = 0; i < 4; i++) {
		DMS* startCoords = subregions[i].getStartCoords(), * endCoords = subregions[i].getEndCoords();
		if (lat >= startCoords->lat && lat < endCoords->lat
			&& lon >= startCoords->lon && lon < endCoords->lon) {
			subregions[i].insertNode(lat, lon);
			break;
		}
	}
}

Region::Node::Node(float lat, float lon) {
	this->context = context;
	coords = new DMS(lat, lon);
}

Region::Node::Node(Node* copy) {
	context = copy->getContext();
	coords = copy->getCoords();
}

Region::Node::~Node() {
	delete context;
	delete coords;
}

void Region::Node::setContext(Region* context) {
	this->context = context;
}

Region* Region::Node::getContext() {
	return context;
}

DMS* Region::Node::getCoords() {
	return coords;
}

QuadTree::~QuadTree() {
	delete region;
}

float QuadTree::getSmallValue(int largeValue) {
	return sqrt(largeValue);
}

void QuadTree::defineRegion(int north, int east, int south, int west) {
	region = new Region(new DMS(getSmallValue(west), getSmallValue(south)),
		new DMS(getSmallValue(east), getSmallValue(north)));
}

void QuadTree::insertNode(int lat, int lon) {
	region->insertNode(getSmallValue(lat), getSmallValue(lon));
}