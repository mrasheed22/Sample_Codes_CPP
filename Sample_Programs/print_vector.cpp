/*
 * print_vector.cpp
 *
 *  Created on: 16-Nov-2021
 *      Author: sands
 */

#include <iostream>
#include <vector>
#include <bits/stdc++.h>

using namespace std;

void print_vector(vector<int> v)
{
	for_each(v.begin(), v.end(),[](int i){
		cout <<i<<" ";
	});

	cout << endl;
}

int main()
{
	vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};

	print_vector(v);
	return 0;
}


