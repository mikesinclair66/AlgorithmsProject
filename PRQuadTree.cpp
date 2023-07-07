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

		start = new DMS(west, south);
		end = new DMS(east, north);

		DMS halfDist((east - west) / 2ul, (north - south) / 2ul);
		sw = new Region(start, new DMS(west + halfDist.lat, south + halfDist.lon));
		nw = new Region(new DMS(west, south + halfDist.lon), new DMS(west + halfDist.lat, north));
		se = new Region(new DMS(west + halfDist.lat, south), new DMS(east, south + halfDist.lon));
		ne = new Region(new DMS(west + halfDist.lon, south + halfDist.lon), end);
		sw->setParent(this);
		nw->setParent(this);
		se->setParent(this);
		ne->setParent(this);

		isSplit = true;
	}
	else {
		if (lat >= start->lat && lat < end->lat
			&& lon >= start->lon && lon < end->lon) {
			auto getWesternRegion = [](unsigned int lat, unsigned int lon, Region* nw, Region* sw) {
				return (lon >= nw->getEndCoords()->lon) ? sw : nw;
			};
			auto getEasternRegion = [](unsigned int lat, unsigned int lon, Region* ne, Region* se) {
				return (lon >= ne->getEndCoords()->lon) ? se : ne;
			};

			if (lat >= nw->getEndCoords()->lat)
				getWesternRegion(lat, lon, nw, sw)->insertNode(lat, lon);
			else
				getEasternRegion(lat, lon, ne, se)->insertNode(lat, lon);
		}
		else
			throw exception("Node reached the wrong boundary");
	}
}

void Region::setParent(Region* parent) {
	this->parent = parent;
}

/*
DMS* Region::getStartCoords() {
	return start;
}
*/

DMS* Region::getEndCoords() {
	return end;
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