/*
 * Lab7.cpp
 *
 *  Created on: Apr 5, 2018
 *      Author: Jeffrey Schulz
 */

#include<iostream>
#include<fstream>
#include<iomanip>
#include<vector>
#include<string>
#include<cstdlib>
#include<cctype>

using namespace std;




//--------------------------------------------Message------------------------------------------------
class Message {
public:
	Message();
	Message(string message);
	virtual ~Message();
	virtual void print();
protected:
	string ENGmsg;
};


/**
 * Default constructor. Asks for user input for message.
 */
Message::Message() {
	cout << "\nType in a message: ";
	getline(cin,ENGmsg);
	int count = 0;
	for(auto i:ENGmsg) {
		ENGmsg[count++] = toupper(i);
	}
}


/**
 * Parametric constructor. For initializing message objects.
 */
Message::Message(string message) {
	int count = 0;
	ENGmsg = message;
	for(auto i:ENGmsg) {
		ENGmsg[count++] = toupper(i);
	}
}


/**
 * Message Destructor
 */
Message::~Message() {
	//
}


/**
 * Prints the message to the screen
 */
void Message::print() {
	cout << endl << ENGmsg;
}






//--------------------------------------------MorseCodeMessage------------------------------------------------
class MorseCodeMessage : public Message {
public:
	MorseCodeMessage();
	MorseCodeMessage(string);
	void translate();
	void print();
	string spitMorse(char);
private:
	string MORSEmsg;
};


/**
 * Constructs with Message constructor, but tacks on the translation function
 */
MorseCodeMessage::MorseCodeMessage() : Message() {
	translate();
}


/**
 * Constructs with Message constructor, but tacks on the translation function
 */
MorseCodeMessage::MorseCodeMessage(string msg) : Message(msg) {
	translate();
}


/**
 * Translates english to morse
 */
void MorseCodeMessage::translate() {
	if(ENGmsg.empty()) {
		cout << "\nENG message is empty. Did not translate.\n";
		return;
	}
	MORSEmsg.clear();
	for(auto i:ENGmsg) {
		if(i == ' ')
			MORSEmsg += "  ";
		else
			MORSEmsg += (spitMorse(i) + " ");
	}
}


/**
 * Nothing fancy here. The most boring and unoriginal function in this program.
 * Wanted to utilize the dichotomic search table, but that was taking too long.
 */
string MorseCodeMessage::spitMorse(char c) {
	if(c=='A')
		return ".-";
	else if(c=='B')
		return "-...";
	else if(c=='C')
		return "-.-.";
	else if(c=='D')
		return "-..";
	else if(c=='E')
		return ".";
	else if(c=='F')
		return "..-.";
	else if(c=='G')
		return "--.";
	else if(c=='H')
		return "....";
	else if(c=='I')
		return "..";
	else if(c=='J')
		return ".---";
	else if(c=='K')
		return "-.-";
	else if(c=='L')
		return ".-..";
	else if(c=='M')
		return "--";
	else if(c=='N')
		return "-.";
	else if(c=='O')
		return "---";
	else if(c=='P')
		return ".--.";
	else if(c=='Q')
		return "--.-";
	else if(c=='R')
		return ".-.";
	else if(c=='S')
		return "...";
	else if(c=='T')
		return "-";
	else if(c=='U')
		return "..-";
	else if(c=='V')
		return "...-";
	else if(c=='W')
		return ".--";
	else if(c=='X')
		return "-..-";
	else if(c=='Y')
		return "-.--";
	else if(c=='Z')
		return "--..";
	else if(c=='0')
		return "-----";
	else if(c=='1')
		return ".----";
	else if(c=='2')
		return "..---";
	else if(c=='3')
		return "...--";
	else if(c=='4')
		return "....-";
	else if(c=='5')
		return ".....";
	else if(c=='6')
		return "-....";
	else if(c=='7')
		return "--...";
	else if(c=='8')
		return "---..";
	else if(c=='9')
		return "----.";
	else if(c=='.')
		return ".-.-.-";
	else if(c==',')
		return "--..--";
	else if(c=='?')
		return "..--..";
	else if(c=='!')
		return "-.-.--";

	return "N/R";
}


/**
 * Redefining print for Message
 */
void MorseCodeMessage::print() {
	cout << endl << ENGmsg;
	cout << endl << MORSEmsg;
}






