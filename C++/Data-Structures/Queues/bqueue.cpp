/********************************************************************************************

Kristian Murphy
3/12/21
Tests the capabilities of implemented doubly-linked circularized list of
integers in a "queue" that can be printed, added to the back and removed from
the front

*********************************************************************************************/

#include "bqueue.h"

using namespace std;

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  enqueue
Pre-Conditon: queue is unchanged
Post-Condition: queue has been added to with another node, factored into circular double links
Description:  If queue is empty, initializes node with given integer - otherwise adds it to a node in the back, and fixes the prev/next pointers in queue
																																						 */
void bqueue::enqueue(int p) {
	bqnode* n = new bqnode;
	n->priority = p;
	if (front == 0) { // check if queue empty and initialize queue if so
		front = n->prev = n->next = n;
	}
	else{ //  otherwise change the links between nodes to fit in new node
		front->prev->next = n;
		n->prev = front->prev;
		n->next = front;
		front->prev = n;
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  print
Pre-Conditon: elements of queue unknown
Post-Condition: elements of queue are printed to screen
Description:  loops through doubly-linked queue printing each integer and if back at the first node, stops - if queue empty, outputs "(empty)"
																																						 */
void bqueue::print() {
	if (front != 0) { // check if queue empty
		bqnode* current = front;
		do { // if not empty, loops through do-while until circles through to the front node again
			cout << current->priority << " ";
			current = current->next;
		} while (current != front);
	}
	else { // if empty print
		cout << "(empty)";
	}
	cout << endl;
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  dequeue
Pre-Conditon: queue is unchanged
Post-Condition: if not empty, queue has its first (or only) node removed
Description:  changes the prev/next pointers in the first node of queue before deleting it
																																						 */
void bqueue::dequeue() {
	if (front != 0) { // check if queue empty
		bqnode* d = front;
		if (front->next == front) { front = 0; }
		else { // change all pointer links before deletion
			front->prev->next = front->next;
			front->next->prev = front->prev;
			front = front->next;
		} // lastly, delete node
		delete d;
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  bqueue
Pre-Conditon: stack has all of its nodes
Post-Condition: top stack node has been removed
Description:  creates a temporary pointer to the top stack node, sets the top node to the next, and then deletes the node through that pointer
																																						 */
bqueue::bqueue(const bqueue& t) {
	bqnode* current = t.front;
	do { // use temporary node to loop through do-while in original queue and create new queue with same nodes and links (utilizing enqueue)
		enqueue(current->priority);
		current = current->next;
	} while (current != t.front);
}