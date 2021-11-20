/*
 * union_ex.cpp
 *
 *  Created on: 17-Nov-2021
 *      Author: sands
 */

#include <iostream>
using namespace std;

struct example2{
	int a = 5;
	char b = 'C';
	float c = 0.5;
};

union example1{
	int a;
	char b;
	float c;
};

int main()
{
	example1 ex1;
	ex1.a = 5;
	ex1.b = 'x';
	ex1.c = 0.5;

	cout <<sizeof(union example1)<< endl;
	cout <<sizeof(struct example2)<< endl;

	return 0;
}

