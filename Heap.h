#pragma once
#include<stddef.h>
#include<iostream>
#include<exception>

template <typename T>

void myownswap(T& a, T& b) {
	T c = a;
	a = b;
	b = c;
}

template <typename T>

T min(T a, T b) {
	if (a < b)
		return a;
	return b;
}

template <typename T>

struct Node {
	T key;
	Node *Parent, *Left_child, *Right_child;
	Node(T x) : Parent(NULL), Left_child(NULL), Right_child(NULL), key(x) {}
	~Node() {
		if (Left_child != NULL)
			delete Left_child;
		if (Right_child != NULL)
			delete Right_child;
	}
};

template <typename T>

class Heap {
private:
	Node<T> *Root, *Last;
	int Size;
	void save_heap_up(Node<T> *Cur) {
		if (Cur == Root || Cur->Parent->key <= Cur->key)
			return;
		T save = Cur->key;
		Cur->key = Cur->Parent->key;
		Cur->Parent->key = save;
		save_heap_up(Cur->Parent);
	}
	Node<T> save_heap_up_node(Node<T> *Cur) {
		if (Cur == Root || Cur->Parent->key <= Cur->key)
			return Cur;
		T save = Cur->key;
		Cur->key = Cur->Parent->key;
		Cur->Parent->key = save;
		return save_heap_up(Cur->Parent);
	}
	void save_heap_down(Node<T> *Cur) {
		if (Cur->Left_child == NULL || Cur->key <= Cur->Left_child->key && Cur->Right_child == NULL || Cur->Right_child != NULL && Cur->key <= Cur->Right_child->key && Cur->key <= Cur->Left_child->key)
			return;
		if (Cur->key > Cur->Left_child->key && (Cur->Right_child == NULL || Cur->Right_child->key >= Cur->Left_child->key)) {
			myownswap(Cur->key, Cur->Left_child->key);
			save_heap_down(Cur->Left_child);
			return;
		}
		myownswap(Cur->key, Cur->Right_child->key);
		save_heap_down(Cur->Right_child);
	}
	Node<T> save_heap_down_node(Node<T> *Cur) {
		if (Cur->Left_child == NULL || Cur->key <= Cur->Left_child->key && Cur->Right_child == NULL || Cur->Right_child != NULL && Cur->key <= Cur->Right_child->key && Cur->key <= Cur->Left_child->key)
			return Cur;
		if (Cur->key > Cur->Left_child->key && (Cur->Right_child == NULL || Cur->Right_child->key >= Cur->Left_child->key)) {
			myownswap(Cur->key, Cur->Left_child->key);
			return save_heap_down(Cur->Left_child);
		}
		myownswap(Cur->key, Cur->Right_child->key);
		return save_heap_down(Cur->Right_child);
	}
public:
	Heap() : Root(NULL), Size(0), Last(NULL) {}
	Heap(T x) : Root(*Node<T>(x)), Size(1) {
		Last = Root;
	}
	int size() {
		return Size;
	}
	bool is_empty() const {
		return Size == 0;
	}
	void insert(T key) {
		if (Root == NULL) {
			Last = Root = new Node<T>(key);
			++Size;
			save_heap_up(Last);
			return;
		}
		if (Last == Root) {
			Last = new Node<T>(key);
			Root->Left_child = Last;
			Last->Parent = Root;
			if (Root->key > Last->key)
				myownswap(Root->key, Last->key);
			++Size;
			save_heap_up(Last);
			return;
		}
		++Size;
		int x = Size >> 1, cnt = -1;
		while (x) {
			++cnt;
			x >>= 1;
		}
		x = Size;
		Node<T> *Cur = Root;
		while (cnt) {
			if ((x >> cnt) & 1)
				Cur = Cur->Right_child;
			else
				Cur = Cur->Left_child;
			--cnt;
		}
		Last = new Node<T>(key);
		if (x & 1)
			Cur->Right_child = Last;
		else
			Cur->Left_child = Last;
		Last->Parent = Cur;
		save_heap_up(Last);
	}
	Node<T> insert_node(T key) {
		if (Root == NULL) {
			Last = Root = new Node<T>(key);
			++Size;
			return save_heap_up_node(Last);
		}
		if (Last == Root) {
			Last = new Node<T>(key);
			Root->Left_child = Last;
			Last->Parent = Root;
			if (Root->key > Last->key)
				myownswap(Root->key, Last->key);
			++Size;
			return save_heap_up_node(Last);
		}
		++Size;
		int x = Size >> 1, cnt = -1;
		while (x) {
			++cnt;
			x >>= 1;
		}
		x = Size;
		Node<T> *Cur = Root;
		while (cnt) {
			if ((x >> cnt) & 1)
				Cur = Cur->Right_child;
			else
				Cur = Cur->Left_child;
			--cnt;
		}
		Last = new Node<T>(key);
		if (x & 1)
			Cur->Right_child = Last;
		else
			Cur->Left_child = Last;
		Last->Parent = Cur;
		return save_heap_up_node(Last);
	}
	T get_min() const {
		try {
			if (is_empty()) {
				throw std::out_of_range("the heap is empty, can't get_min\n");//ошибка если куча пуста
			}
			else {
				return Root->key;
			}
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return NULL;
		}
	}
	T extract_min() {
		try {
			if (is_empty()) {
				throw std::out_of_range("the heap is empty, can't get_min\n");//ошибка если куча пуста
			}
			else {
				T Min_key = Root->key;
				if (Root == Last) {
					delete Root;
					Root = Last = NULL;
					--Size;
					return Min_key;
				}
				Root->key = Last->key;
				if (Last->Parent->Right_child == NULL)
					Last->Parent->Left_child = NULL;
				else
					Last->Parent->Right_child = NULL;
				delete Last;
				//Last = NULL;
				--Size;
				int x = Size >> 1, cnt = -1;
				while (x) {
					++cnt;
					x >>= 1;
				}
				x = Size;
				Node<T> *Cur = Root;
				while (cnt >= 0) {
					if ((x >> cnt) & 1)
						Cur = Cur->Right_child;
					else
						Cur = Cur->Left_child;
					--cnt;
				}
				Last = Cur;
				save_heap_down(Root);
				return Min_key;
			}
		}
		catch (std::exception& e) {
			std::cerr << e.what() << '\n';
			return NULL;
		}
	}
	void del(Node<T> x) {
		int save = x->key;
		x->key = Root->key;
		Root->key = save;
		H.extract_min();
		H.save_heap_up(x);
	}
	void change(Node<T> x, T k) {
		x->key = k;
		H.save_heap_down(x);
		H.save_heap_up(x);
	}
	~Heap() {
		if (Root != NULL)
			delete Root;
	}
};
