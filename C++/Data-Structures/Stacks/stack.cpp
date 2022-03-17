/********************************************************************************************

Kristian Murphy
3/5/21
This program tests the capabilities of implemented stack, meant to convert postfix expression
into infix expression with parentheses via stack system in class

*********************************************************************************************/

#include "stack.h"

using namespace std;

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  pop
Pre-Conditon: stack has all of its nodes
Post-Condition: top stack node has been removed
Description:  creates a temporary pointer to the top stack node, sets the top node to the next, and then deletes the node through that pointer
																																						 */
void STACK::pop()
{
	/*cout<<"Inside pop \n";*/
	stack_node *p;
	
	if (s_top != 0)
	{// delete top
		p = s_top;
		s_top = s_top->next;
		delete p;
	}
	
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  convert
Pre-Conditon: string is in postfix expression form
Post-Condition: string has been analyzed  and has been turned into stack node infix expression form if no errors are detected
Description:  loops through the given postfix expression form string, checking for errors and if none are found calls push
																																						 */
void STACK::convert(const string& postfix) {
	errorCode = 0;       // - start with a fresh 0 code
	for (unsigned int i = 0; i < postfix.length(); i++) {

		              // Input error detection (code 1 - postfix spacing incorrect):
		if ((i + 1) % 2 == 0 && postfix[i] != ' ') { errorCode = 1; break; }
		if ((i + 1) % 2 != 0 && postfix[i] == ' ') { errorCode = 1; break; }
		
		          // Input error detection (code 4 - unrecognized symbols):
		if (isalpha(postfix[i]) == false && postfix[i] != '+' && postfix[i] != '-' && postfix[i] != '*' && postfix[i] != '/' && postfix[i] != ' '){
			errorCode = 4;
			break;
		}

		   // check for any errors before continue:
		if (errorCode != 0) { break; }
		
		// push operator/operand onto stack if not a space:
		if (postfix[i] != ' ') {
			stack_element op;
			op += postfix[i];
			push(op);
		}

	}
	// if the first stack element has a 'next' element, then there were too many operands to consider
	if (s_top->next != NULL) { errorCode = 3; }
	if (s_top->data == "+" || s_top->data == "-" || s_top->data == "*" || s_top->data == "/") { errorCode = 2; }

}



/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  push
Pre-Conditon: stack has a certain number of nodes, and top node
Post-Condition: new node is added to stack, and set as top
Description:  creates a new pointer to add a new node to stack, sets as top and sets next as the previous top node, then calls update to update the stack
																																						 */

void STACK::push(const stack_element & item)
{
	/*cout<<"Inside push \n";*/
	stack_node *p = new stack_node;

	p->data = item;
	p->next = s_top;
	s_top = p;
	update(); // update parentheses every time push has ran
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  update
Pre-Conditon: operator has not been processed in update
Post-Condition: operator has or has not been processed in update (if found)
Description:  if newly push-added top stack node is an operator, the update function takes the two operands below it and appends to a parenthesized
			  expression if no errors are found
																																						 */
void STACK::update() {
	// combine operators to parentheses
	stack_element operator1 = s_top->data;
	if (s_top->data == "+" || s_top->data == "-" || s_top->data == "*" || s_top->data == "/") {
		if (s_top->next == NULL || s_top->next->next == NULL) { errorCode = 2; }
		else {
			stack_element operand1 = s_top->next->data;
			stack_element operand2 = s_top->next->next->data;
			stack_element infix;
			infix.append("(");
			infix.append(operand2);
			infix.append(operator1);
			infix.append(operand1);
			infix.append(")");
			for (int i = 0; i < 3; i++) { pop(); }
			push(infix);
		}
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  print
Pre-Conditon: error message or stack has not been printed
Post-Condition: error message or stack has been printed
Description:  checks for error codes in the errorCode class variable and displays them if found - if error code 0 (no errors) then prints the stack
																																						 */
void STACK::print()
{
	/*cout<<"Inside print \n";*/
	if (errorCode == 0) {// code 0 (print stack)
		for (stack_node* p = s_top; p != 0; p = p->next)
		{
			cout << p->data;
		}
		cout << endl;
	}// error code messages:
	else if (errorCode == 1) {// code 1
		cout << "Invalid input - use a space between each operator and operand" << endl;
	}
	else if (errorCode == 2) {// code 2
		cout << "Invalid input - too many operators and not enough operands" << endl;
	}
	else if (errorCode == 3) {// code 3
		cout << "Invalid input - too many operands and not enough operators" << endl;
	}
	else if (errorCode == 4) {// code 4
		cout << "Invalid input - unrecognized symbols, use only alphabet and +-*/" << endl;
	}
	else {
		cout << "Unknown error" << endl;
	}
}

/*********************** FUNCTION HEADER ******************************************************************************************************************
Name:  top
Pre-Conditon: the top node of the stack has not been identified
Post-Condition: the top node of the stack has been returned through the function
Description:  if not empty, returns top node's data element through the function
																																						 */
stack_element STACK::top()
{
	/*cout<<"Inside top \n";*/

	if (s_top == 0)
	{// if no top, exit
		exit(1);
	}
	else
	{
		return s_top->data;
	}
}

