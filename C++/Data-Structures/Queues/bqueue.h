/********************************************************************************************

Kristian Murphy
3/12/21
Tests the capabilities of implemented doubly-linked circularized list of
integers in a "queue" that can be printed, added to the back and removed from
the front

*********************************************************************************************/

#include <iostream>
#include <string>

using namespace std;


#ifndef BQUEUE_H
#define BQUEUE_H

class bqnode
{
public:
	int priority;
	bqnode* prev, * next;
};

class bqueue
{
public:
	bqueue(){/*cout<<"Inside Default Constructor\n"*/; front = 0; } // Changed to inline (just initialize front to 0/empty)
	~bqueue(){ while (front != 0) { dequeue(); } }; // Changed to inline (loop dequeue until queue is empty)
	bqueue(const bqueue& t);
	void enqueue(int p);
	void dequeue();
	void print();
private:
	bqnode* front;//use ONLY one pointer
};

#endif
