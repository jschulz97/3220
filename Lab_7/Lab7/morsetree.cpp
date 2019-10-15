/*
 * morsetree.cpp
 *
 *  Created on: Apr 11, 2018
 *      Author: jschu
 */




//MorseTreeNode* generateMorseTree(MorseTreeNode,ifstream,int);

//head = generateMorseTree(*head,ifs,0);






//--------------------------------------------MorseTreeNode------------------------------------------------
/*
class MorseTreeNode {
public:
	bool operator==(MorseTreeNode*);
	bool operator=(MorseTreeNode*);
	MorseTreeNode();
	MorseTreeNode *left;
	MorseTreeNode *right;
	char letter;
};


MorseTreeNode::MorseTreeNode() {
	left = NULL;
	right = NULL;
	letter = NULL;
}


bool MorseTreeNode::operator==(MorseTreeNode* rhs) {

}

/**
 *
 *
MorseTreeNode* MorseCodeMessage::generateMorseTree(MorseTreeNode head,ifstream fs,int count) {
	if(head == NULL) {
		char c;
		if(count<7) {
			head = MorseTreeNode();
			head.left = generateMorseTree(NULL,fs,count+1);
			fs >> c;
			head.letter = c;
			head.right = generateMorseTree(NULL,fs,count+1);
		} else {
			return NULL;
		}
	}

	return &head;
}*/
