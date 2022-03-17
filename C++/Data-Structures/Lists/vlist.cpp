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

// V L I S T . C P P

#include "vlist.h"
using namespace std;


///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: vlist
//Precondition: Constructor has not been invoked.
//Postcondition: count = 0; vector size is 9.
//Description: Constructs an instance of a vlist object.
///////////////////////////////////////////////////////////////////////////////////////////////
vlist::vlist(){
	cout << "\nDefault Constructor Invoked" << endl;
	count = 0;  // set initial count to 0 then resize array to 9:
	DB.resize(9);
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: vlist
//Precondition: A vlist object is being passed by reference.
//Postcondition: A hard copy of a vlist object has been created.
//Description: Creates a hard copy of a vlist object.
///////////////////////////////////////////////////////////////////////////////////////////////
vlist::vlist(const vlist & Org){
	cout << "\nCopyConstructor Invoked" << endl;
	DB = Org.DB; // copy over array and count to new obj:
	count = Org.count;
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: ~vlist
//Precondition: Destructor has not been invoked.
//Postcondition: Array DB deleted.
//Description: Deallocates memory of a vlist object.
///////////////////////////////////////////////////////////////////////////////////////////////
vlist::~vlist(){
	cout << "\nDestructor Invoked" << endl;
	DB.clear();  // clear all elements and then shrink to fit (to 0):
	DB.shrink_to_fit();
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: isEmpty
//Precondition: Whether vlist is empty or not is unknown.
//Postcondition: Whether vlist is empty or not is known.
//Description: Returns true if vlist is empty and false if not, based on count.
///////////////////////////////////////////////////////////////////////////////////////////////
bool vlist::isEmpty() {
	if (count == 0) { return true; }
	else { return false; } // simple bool from count variable
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: search
//Precondition: Item and its location in vlist are unknown.
//Postcondition: Item and its location, if exist in vlist, are known.
//Description: For-loop to analyze vector string and return iterator if key found.
///////////////////////////////////////////////////////////////////////////////////////////////
vector<string>::iterator vlist::search(const string& key) {
	//cout << "Searching for " << "\"" << key << "\"...";
	for (unsigned int i = 0; i < count; i++) {
		if (key == DB[i]) { // upon finding key return position and print output
			cout << "Item Found...  \t";
			return DB.begin() + i;
		}
	} // if not found:
	cout << "Item Not Found...  " << endl;
	return DB.begin();
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: insert
//Precondition: String key does not exist in vlist.
//Postcondition: String key is inserted into vlist in alphabetical order.
//Description: For-loop through array until alphabetically appropriate position is found, then
//			   inserts string key at start + i position in vlist - then updates count (++).
///////////////////////////////////////////////////////////////////////////////////////////////
void vlist::insert(const string & key){
	unsigned int i;
	for (i = 0; i < count; i++) {
		if (key <= DB[i]) { // upon finding alphabetical position for key, insert and update count
			DB.insert(DB.begin() + i, key);
			count++;
			return;
		}
	} // if no suitable positions in throughout the array then insert at the end:
	DB.insert(DB.begin() + i, key);
	count++;
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: remove
//Precondition: If key exists in vlist, it remains.
//Postcondition: If key exists in vlist, it is removed.
//Description: For-loop through vlist and if key found, use iterator to erase at position.
///////////////////////////////////////////////////////////////////////////////////////////////
void vlist::remove(const string& key){
	cout << "Removing " << "\"" << key << "\"...\t";
	for (unsigned int i = 0; i < count; i++) {
		if (key == DB[i]) {  // upon finding key, erase and update count
			vector<string>::iterator itr = search(key);
			DB.erase(itr);
			count--;
			cout << "Removed" << endl;
			return;
		}
	} // if not found:
	cout << "Item Not Found - Could not remove" << endl;
}


///////////////////////////////////////////////////////////////////////////////////////////////
//Function Name: print
//Precondition: Contents of vlist are unknown.
//Postcondition: Contents of vlist are output to console.
//Description: For-loop through array, each time outputs element at pos i to console, and if
//			   not at the end, uses comma separation.
///////////////////////////////////////////////////////////////////////////////////////////////
void vlist::print() {
	for (unsigned int i = 0; i < count; i++) {
		cout << DB[i]; // print each element
		if (i < count - 1) { cout << ", "; }
		else { cout << endl; } // if not the last element then use commas between
	}
}
