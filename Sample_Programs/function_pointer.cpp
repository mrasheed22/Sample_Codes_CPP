/*
 * function_pointer.cpp
 *
 *  Created on: 16-Nov-2021
 *      Author: sands
 */

#include <iostream>
#include <stdlib.h>

using namespace std;

void fun(int a){
	cout <<a<< endl;
}

int main(int argc , char *argv[])
{
	/*void (*fun_ptr)(int) = &fun;
	(*fun_ptr)(786);*/

	void (*fun_ptr)(int) = fun;
	fun_ptr(786);
	return 0;
}


