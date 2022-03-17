/********************************************************************************************
Kristian Murphy
4/16/21
This program tests the capabilities of implemented binary search tree with class
member functions to manipulate the data within the tree
*********************************************************************************************/

#include "bst.h"

using namespace std;

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  bst
Pre-Conditon: default constructor has not been called
Post-Condition: default constructor has been called
Description:  the default constructor creates a binary tree with the insert function from the county data file for every line's county name and population
			  as a node, utilizing substrings when a number is detected to separate the name string and population double values
																																						 */
bst::bst() {
	ifstream in; //file stream
	string line, name;
	double pop;
	in.open("county_data.txt");
	while (getline(in, line)) {
		for (unsigned int i = 0; i < line.length(); i++) {
			if (line[i + 1] == '1' || line[i + 1] == '2' || line[i + 1] == '3' || line[i + 1] == '4' || line[i + 1] == '5' || line[i + 1] == '6' || line[i + 1] == '7' || line[i + 1] == '8' || line[i + 1] == '9') {
				name = line.substr(0,i);
				pop = stod(line.substr(i+1,line.length()));
				break;
			}
		}
		insert(name, pop);
	}
	in.close();
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  insert
Pre-Conditon: bst is unchanged
Post-Condition: bst has had a node added in certain placement according to the alphabetical importance of its county_name compared to the other nodes'
Description:  first checks if the pointer location parameter is null; if not, checks whether less than (left) or greater than (right) the current node and
			  calls recursively to check the next node - once down to a null child pointer, it creates a new node at that location with the name and pop
																																						 */
void bst::insert(treenode*& loc_ptr, const string& item, const double& population) {
	if (loc_ptr == 0) {
		loc_ptr = new treenode;
		loc_ptr->lchild = loc_ptr->rchild = 0;
		loc_ptr->county_name = item;
		loc_ptr->population_size = population;
	}
	else if (loc_ptr->county_name >item)
		insert(loc_ptr->lchild, item, population);
	else if (loc_ptr->county_name <item)
		insert(loc_ptr->rchild, item, population);
	else
		cout << "\nThe item is already in the tree\n";
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  del_name
Pre-Conditon: bst is unchanged
Post-Condition: bst has had a node removed based on the name parameter, item
Description:  recursively checks left and right children of each node in the bst, and notifies user if the given element was not found - if found, checked
			  left and right children, or else uses inorder_succ to replace the node and keep organization structure in bst
																																						 */
void bst::del_name(treenode * & loc_ptr, string item) {
	if (loc_ptr == 0)
		cout << "\nItem not in tree\n";
	else if (loc_ptr->county_name > item)
		del_name(loc_ptr->lchild, item);
	else if (loc_ptr->county_name < item)
		del_name(loc_ptr->rchild, item);
	else {
		treenode * ptr;
		if (loc_ptr->lchild == 0) {
			ptr = loc_ptr->rchild;
			delete loc_ptr;
			loc_ptr = ptr;
		}
		else if (loc_ptr->rchild == 0) {
			ptr = loc_ptr->lchild;
			delete loc_ptr;
			loc_ptr = ptr;
		}
		else {
			ptr = inorder_succ(loc_ptr);
			loc_ptr->county_name = ptr->county_name;
			del_name(loc_ptr->rchild, ptr->county_name);
		}
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  inorder_succ
Pre-Conditon: inorder successor unknown
Post-Condition: inorder successor returned through pointer
Description:  uses treenode pointer ptr to loop through lchild and return the inorder successor
																																						 */
treenode * bst::inorder_succ(treenode * loc_ptr) {
	treenode *ptr = loc_ptr->rchild;
	while (ptr->lchild != 0)
		ptr = ptr->lchild;
	return ptr;
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  print_tree
Pre-Conditon: tree is unknown
Post-Condition: tree is displayed to console
Description: recursively calls itself for every time a left and right child of a node is detected, and then prints in order from left to right for order
																																						 */
void bst::print_tree(treenode*& loc_ptr) {
	if (loc_ptr != 0){
		print_tree(loc_ptr->lchild);
		cout << loc_ptr->county_name << " " << loc_ptr->population_size << endl;
		print_tree(loc_ptr->rchild);
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  county_ranges
Pre-Conditon: counties in certain range unknown
Post-Condition: counties in certain range displayed to console
Description: recursively calls itself for every time a left and right child of a node is detected, and then prints in order from left to right for order
			 only if the name of the county to be printed is alphabetically less than or equal to the max_name and greater than or equal to the min_name
																																						 */
void bst::county_ranges(treenode*& loc_ptr, const string& min_name, const string& max_name) {
	if (loc_ptr != 0) {
		county_ranges(loc_ptr->lchild, min_name, max_name);
		if (loc_ptr->county_name >= min_name && loc_ptr->county_name <= max_name)
			cout << loc_ptr->county_name << " " << loc_ptr->population_size << endl;
		county_ranges(loc_ptr->rchild, min_name, max_name);
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  sorted_info
Pre-Conditon: bst nodes have not been saved
Post-Condition: bst nodes have been saved to new file, in alphabetical order
Description: opens county_info.txt through ofstream out and calls sorted_info to print to the file in alphabetical order from the bst
																																						 */
void bst::sorted_info() {
	ofstream out;
	out.open("county_info.txt");
	sorted_info(out, root);
	out.close();
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  sorted_info
Pre-Conditon: bst nodes have not been output
Post-Condition: bst nodes have been output in alphabetical order
Description: recursively calls upon itself to output nodes' names and population sizes from left to right, or alphabetical order
																																						 */
void bst::sorted_info(ostream& out, treenode*& loc_ptr) {
	if (loc_ptr != 0) {
		sorted_info(out, loc_ptr->lchild);
		out << loc_ptr->county_name << " " << loc_ptr->population_size << endl;
		sorted_info(out, loc_ptr->rchild);
	}
}