/********************************************************************************************
Kristian Murphy
4/16/21
This program tests the capabilities of implemented binary search tree with class
member functions to manipulate the data within the tree
*********************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class treenode { // node for binary search tree
public:
	string county_name; //node information
	double population_size;
	treenode* lchild, * rchild; // left/right child pointers
};

class bst {
public:
	bst(); //store the data file (“county_data.txt”) into initial bst
	~bst() { empty_tree(); } //de-allocates dynamic memory allocate for tree bool empty()
	bool empty() { return (root == 0); } //return true if bst is null; otherwise false is retured
	void insert(const string& item, const double& population) {insert(root, item, population);} //auxiliary function
	void insert(treenode*& loc_ptr, const string& item, const double& population); //inserts an item into bst
	void del_name(string item) {del_name(root, item);} //auxiliary function
	void del_name(treenode*& loc_ptr, string item);   //function deletes an item from the bs
	treenode* search_tree(treenode* loc_ptr, string item) { return loc_ptr; } //returns a pointer to the node in bst with a county name county name that matches item
	treenode* search_tree(string item){return search_tree(root, item);} //auxiliary function, placeholder definition ^
	treenode* inorder_succ(treenode* loc_ptr); //returns a pointer to the inorder successor, based on county name
	void county_ranges(const string& min_name, const string& max_name) { county_ranges(root, min_name, max_name); } //auxiliary function
	void county_ranges(treenode*& loc_ptr, const string& min_name, const string& max_name); // prints all the county names to the screen that lie between min_name and max_name,  inclusive
	void print_tree() {print_tree(root);} //auxiliary function
	void print_tree(treenode*& loc_ptr); //prints each county record to the screen sorted by county name
	void empty_tree() { while (root != 0) { del_name(root->county_name); } } //de-allocate all nodes that were allocated to the bst
	void sorted_info();//auxiliary function
	void sorted_info(ostream& out, treenode*& loc_ptr); //prints each county record to a file called “county_info.txt” sorted by county name
private:
	treenode* root; //pointer to root of bst
};