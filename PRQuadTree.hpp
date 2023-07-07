#pragma once
#ifndef PRQUAD_TREE_HPP
#define PRQUAD_TREE_HPP

#include <string>
#include <stack>
#include <exception>

using namespace std;

/*
	Follows the implementation at https://www.youtube.com/watch?v=OELWhbqaUWQ
	Work done by Michael
*/
namespace pr {
	struct DMS {
		unsigned long lat, lon;
		DMS(unsigned long lat, unsigned long lon);
	};

	class Region {
		bool isSplit = false;
		Region* parent, * sw, * nw, * se, * ne;
		DMS* start, * end;

		class Node {
			Region* context;
			DMS* coords;

		public:
			Node(Region* context, unsigned long lat, unsigned long lon);
			Node(Node* copy);
			Region* getContext();
			DMS* getCoords();
		};

		Node* referenceNode = nullptr;

	public:
		Region();
		Region(DMS* start, DMS* end);
		void insertNode(unsigned long lat, unsigned long lon);
		void setParent(Region*);
		//DMS* getStartCoords();
		DMS* getEndCoords();
		Region::Node* getReferenceNode();
	};

	class QuadTree {
		Region region;

	public:
		void insertNode(string latStr, string lonStr);
	};
}

#endif