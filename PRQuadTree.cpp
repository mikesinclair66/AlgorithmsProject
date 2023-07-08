#include "PRQuadTree.hpp"

using namespace pr;

Region::Region(DMS* start, DMS* end) {
	this->start = start;
	this->end = end;
}

Region::~Region() {
	delete start;
	delete end;
	for (int i = 0; i < bucket.size(); i++) {
		Node* t = bucket.top();
		bucket.pop();
		delete t;
	}
}

void Region::insertNode(float lat, float lon) {
	if (lat >= start->lat && lat < end->lat
		&& lon >= start->lon && lon < end->lon) {
		if (!isSplit) {
			if (bucket.size() < BUCKET_SIZE) {
				Node* node = new Node(lat, lon);
				node->setContext(this);
				bucket.push(node);
			}
			else {
				DMS halfDist((end->lat - start->lat) / 2.f, (end->lon - start->lon) / 2.f),
					halfNE(start->lat + halfDist.lat, start->lon + halfDist.lon);

				subregions.push_back(Region(new DMS(halfNE), end));//ne
				subregions.push_back(Region(new DMS(halfNE.lat, start->lon), new DMS(end->lat, halfNE.lon)));//se
				subregions.push_back(Region(start, new DMS(halfNE)));//sw
				subregions.push_back(Region(new DMS(start->lat, halfNE.lon), new DMS(halfNE.lat, end->lon)));//nw

				vector<Node*> nodesInComparison;
				for (int i = 0; i < BUCKET_SIZE; i++) {
					nodesInComparison.push_back(bucket.top());
					bucket.pop();
				}
				nodesInComparison.push_back(new Node(lat, lon));

				for (int n = 0; n < nodesInComparison.size(); n++) {
					DMS* nCoords = nodesInComparison[n]->getCoords();
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
	return sqrt((float)largeValue);
}

void QuadTree::defineRegion(int north, int east, int south, int west) {
	region = new Region(new DMS(getSmallValue(west), getSmallValue(south)),
		new DMS(getSmallValue(east), getSmallValue(north)));
}

void QuadTree::insertNode(int lat, int lon) {
	region->insertNode(getSmallValue(lat), getSmallValue(lon));
}