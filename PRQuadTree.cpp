#include "PRQuadTree.hpp"

using namespace pr;

DMS::DMS(unsigned long lat, unsigned long lon) {
	this->lat = lat;
	this->lon = lon;
}

Region::Region() {
	parent = nullptr;
}

Region::Region(DMS* start, DMS* end) {
	this->start = start;
	this->end = end;
}

void Region::insertNode(unsigned long lat, unsigned long lon) {
	if (referenceNode == nullptr)
		referenceNode = new Node(this, lat, lon);
	else if(!isSplit) {
		Node n1 = Node(referenceNode), n2(this, lat, lon);
		referenceNode = nullptr;

		unsigned long north, east, west, south;
		if (n1.getCoords()->lon >= n2.getCoords()->lon) {
			north = n1.getCoords()->lon;
			south = n2.getCoords()->lon;
		}
		else {
			north = n2.getCoords()->lon;
			south = n1.getCoords()->lon;
		}
		if (n1.getCoords()->lat >= n2.getCoords()->lat) {
			east = n1.getCoords()->lat;
			west = n2.getCoords()->lat;
		}
		else {
			east = n2.getCoords()->lat;
			west = n1.getCoords()->lat;
		}

		DMS halfDist((east - west) / 2ul, (north - south) / 2ul);
		sw = new Region(new DMS(west, south), new DMS(west + halfDist.lat, south + halfDist.lon));
		nw = new Region(new DMS(west, south + halfDist.lon), new DMS(west + halfDist.lat, north));
		se = new Region(new DMS(west + halfDist.lat, south), new DMS(east, south + halfDist.lon));
		ne = new Region(new DMS(west + halfDist.lon, south + halfDist.lon), new DMS(east, north));
		sw->setParent(this);
		nw->setParent(this);
		se->setParent(this);
		ne->setParent(this);

		isSplit = true;
	}
	else {
		bool isEast = false, isNorth = false;

	}
}

void Region::setParent(Region* parent) {
	this->parent = parent;
}

Region::Node* Region::getReferenceNode() {
	return referenceNode;
}

Region::Node::Node(Region* context, unsigned long lat, unsigned long lon) {
	this->context = context;
	coords = new DMS(lat, lon);
}

Region::Node::Node(Node* copy) {
	context = copy->getContext();
	coords = copy->getCoords();
}

Region* Region::Node::getContext() {
	return context;
}

DMS* Region::Node::getCoords() {
	return coords;
}

void QuadTree::insertNode(string latStr, string lonStr) {
	region.insertNode(
		stoul(latStr.substr(0, latStr.size() - 1)),
		stoul(lonStr.substr(0, lonStr.size() - 1))
	);
}