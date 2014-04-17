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

/*	int getColor(){
		return color;
	}
	void setColor(int _color) {
		color = _color;
	}
	
	T getKey() {
		return key;
	}
	void setKey(T _key) {
		key = _key;
	}

	node getLeft() {
		return left;
	}
	void setLeft(node _left) {
		left = _left;
	}

	node getRight() {
		return right;
	}
	void setRight(node _right) {
		right = _right;
	}

	node getParent() {
		return parent;
	}
	void setParent(node _parent) {
		parent = _parent;
	}*/
};