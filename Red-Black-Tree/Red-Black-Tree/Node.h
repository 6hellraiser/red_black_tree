#include "stdafx.h"
#ifndef RBTREE_H
#define RBTREE_H
#include "RBTree.h"
#endif

template <class T> class node {
private:
	int color; // 0-black, 1-red
	T key;
	node* left;
	node* right;
	node* parent;

	template <class T>
	friend class Tree;

public:
	node<T>(int _color, T _key):color(_color),key(_key) {
		
	}

	node<T>(int _color) : color(_color) {}

};