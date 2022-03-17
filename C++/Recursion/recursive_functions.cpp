/********************************************************************************************

Kristian Murphy
3/29/21
This program tests the capabilities of basic recursive functions to find the
reversal of words (and compared to iterated loop) and whether they are palidromes

*********************************************************************************************/

#include <iostream>
#include <string>

using namespace std;

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  palindrome
Pre-Conditon: whether string s is palindrome or not is unknown
Post-Condition: whether string s is palindrome or not is known
Description: checks if front char is equal to back char of string, then calls itself recursively with string minus the front and back chars and repeats,
			 and once it gets to 0characters, it returns true (if it gets to 1, returns true and drops to 0) - if it ever returns false then it stops
			 and returns false for the whole function
																																						 */
bool palindrome(const string& s) {
	if (s.size() == 0) // if size is down to 0, finished
		return true;
	else if (s[0] == s[s.size()-1]) // if the front of the string is equal to the back:
		return(palindrome(s.substr(1,s.size()-2))); // return itself, but with string parameter front and back characters removed
	else
		return false; // returns false up the whole chain if not empty or equal
};

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  printReversal
Pre-Conditon: reversal of string has not been printed
Post-Condition: reversal of string has been returned/printed
Description:  first checks if string is 0 or 1 characters, which would just return s - if 2 or greater, it returns its own function with the whole string
			  without the first character and that first character added to the back of the string, looping recursively until all characters have been
			  carried over to the back
																																						 */
string printReversal(const string& s) {
	if (s.length() < 2)
		return s; // return original string if empty or only 1 character (reversal is the same)
	else // otherwise call recusively with the substring excluding the first and last characters PLUS the first character on the end:
		return printReversal(s.substr(1,s.length())) + s[0];
};

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  printIterReverse
Pre-Conditon: reversal of string has not been printed
Post-Condition: reversal of string has been returned/printed
Description:  simple for-loop with count as the size, decrementing down to 0 - count is used to append the characters of the new string one by one to the
			  new string, starting with the back of the old string, and then finally returning the newly reversed string
																																						 */
string printIterReverse(const string& s) {
	string p; // temp string p used for simple for-loop
	for (int i = s.size(); i >= 0; i--)
		p += s[i]; // use counter i to decrement down original string while appending (incrementing) new string resulting in reversed string
	return p;
};

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  main
Pre-Conditon: main driver has not been called
Post-Condition: main driver has been run/called
Description:  uses y/n user response to loop over and over with newly inputted strings - first asks for string, gets line, and then uses palindrome
			  function to print whether it is a palindrome, and then the recursive and iterated reversal functions to determine the reversals of the input
																																						 */
int main()
{
	string s = "";
	string response = "y"; // start with response y

	while (response == "y" || response == "Y") 
	{ // user input loop to try again
		cout << " please enter string: ";
		getline(cin, s);
		if (palindrome(s) == true) // if user input string is palindrome:
		{ // print to console whether or not it is a palindrome
			cout << s << " is a palindrome \n";
		}
		else
		{
			cout << s << " is a not palindrome \n";
		}
		// use recursive and iterative reversal functions, respectively - print each to console
		cout << "The Rec-reverse of \"" << s << "\" is \"" << printReversal(s) << "\"" << endl;
		cout << "The Iter-reverse of \"" << s << "\" is \"" << printIterReverse(s) << "\"" << endl;
		cout << endl << "Do you wish to continue (y or Y for yes; n or N for no ? ";
		cin >> response;
		cin.ignore();
	}
	return 0;
}