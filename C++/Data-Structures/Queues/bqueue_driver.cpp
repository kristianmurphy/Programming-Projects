/********************************************************************************************

Kristian Murphy
3/12/21
Tests the capabilities of implemented doubly-linked circularized list of
integers in a "queue" that can be printed, added to the back and removed from
the front

*********************************************************************************************/

#include<iostream>
#include "bqueue.h"

using namespace std;

int main()
{
	bqueue k;
	k.enqueue(60);
	k.print();
	k.enqueue(20);
	k.enqueue(30);
	k.print();
	k.enqueue(10);
	k.print();
	k.enqueue(50);
	k.enqueue(40);
	k.print();
	bqueue j = k;
	j.dequeue();
	j.print();
	j.dequeue();
	j.dequeue();
	j.dequeue();
	j.print();
	j.dequeue();
	j.dequeue();
	j.print();
	j.dequeue();
	j.dequeue();
	
	return 0;
}
