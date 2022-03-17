
//Remember to put your program header in this file;
//Remember to include function name, pre/post conditions, and descriptions in all function headers;
//Remember to comment code if necessary to understand.

#include "sentence.h"

using namespace std;

/********************************************************************************************

Kristian Murphy
2/22/21
Tests the implemented functionalities of my single-link structure list

*********************************************************************************************/

int main()
{	
	cout << "****Test#1: default constructor, length, and operator<<***\n\n";
	sentence you;
	cout<<"\""<<you << "\"" <<" : length = "<<you.length()<< endl;
	cout<<"\n****End of Test#1*******************************************\n";
	cout<<endl;
	
	cout << "****Test#2: explicit-value constructor, length, and operator<<***\n\n";
	sentence me("Today is a wonderful day!   ");//sentence with 3 spaces at end
	cout<<"me is "<<"\""<<me<<"\""<<" =  "<<"\""<<"Today is a wonderful day!   "<<"\""<<"\n";
	cout << "The length of me is " << me.length() << "\n\n";
	sentence me_to("");
	cout << "me_to is " << "\"" << me_to << "\"" << " = " << "\""<< "\""<<"\n"; //sentence should be empty string
	cout << "The length of me_to is " << me_to.length() << "\n\n";
	sentence you_to(" ");
	cout << "you_to is " << "\"" << you_to << "\"" << " =  "<<"\"" <<" "<< "\"" << "\n";//sentence is one space
	cout << "The length of you_to is " << you_to.length() << "\n\n";
	cout << "****End of Test#2*******************************************\n";
	cout<<endl;
	
	cout << "****Test#3: copy constructor, length, isEqual, and operator<<***\n\n";
	sentence them = me;
	cout<<"them is "<<"\""<<them<<"\""<<"\n";
	cout << "The length of me is " << me.length()
	     << " = The length of them is " << them.length()<<"\n";
	cout <<"isEqual should equal 1 = "<< them.isEqual(me) << endl<<endl;
	cout << "****End of Test#3*******************************************\n";
	cout<<endl;
	
	cout<<"****TEST#4: overloaded operator= with string, and operator<<*******************\n\n";
	sentence us;
	us = "There are five racoons in the palm tree.";
	cout<<"Testing operator = by assigning the value of "<<
		"\""<<"There are five racoons in the palm tree."<<"\""<<"\n";
	cout<<"The sentence us is "<< "\""<<us<<"\""<<endl<<endl;
	cout<<"****End of Test#4*********************************************\n";
	cout<<endl;

	cout<<"****TEST#5: overloaded operator= with string, isEqual, and operator<<*********\n\n";
	sentence her, him;

	her = "I am very happy";
	him = "They are very happy";
	cout << "isEqual should equal 0 = " << her.isEqual(him) << endl;
	
	her = "";
	him = "";
	cout << "isEqual should equal 1 = " << her.isEqual(him) << endl;

	her = " ";
	him = " ";
	cout << "isEqual should equal 1 = " << her.isEqual(him) << endl;

	her = "";
	him = " ";
	cout << "isEqual should equal 0 = " << her.isEqual(him) << endl;

	her = "        ";
	him = "        ";
	cout << "isEqual should equal 1 = " << her.isEqual(him) << endl;

	her = "       ";
	him = "        ";
	cout << "isEqual should equal 0 = " << her.isEqual(him) << endl;

	cout << "****End of Test#5*********************************************\n";
	cout << endl;
	
	cout<<"****TEST#6: operator= with a string, operator+ with a sentence, and operator<<*****\n\n";
	cout<<"Adding 2 sentences by adding us to the back of their.  Their is the current object \n";
	sentence their("Everything ");
	us = "will be okay.";
	cout << "us = " <<"\""<< us <<"\""<<" and length = "<<us.length()<< endl;
	cout << "their = " <<"\""<< their <<"\""<<" and length = "<<their.length()<< endl;
	their + us;
	cout<<"their followed by us is "<< "\""<<their<< "\""<<" and length = " << their.length() << endl;

	cout << "us = " << "\"" << us << "\"" << " and length = " << us.length() << endl;
	cout << "their = " << "\"" << their << "\"" << " and length = " << their.length() << endl;
	us + their;
	cout << "us followed by their is " << "\"" << us << "\"" <<" and length = "<< us.length()<< endl;
	cout<<"*************************************************\n";
	cout<<endl<<endl;

	us = "123 456";
	their = "123";
	cout << "us = " << "\"" << us << "\"" << " and length = " << us.length() << endl;
	cout << "their = " << "\"" << their << "\"" << " and length = " << their.length() << endl;
	us + their;
	cout << "us followed by their is " << "\"" << us << "\"" << "and length = " << us.length() << endl;

	us = "123 456";
	their = "";
	cout << "us = " << "\"" << us << "\"" << " and length = " << us.length() << endl;
	cout << "their = " << "\"" << their << "\"" << " and length = " << their.length() << endl;
	their + us;
	cout << "their followed by us is " << "\"" << their << "\"" << "and length = " << their.length() << endl<<endl;
	cout << "****End of Test#6*********************************************\n\n";
	
	cout<<"****TEST#7: remove with a string without spaces, and operator<<*****\n\n";
	them = "";
	them.remove("123");
	cout << "\"" << them << "\"" << " length of them = " << them.length() << endl;
	them = "123";
	them.remove("123");
	cout <<"\""<< them<< "\"" << " length of them = "<<them.length()<<endl;
	them = "123 abc 124 abc 123 4567";
	them.remove("123");
	cout << "\""<<them <<"\""<< " length of them = " << them.length() << endl;
	them = "123 abc 124 abc 123 4567";
	them.remove("4567");
	cout <<"\""<< them <<"\"" " length of them = " << them.length() << endl;
	them = "123 abc 124 abc 123 4567";
	them.remove("124");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	them.remove(" ");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	them.remove(" ");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	them.remove(" ");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	them.remove(" ");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl;
	them.remove(" ");
	cout << "\"" << them << "\"" " length of them = " << them.length() << endl<<endl;
	cout << "****End of Test#7*********************************************\n";
	cout << endl;
	cout << "****TEST#8: operator= with a sentence object and operator<<*****\n\n";
	sentence h("123 456 780");
	them = h;
	cout << "right object = " << h << endl;
	cout << "them = "<<them << endl<<endl;
	cout << "****End of TEST#8****************************************\n\n";
	cout << "****End of Program*********************************************\n";
	
	return 0;
}
