/*
 * thread_ex1.cpp
 *
 *  Created on: 19-Nov-2021
 *      Author: sands
 */

#include <iostream>
#include <thread>
#include <stdlib.h>

using namespace std;

//Function pointer
void fun_ptr(int i){
	cout <<i*2<< endl;
}

//Function Object
class fun_object{
public:
	void operator()(int x){ //oparator() is must. otherwise it will not work.
		cout <<x*3<< endl;
	}
};

int main()
{
	thread th1(fun_ptr, 1);
	thread th2(fun_object(), 1);

	auto f = [](int y){
		cout <<y*4<< endl;
	};

	thread th3(f, 1);

	//th1.join();
	//th2.join();
	//th3.join();

	//th1.detach();
	//thread becomes not joinable after detach() member function is called:
	//This function detaches a thread from the parent thread. It allows parent and child threads to be executed independently from each other.
	//After the call of detach() function, the threads are not synchronized in any way:

	thread::id id1 = th1.get_id(); //return thread id
	thread::id id2 = th2.get_id();
	thread::id id3 = th3.get_id();

	if(th1.joinable()){//better to check joinable before join
		th1.join();//This function returns only after all the threads are terminated. It means that the main thread will wait until child thread does not finish its execution:
		cout <<"th1-id:"<<id1<< endl;
	}
	if(th2.joinable()){
		th2.join();
		cout <<"th2-id:"<<id2<< endl;
	}
	if(th3.joinable()){
		th3.join();
		cout <<"th3-id:"<<id3<< endl;
	}

	return 0;
}
