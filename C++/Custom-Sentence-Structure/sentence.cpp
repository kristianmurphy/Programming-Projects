
#include "sentence.h"

using namespace std;

//*************************************************************************************************
//*************************************************************************************************
//	S E N T E N C E . c p p                                                                      */

/********************************************************************************************

Name: Kristian Murphy	Z#: Z23442202
Course: Date Structures and Algorithm Analysis (COP3530) Professor: Dr. Lofton Bullard
Due Date: 2/22/21	Due Time: 11:59
Total Points: 25 Assignment 5: Sentence program (Module 6 - Programming asssignment 5)

Description: Tests the implemented functionalities of my single-link structure list



*********************************************************************************************/

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  sentence (copy constructor)
Pre-Conditon: The front and back pointers and list elements have not been copied
Post-Condition: The front and back pointers and list elements have been copied
Description:  The function initiailizes the state (private data) in a new object copied from the original
                                                                                                                                                         */
sentence::sentence(const sentence& org) {
	front = back = NULL;
	word* copy = org.front;
	while (copy != NULL) {
		add_back(copy->term);
		copy = copy->next;
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  sentence (destructor)
Pre-Conditon: the sentence is unchanged
Post-Condition: the sentence is deleted from memory
Description:  The function uses a a temporary pointer temp to process each list element and a temporary pointer del to delete them
																																						 */
sentence::~sentence() {
	if (front != NULL) {
		word* temp = front;
		while (temp != NULL) {
			word* del = temp;
			temp = temp->next;
			delete del;
		}
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  stringtolist
Pre-Conditon: The string has not been processed
Post-Condition: The string has not been processed by the function and created as a singley-linked list
Description:  The function first checks for a simple string and creates a list by going through each character and adding to an element in the list until it
              hits a space
			  I created explicit constructor and operator= and realized that I could use this same implementation for each to process the strings into list
																																						 */
void sentence::stringtolist(const string& s) {
	front = back = NULL;
	string temp;
	if (s == " ") { temp = " "; add_back(temp); temp = ""; return; }
	if (s == "") { temp = ""; add_back(temp); return; }
	if (s.empty() == false) {

		bool prevspace = true;
		for (unsigned int i = 0; i < s.length(); i++) {
			if (s[i] == ' ') {
				if (prevspace == false && i > 0) { add_back(temp); } // adds previous characters if not space
				temp = " ";
				add_back(temp); // adds temp as a space, then resets for next word
				temp = "";
				prevspace = true;
			}
			else {
				temp += s[i];
				prevspace = false;
			}
		}
		if (temp != " " || temp != "" || prevspace == false) { add_back(temp); }
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  operator+
Pre-Conditon: The operator has not been overloaded
Post-Condition: The operator has been overloaded so that lists (sentence) can be added
Description:  The function just adds each element of sentence B so each sentence is combined to one
																																						 */
void sentence::operator+(sentence& B) {
	word* add = B.front;
	while (add != NULL) {
		add_back(add->term);
		add = add->next;
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  operator<<
Pre-Conditon: The operator has not been overloaded
Post-Condition: The operator has been overloaded so that lists (sentence) can be printed to out
Description:  The function goes through each element of the list and uses out << on each term one at a time, then returns all at once
																																						 */
ostream& operator<<(ostream& out, const sentence& org) {
	if (org.front != 0) {
		word* current = org.front;
		while (current != 0) {
			out << current->term;
			current = current->next;
		}
	}
	return out;
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  add_back
Pre-Conditon: The sentence has not been added to
Post-Condition: The sentence has been added to by the given string
Description:  The function uses the string passed in the function arguments to expand the sentence terms.  A temporary pointer is used to add a next pointer
			  to the back of the sentence using that string
																																						 */
void sentence::add_back(string& s) {
	if (isEmpty()) {
		front = new word;
		front->next = NULL;
		front->term = s;
		back = front;
	}
	else {
		word* add = new word;
		add->next = NULL;
		add->term = s;
		back->next = add;
		back = add;
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  length
Pre-Conditon: The length (num of characters) in the terms/words of the sentence is unknown
Post-Condition: The length (num of characters) in the terms/words of the sentence is returned
Description:  The function adds each number of characters from the terms one at a time to a temporary int and returns it at the end of calculation
																																						 */
int sentence::length() {
	word* current = front;
	int length = 0;
	while (current != NULL) {
		length += current->term.length();
		current = current->next;
	}
	return length;
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  isEqual
Pre-Conditon: Whether the given sentence is equal to original is unknown
Post-Condition: Whether the given sentence is equal to original is returned
Description:  The function checks the current object this against the argument sentence B one word at a time each, and returns false if there are any
			  differences in the terms.  Otherwise, returns true at the final line
																																						 */
bool sentence::isEqual(sentence& B) {
	word* checkB = B.front;
	word* checkthis = this->front;
	while (checkthis != NULL && checkB != NULL) {
		if (checkthis->term != checkB->term) { return false; }
		checkthis = checkthis->next;
		checkB = checkB->next;
	}
	return true;
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  remove
Pre-Conditon: The string given in function argument has not been removed from the sentence
Post-Condition: The string given in function argument has been removed from the sentence
Description:  The function goes through each word and overwrites the targeted string in the terms of the sentence.  If found, breaks past while loop and
			  overwrites front if found in the first term, otherwise deletes it within the sentence
																																						 */
void sentence::remove(const string& s) {
	word* current = front;
	word* prev = NULL;
	bool found = false;
	while (current != NULL && found == false) {
		if (current->term == s) { found = true; } // loops through until finding string in term
		else {
			prev = current;
			current = current->next;
		}
	}
	if (found) {
		if (front == current) { front = front->next; }
		else { prev->next = current->next; }
	}
	delete current; // deletion
}