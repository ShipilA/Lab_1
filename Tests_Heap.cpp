#include "stdafx.h"
#include <stdio.h>
#include "Heap.h"
#include<iostream>
#include <ctime>

bool Test1() {//checking insert() and is_empty()
	bool ok = 1;
	Heap<int> H;
	ok = ok && H.is_empty();
	H.insert(1);
	ok = ok && !H.is_empty();
	if (!ok)
		std::cout << "Test1 wasn't passed" << std::endl;
	return ok;
}

bool Test2() {//checking insert() and get_min()
	bool ok = 1;
	Heap<int> H;
	ok = ok && H.is_empty();
	H.insert(11);
	ok = ok && H.get_min() == 11;
	ok = ok && !H.is_empty();
	H.insert(1);
	ok = ok && H.get_min() == 1;
	ok = ok && !H.is_empty();
	H.insert(2);
	ok = ok && H.get_min() == 1;
	ok = ok && !H.is_empty();
	H.insert(9);
	ok = ok && !H.is_empty();
	ok = ok && H.get_min() == 1;
	if (!ok)
		std::cout << "Test2 wasn't passed" << std::endl;
	return ok;
}

bool Test3() {//checking insert() and extract_min()
	bool ok = 1;
	Heap<int> H;
	H.insert(12);
	H.insert(3);
	H.insert(5);
	H.insert(1);
	H.insert(13);
	H.insert(9);
	ok = ok && H.extract_min() == 1;
	ok = ok && H.extract_min() == 3;
	H.insert(7);
	ok = ok && H.extract_min() == 5;
	ok = ok && H.extract_min() == 7;
	ok = ok && H.extract_min() == 9;
	H.insert(9);
	ok = ok && H.extract_min() == 9;
	ok = ok && H.extract_min() == 12;
	ok = ok && H.extract_min() == 13;
	if (!ok)
		std::cout << "Test3 wasn't passed" << std::endl;
	return ok;
}

bool Test4() {//checking insert(), extract_min() and is_empty()
	Heap<int> H;
	bool ok = 1;
	ok = ok && H.is_empty();
	H.insert(9);
	ok = ok && !H.is_empty();
	H.insert(1);
	ok = ok && !H.is_empty();
	H.insert(13);
	ok = ok && !H.is_empty();
	H.insert(5);
	ok = ok && !H.is_empty();
	H.insert(12);
	ok = ok && !H.is_empty();
	H.insert(3);
	ok = ok && !H.is_empty();
	H.insert(7);
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 1;
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 3;
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 5;
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 7;
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 9;
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 12;
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 13;
	ok = ok && H.is_empty();
	if (!ok)
		std::cout << "Test4 wasn't passed" << std::endl;
	return ok;
}

bool Test5() {
	Heap<char> H;
	bool ok = 1;
	ok = ok && H.is_empty();
	H.insert('b');
	ok = ok && !H.is_empty();
	H.insert('a');
	ok = ok && !H.is_empty();
	H.insert('z');
	ok = ok && !H.is_empty();
	H.insert('s');
	ok = ok && !H.is_empty();
	H.insert('c');
	ok = ok && !H.is_empty();
	H.insert('d');
	ok = ok && !H.is_empty();
	H.insert('g');
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 'a';
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 'b';
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 'c';
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 'd';
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 'g';
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 's';
	ok = ok && !H.is_empty();
	ok = ok && H.extract_min() == 'z';
	ok = ok && H.is_empty();
	if (!ok)
		std::cout << "Test5 wasn't passed" << std::endl;
	return ok;
}

bool Test6() {//checking insert() and extract_min()
	bool ok = 1;
	Heap<int> H;
	H.insert(21);
	H.insert(3);
	H.insert(1);
	H.insert(11);
	H.insert(13);
	H.insert(9);
	ok = ok && H.extract_min() == 1;
	ok = ok && H.extract_min() == 3;
	H.insert(7);
	ok = ok && H.extract_min() == 7;
	ok = ok && H.extract_min() == 9;
	ok = ok && H.extract_min() == 11;
	H.insert(3);
	H.insert(5);
	ok = ok && H.extract_min() == 3;
	ok = ok && H.extract_min() == 5;
	ok = ok && H.extract_min() == 13;
	ok = ok && H.extract_min() == 21;
	if (!ok)
		std::cout << "Test6 wasn't passed" << std::endl;
	return ok;
}

bool Test7() {//checking insert() and extract_min() big test
	double start_time = clock();
	Heap<int> H;
	bool ok = 1;
	for (int i = 0; i < 100000; ++i) {
		H.insert(i);
	}
	for (int i = 0; i < 100000; ++i) {
		ok = ok && H.extract_min() == i;
	}
	long double end_time = clock();
	long double time = end_time - start_time; //time spent on the test
	std::cout << "Test7: " << time / 1000 << " seconds" << std::endl;
	if (!ok)
		std::cout << "Test7 wasn't passed" << std::endl;
	return ok;
}

bool Test8() {//checking insert() and extract_min() big test
	double start_time = clock();
	Heap<int> H;
	bool ok = 1;
	for (int i = 0; i < 1000000; ++i) {
		H.insert(i);
	}
	for (int i = 0; i < 1000000; ++i) {
		ok = ok && H.extract_min() == i;
	}
	long double end_time = clock();
	long double time = end_time - start_time; //time spent on the test
	std::cout << "Test8: " << time / 1000 << " seconds" << std::endl;
	if (!ok)
		std::cout << "Test8 wasn't passed" << std::endl;
	return ok;
}

int main() {
	bool ok = 1;
	ok = Test1() && Test2() && Test3() && Test4() && Test5() && Test6() && Test7() && Test8();
	if (ok)
		std::cout << "OK" << std::endl;
	else
		std::cout << "FAILED" << std::endl;
	return 0;
};
