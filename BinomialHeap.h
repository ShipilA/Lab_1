#pragma once
#include<stddef.h>
#include<iostream>
#include<exception>

template <typename T>

struct Node {
	T key;
	int cnt_children;//degree of the Node
	Node *Parent, *Left_child, *Right_brother;
	Node(T x) : Parent(NULL), Left_child(NULL), Right_brother(NULL), key(x), cnt_children(0) {}
};

template <typename T>

struct BinTree {
	int k;//height
	Node<T> *Root;
	BinTree *Right;
	BinTree() : Root(NULL), Right(NULL), k(0) {}
	void merge(BinTree &otherTree) {
		otherTree.Root->Parent = Root;
		otherTree.Root->Right_brother = Root->Left_child;
		Root->Left_child = otherTree.Root;
		++k;
	}
	~BinTree() {
		delete Root;
		delete Right;
	}
};

template <typename T>

class BinomialHeap
{
	BinTree<T> *Head;
	void merge_line(BinomialHeap &otherHeap) {
		BinTree<T> *i = Head, *j = otherHeap.Head, *save;
		if (i == NULL || i->Root == NULL) {
			Head = otherHeap.Head;
		}
		while (j != NULL && j->Root != NULL && i != NULL) {
			if (j->Root->key >= i->Root->key) {
				if (i->Right == NULL || j->Root->key <= i->Right->Root->key) {
					save = i->Right;
					i->Right = j;
					i = j->Right;
					j->Right = save;
					save = i;
					i = j;
					j = save;
				}
				else
					i = i->Right;
			}
			else if (j->Root->key < i->Root->key && i == Head) {
					Head = j;
					save = j->Right;
					j->Right = i;
					i = j;
					j = save;
			}
		}
	}
public:
	~BinomialHeap() {
		if (Head != NULL)
			delete Head;
	}
	BinomialHeap() : Head(NULL) {}
	bool is_empty() const {
		return Head == NULL;
	}
	T get_min() const {
		try {
			if (is_empty()) {//mistake in case heap is empty
				throw std::out_of_range("the heap is empty, can't get_min\n");
			}
			else {
				T ans = Head->Root->key;
				BinTree<T> *cur = Head;
				while (cur->Right != NULL && cur->Right->Root != NULL) {
					cur = cur->Right;
					if (cur->Root->key < ans)
						ans = cur->Root->key;
				}
				return ans;
			}
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return NULL;
		}
	}
	void merge(BinomialHeap &otherHeap) {
		merge_line(otherHeap);
		if (Head == NULL)
			return;
		BinTree<T> *prev = NULL, *cur = Head, *next = Head->Right;
		while (next != NULL && next->Root != NULL) {
			if (cur->k != next->k || next->Right != NULL && next->Right->k == cur->k) {
				prev = cur;
				cur = next;
			}
			else if (cur->Root->key <= next->Root->key) {
				cur->Right = next->Right;
				cur->merge(*next);
			}
			else {
				if (prev == NULL)
					Head = next;
				else
					prev->Right = next;
				next->merge(*cur);
				cur = next;
			}
			next = cur->Right;
		}
	}
	void insert(T key) {
		BinomialHeap<T> *NewH = new BinomialHeap<T>();
		NewH->Head = new BinTree<T>();
		NewH->Head->Root = new Node<T>(key);
		NewH->Head->k = 1;
		merge(*NewH);
	}
	T extract_min() {
		try {
			if (is_empty()) {//mistake in case empty
				throw std::out_of_range("the heap is empty, can't get_min\n");
			}
			else {
				BinTree<T> *cur = Head, *prev = NULL;
				T min_key = get_min();
				while (cur->Root->key != min_key) {
					prev = cur;
					cur = cur->Right;
				}
				if (prev != NULL)
					prev->Right = cur->Right;
				else
					Head = cur->Right;
				BinomialHeap<T> *NewH = new BinomialHeap<T>();
				NewH->Head = new BinTree<T>();
				Node<T> *help_cur = cur->Root->Left_child;
				cur = NewH->Head;
				cur->Root = help_cur;
				while (help_cur != NULL) {
					cur->Root = help_cur;
					cur->Right = new BinTree<T>();
					cur = cur->Right;
					help_cur = help_cur->Right_brother;
				}
				merge(*NewH);
				delete cur;
				delete prev;
				delete NewH;
				delete help_cur;
				return min_key;
			}
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return NULL;
		}
	}
};

