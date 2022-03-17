//*****************************************************************************
//P R O G R A M  H E A D E R
//
//	Kristian Murphy
//  March 22, 2021
//
//	Description: This program accesses your C++ language skills.
//	After completing this assignment you will be able to perform the following:
//
//	(1) Manage a vector(allocatm and de-allocate memory, insert inorder, remove, etc).
//	(2) Implement a default constructor and a copy constructor.
//	(3) Implement an insert function to add a string, in order, into a vector
//	(4) Implement a remove function to delete a string from a vector
//******************************************************************************

// V L I S T . H

#include <iostream>
#include <vector> 
#include <string>
using namespace std;

#ifndef vlist_H
#define vlist_H

class vlist
{
public:
	vlist();
	vlist(const vlist&);
	~vlist();
	bool isEmpty();
	vector<string>::iterator search(const string&); 
	void insert(const string&);
	void remove(const string&); 
	void print();
private:
	vector<string> DB;
	int count;
};

#endif
