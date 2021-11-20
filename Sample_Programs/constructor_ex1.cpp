/*
 * constructor_ex1.cpp
 *
 *  Created on: 17-Nov-2021
 *      Author: sands
 */

#include <iostream>
using namespace std;

class cpy_cnstr{
private:
	int x, y;
public:
	cpy_cnstr(int a, int b){
		x = a;
		y = b;
	}

	cpy_cnstr(const cpy_cnstr &cpy){
		x = cpy.x;
		y = cpy.y;
	}

	void get_x(){
		cout <<x<< " ";
	}

	void get_y(){
		cout <<y<< endl;
	}
};

int main()
{
	cpy_cnstr c1(10, 20);
	cpy_cnstr c2 = c1;

	c2.get_x();
	c2.get_y();

	return 0;
}


