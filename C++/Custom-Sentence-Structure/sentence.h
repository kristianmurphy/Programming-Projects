
#include <iostream>
#include <string>

using namespace std;

//*************************************************************************************************
//*************************************************************************************************
//	S E N T E N C E . h                                                                          */

/********************************************************************************************

Kristian Murphy
2/22/21
Tests the implemented functionalities of my single-link structure list

*********************************************************************************************/

#ifndef SENTENCE_H
#define SENTENCE_H

class word
{
public:
	string term;
	word* next;
};

class sentence
{
public:
	sentence() { front = back = NULL; };                       //The default constructor will initialize your state variables. (****CONVERTED TO INLINE)
									 //The front of the linked list is initially set to NULL or 0; this implies a non-header node 
									//implementation of the link list.
	sentence(const string& s) { stringtolist(s); }  //Explicit-value constructor: This constructor will have one argument; (****CONVERTED TO INLINE)
							   //a C-style string or a C++ string representing the word to be created;
	sentence(const sentence& org);  // Copy Constructor: Used during a call by value, return, or initialization/declaration of a word object;
	~sentence();    //Destructor: The destructor will de-allocate all memory allocated for the word. Put the message 
				   //"destructor called\n" inside the body of the destructor.
	bool isEmpty() { return front == 0; } //inline implementation
	int length();  //Length: Determines the length of the word A; remember A is the current object;
	void add_back(string& s);
	friend ostream& operator<<(ostream& out, const sentence& A); //Overload the insertion operator as a friend function with chaining to print a word A;
	void operator=(const string& s) { stringtolist(s); }  // Overload the assignment operator as a member function to take a  (****CONVERTED TO INLINE)
									 //string (C-style or C++ string, just be consistent in your implementation) as an argument and 
									//assigns its value to A, the current object;
	sentence& operator=(const sentence& w) { sentence k; return k; } // Overload the assignment operator as a member function with chaining to take a word 
								                                    //object as an argument and assigns its value to A, the current object;
	void operator+(sentence& B); //Overload the ‘+” operator as a member function without chaining to add word B 
					            //(adds the set of symbols that makep B's linked list to the back of A's linked list) to the back of word A; 
					           //remember A is the current object;
	bool isEqual(sentence& B);   //Returns true if two word objects are equal; otherwise false; remember A is the current
	void remove(const string& s); //Deletes the first occurrence of the string s from the list A;
	
	void stringtolist(const string& s); // I added to condense two indentical functions down to 1 call
private:
	word* front, * back;
};
// notes - added 1 member function stringtolist which helped to make 3 more functions implemented inline
#endif
