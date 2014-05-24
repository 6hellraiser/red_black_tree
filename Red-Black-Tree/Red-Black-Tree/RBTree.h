#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <list>
#ifndef NODE_H
#define NODE_H
#include "Node.h"
#endif

template <class T> class Tree {
private:
	node<T> *root;
	node<T> *nil;
	const int RED = 1;
	const int BLACK = 0;
	std::list<node<T> *> nodes;

	void form_list(node<T>* x) {
		if (!isEmpty()) {
			nodes.push_back(x);
			if (x->left != nil) {
				form_list(x->left);
			}
			if (x->right != nil) {
				form_list(x->right);
			}
		}
	}

	bool isEmpty() {
		return (root == nullptr);
	}

	node<T> *find(node<T>* n, T key) {
		if (isEmpty()) {
			return nullptr;
		}
		else {
			if (n != NULL) {
				if (key == n->key)
					return n;
				if (key > n->key)
					return find(n->right, key);
				if (key < n->key)
					return find(n->left, key);
			}
		}
		return nullptr;
	}

	void display_found(node<T>* found) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
			for (list<node<T> *>::iterator i = nodes.begin(); i != nodes.end(); i++) {
				if ((*i) == found) {
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 2));
					std::cout << "(" << (*i)->key << " ";
					(*i)->color == RED ? std::cout << "r" : std::cout << "b";
					std::cout << ") ";
					SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
				}
				else {
					std::cout << "(" << (*i)->key << " ";
					(*i)->color == RED ? std::cout << "r" : std::cout << "b";
					std::cout << ") ";
				}
			}
	}

	void left_rotate(node<T>* x) {
		node<T> *y;
		y = x->right;
		x->right = y->left;

		if (y->left != nil) {
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

		if (y->right != nil) { 
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

	void tree_delete_fixup(node<T>* x) {
		node<T>* w;
		while (x != root && x->color == BLACK) {
			if (x == x->parent->left) {
				w = x->parent->right;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					left_rotate(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == BLACK && w->right->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->right->color == BLACK) {
						w->left->color = BLACK;
						w->color = RED;
						right_rotate(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->right->color = BLACK;
					left_rotate(x->parent);
					x = root;
				}
			}
			else {
				w = x->parent->left;
				if (w->color == RED) {
					w->color = BLACK;
					x->parent->color = RED;
					right_rotate(x->parent); 
					w = x->parent->left;
				}
				if (w->right->color == BLACK && w->left->color == BLACK) {
					w->color = RED;
					x = x->parent;
				}
				else {
					if (w->left->color == BLACK) {
						w->right->color = BLACK;
						w->color = RED;
						left_rotate(w); 
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = BLACK;
					w->left->color = BLACK;
					right_rotate(x->parent);
					x = root;
				}
			}
		}
		x->color = BLACK;
	}

	node<T>* tree_minimum(node<T>* x) {
		while (x->left != nil) {
			x = x->left;
		}
		return x;
	}

	node<T>* tree_successor(node<T>* x) {
		if (x->right != nil) {
			return tree_minimum(x->right);
		}
		node<T>* y = x->parent;
		while (y != nil && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	node<T>* tree_delete(node<T>* z) {
		node<T>* y;
		node<T>* x;
		if (z->left == nil || z->right == nil) {
			y = z;
		}
		else {
			y = tree_successor(z);
		}
		if (y->left != nil) {
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

	void display_tree() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		for (list<node<T> *>::iterator i = nodes.begin(); i != nodes.end(); i++) {
			std::cout << "(" << (*i)->key << " ";
			(**i).color == RED ? std::cout << "r" : std::cout << "b";
			std::cout << ") ";
		}
	}

	void tree_insert(node<T>* z) {
		node<T>* y = nullptr;
		node<T>* x = root;
		while (x != nil) {
			y = x;
			if (z->key < x->key) {
				x = x->left;
			}
			else {
				x = x->right;
			}
		}
		z->parent = y;
		if (y == nullptr) {
			root = z;
		}
		else {
			if (z->key < y->key) {
				y->left = z;
			}
			else {
				y->right = z;
			}
		}
	}

public:
	Tree() {
		nil = new node<T>(BLACK);
		root = nil;
	}

	node<T> *find(T key, bool display) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << "Find " << key << "\n";
		node<T> *found = find(root, key);
		if (display) {
			cout << "Displaying tree...";
			display_found(found);
		}
		return found;
	}

	void display() {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << "Displaying tree...";
		display_tree();
	}

	void rb_insert(T key) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << "Insert " << key << "\n";

		node<T>* x = new node<T>(RED, key);
		x->left = nil; 
		x->right = nil;
		tree_insert(x);
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
						right_rotate(x);
					}
					x->parent->color = BLACK;
					x->parent->parent->color = RED;
					left_rotate(x->parent->parent);
				}
			}
		}
		root->color = BLACK;
		nodes.clear();
		form_list(root);
	}

	void tree_delete(T key) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hConsole, (WORD)((0 << 4) | 15));
		cout << "Delete " << key << "\n";
		node<T> *z = find(key, false);
		delete(tree_delete(z));
		nodes.clear();
		form_list(root);
	}
};