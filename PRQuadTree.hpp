#pragma once
#ifndef PRQUAD_TREE_HPP
#define PRQUAD_TREE_HPP

namespace pr {
	class Node {
		Node* top, * left, * right;

	public:
		Node();
	};

	class QuadTree {
		Node top;
	};
}

#endif