//--------------------------------------------MessageStackNode------------------------------------------------
class MessageStackNode {
public:
	MessageStackNode();
	MessageStackNode(Message* newMsg);
	~MessageStackNode();
	Message* getMessage();
	MessageStackNode *down;

private:
	Message *msg;
};


/**
 * Default constructor.
 */
MessageStackNode::MessageStackNode() {
	down = nullptr;
}


/**
 * Parametric constructor to initialize node with a msg value
 */
MessageStackNode::MessageStackNode(Message* newMsg) {
	down = nullptr;
	msg = newMsg;
}


/**
 * Destructor
 */
MessageStackNode::~MessageStackNode() {
	//
}


/**
 * Returns msg pointer
 */
Message* MessageStackNode::getMessage() {
	return msg;
}






//--------------------------------------------MessageStack------------------------------------------------
class MessageStack {
public:
	MessageStack();
	MessageStack(Message*);
	~MessageStack();
	void push(Message*);
	Message* pop();
	void print();
	void printHelper(MessageStackNode*);
	void del(MessageStackNode*);
	bool empty();

	MessageStackNode *head;
};

/**
 * Constructs the stack with an empty head pointer
 */
MessageStack::MessageStack() {
	head = NULL;
}


/**
 * Parametric constructor. Creates new stack with the parameter node as the head.
 */
MessageStack::MessageStack(Message* msg) {
	head = new MessageStackNode();
	*head = MessageStackNode(msg);
}


/**
 * Destructor for stack
 */
MessageStack::~MessageStack() {
	del(head);
}


/**
 * Recursive function for the destructor
 */
void MessageStack::del(MessageStackNode *ob) {
	if(ob == NULL) {
		return;
	}
	del(ob->down);
	delete ob;
}


/**
 * Adds a msg object to a Node and then pushes it to stack
 */
void MessageStack::push(Message *msg) {
	MessageStackNode* node = new MessageStackNode(msg);
	node->down = head;
	head = node;
}


/**
 * Pops node off stack, returns msg object within
 */
Message* MessageStack::pop() {
	MessageStackNode* temp = head;
	head = head->down;
	return temp->getMessage();
}


/**
 * Prints the stack
 */
void MessageStack::print() {
	printHelper(head);
}


/**
 * Prints all messages on stack using recursion
 */
void MessageStack::printHelper(MessageStackNode *head) {
	if(head == NULL) {
		return;
	}
	Message* temp = head->getMessage();
	temp->print();
	cout << endl;
	printHelper(head->down);
}


/**
 * Checks if stack is empty (checks if head has been allocated)
 */
bool MessageStack::empty() {
	if(head == NULL)
		return 1;
	return 0;
}




//--------------------------------------------MAIN------------------------------------------------

int main() {
	MessageStack stack;
	int choice;

	//Menu loop for main
	do {
		cout << "\n\n1. Enter Text\n2. Print Stack\n3. Pop\n4. Exit\nSelect an option: ";
		cin >> choice;
		switch(choice) {
		case 1: { //Gets new string and makes object. Asks whether or not to translate (MorseCodeMessage)
			string text;
			cout << "\nEnter text: ";
			fflush(stdin);
			getline(cin,text);
			cout << "\nTranslate that into Morse Code?\n(Y/N): ";
			char ch;
			cin >> ch;
			if(toupper(ch) == 'Y') {
				MorseCodeMessage* mcm = new MorseCodeMessage(text);
				stack.push(mcm);
			} else {
				Message* mes = new Message(text);
				stack.push(mes);
			}
			break; }

		case 2: { //Prints stack if not empty
			if(stack.empty()) {
				cout << "\nStack is empty.\n";
			} else {
				cout << "\nStack contents: \n";
				stack.print();
				cout << endl;
			}
			break; }

		case 3: { //Pops the first Message off the stack
			if(stack.empty()) {
				cout << "\nCannot pop. Stack is empty.\n";
			} else {
				Message *temp = stack.pop();
				cout << "\nPopped message: \n";
				temp->print();
				cout << endl;
			}
			break; }

		case 4: { //Quits
			cout << "\nQuitting...\n";
			break; }

		default:
			cout << "\nIncorrect Option!\n";
			break;
		}
	} while(choice != 4);

	return 0;
}




