#include "stdafx.h"
#ifndef NODE_H
#define NODE_H
#include "Node.h"
#endif

template <class T> class Tree {
private:
	node<T> *root;
	const int RED = 1;
	const int BLACK = 0;

	bool isEmpty() {
		return (root == nullptr);
	}

	node<T> *find(node<T>* n, T key) {
		if (isEmpty()) {
			return nullptr;
		}
		else {
			if (key == n->key)
				return n;
			if (key > n->key)
				return find(n->right, key);
			if (key < n->key)
				return find(n->left, key);
		}
		return nullptr;
	}

	void left_rotate(node<T>* x) {
		node<T> *y;
		y = x->right;
		x->right = y->left;

		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			root = y;
		}
		else {
			if (x == x->parent->left) {
				x->parent->left = y;
			}
			else {
				x->parent->right = y;
			}
		}
		y->left = x;
		x->parent = y;
	}

	void right_rotate(node<T>* x) {
		node<T>* y;
		y = x->left;
		x->left = y->right;

		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			root = y;
		}
		else {
			if (x == x->parent->right) {
				x->parent->right = y;
			}
			else {
				x->parent->left = y;
			}
		}
		y->right = x;
		x->parent = y;
	}

	void tree_delete_fixup(node<T>* x);

	node<T>* tree_minimum(node<T>* x) {
		while (x->left != nullptr) {
			x = x->left;
		}
		return x;
	}

	node<T>* tree_successor(node<T>* x) {
		if (x->right != nullptr) {
			return tree_minimum(x->right);
		}
		node<T>* y = x->parent;
		while (y != nullptr && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	tree_delete(node<T>* z) {
		node<T>* y, x;
		if (z->left == nullptr || z->right == nullptr) {
			y = z;
		}
		else {
			y = tree_successor(z);
		}
		if (y->left != nullptr) {
			x = y->left;
		}
		else
		{
			x = y->right;
		}
		x->parent = y->parent;
		if (y->parent == nullptr) {
			root = x;
		}
		else {
			if (y == y->parent->left) {
				y->parent->left = x;
			}
			else {
				y->parent->right = x;
			}
		}
		if (y != z) {
			z->key = y->key;
		}
		if (y->color == BLACK) {
			tree_delete_fixup(x);
		}
		return y;
	}

public:
	node<T> *find(T key) {
		return find(root, key);
	}

	void tree_insert(T key) {
		node<T>* x = new node<T>(RED, key);
		node<T>* y;
		while (x != root && x->parent->color == RED) {
			if (x->parent == x->parent->parent->left) {
				y = x->parent->parent->right;
				if (y->color == RED) {
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				}
				else {
					if (x == x->parent->right) {
						x = x->parent;
						left_rotate(x);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					right_rotate(x->parent->parent);
				}
			}
			else {
				y = x->parent->parent->left;
				if (y->color == RED) {
					x->parent->color = BLACK;
					y->color = BLACK;
					x->parent->parent->color = RED;
					x = x->parent->parent;
				}
				else {
					if (x == x->parent->left) {
						x = x->parent;
						left_rotate(x); //всё ли здесь правильно? О_о
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					right_rotate(x->parent->parent);
				}
			}
		}
		root->color = BLACK;
	}

	void tree_delete(T key) {
		node<T> *z = find(key);
		tree_delete(z);
	}
};