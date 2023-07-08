#pragma once
#ifndef PRQUAD_TREE_HPP
#define PRQUAD_TREE_HPP

#include <string>
#include <vector>
#include <exception>
#include <math.h>
#include "DMS.hpp"

using namespace std;

/*
	Follows the implementation at https://www.youtube.com/watch?v=OELWhbqaUWQ
	Work done by Michael
*/
namespace pr {
	class Region {
		bool isSplit = false;
		vector<Region> subregions;//ne, se, sw, nw
		DMS* start, * end;
		void testSubregionForInsert(float lat, float lon);

		class Node {
			Region* context = nullptr;
			DMS* coords;

		public:
			Node(float lat, float lon);
			Node(Node* copy);
			~Node();
			void setContext(Region* context);
			Region* getContext();
			DMS* getCoords();
		};

		Node* internalNode = nullptr;

	public:
		Region(DMS* start, DMS* end);
		~Region();
		void insertNode(float lat, float lon);
		DMS* getStartCoords();
		DMS* getEndCoords();
	};

	class QuadTree {
		Region* region;
		float getSmallValue(int largeValue);

	public:
		~QuadTree();
		void defineRegion(int north, int east, int south, int west);
		void insertNode(int lat, int lon);
	};
}

#endif