/********************************************************************************************

Kristian Murphy
3/5/21
This program tests the capabilities of implemented stack, meant to convert postfix expression
into infix expression with parentheses via stack system in class

*********************************************************************************************/

#include <iostream>
#include <string>

using namespace std;

#ifndef STACK_H
#define STACK_H

typedef string stack_element;

class stack_node
{
public:
	stack_element data;
	stack_node* next;
};

class STACK
{
public:
	STACK() {/*cout<<"Inside Default Constructor\n"*/; s_top = 0; }
	~STACK() {/*cout<<"Inside !stack \n";*/; clear(); }
	STACK(const string& postfix) { convert(postfix); }
	stack_element top();
	int errorCode; // stored variable of current error code
	void operator=(const string& postfix) { convert(postfix); }
	void pop(); // pops off the topmost stack element
	void push(const stack_element&);
	void update(); // process parenthesizing and appending of the stack elements
	void print(); // print error message or the contents of stack
	void clear(){ while (s_top != 0) { pop(); } } // loops through stack with pop each iteration
	void convert(const string& postfix); // converts a postfix expression to a parenthesized infix expression implemented in stack
private:
	stack_node* s_top;
};

#endif
