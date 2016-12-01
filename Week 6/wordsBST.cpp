#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <stdlib.h>
#include <algorithm>
#include <vector>

using namespace std;

struct BST {
//Binary Search Tree data structure
	string word;
	int freq;
	BST *left = NULL; //Pointers to left and right subtree are null initially
	BST *right = NULL;

	void insert(BST *node, BST *current = NULL) {
	//Function to insert node from a root
		if (current == NULL) {
			current = this; //Initially, we want to look at the root's subtrees, we can't do this as a default argument because using 'this' is not allowed
		}
		/* Firstly, the node's word frequency is checked to determine whether to add to the left or right subtree
		   Secondly, the corresponding pointer is checked to see if a node exists there
		   Finally, if the pointer is null, it is made to point to the node, if not then the recursion continues
		*/
		if (current->freq > node->freq) { 
			if (current->left == NULL) {
				current->left = node;
			}
			else {
				insert(node, current->left);
			}
		}
		else {
			if (current->right == NULL) {
				current->right = node;
			}
			else {
				insert(node, current->right);
			}
		}
		return;
	}

	
};

bool search(string word, BST *current, bool top = true) {
//Function to search for a word in a BST given the root
	
	cout << current->word << ", "; //We print the path traversed as we go

	if (current->word == word) {
		cout << "Yes" << endl;
		return true; //The boolean statements are used to stop at each recursion layer if the word is found
	}

	if (current->left != NULL) {
		if (search(word, current->left, false)) {
			return true;
		}
	}
	if (current->right != NULL) {
		if (search(word, current->right, false)) {
			return true;
		};
	}

	if (top) { //The top parameter is used to output that the word was not found if nothing was returned in the tree traversal
		cout << "No" << endl;
	}

	return false;
}

void preOrder(BST *current) {
//Standard tree pre-order traversal: root, left subtree, right subtree

	cout << current->word << ": " << current->freq << ", ";

	if (current->left != NULL) { preOrder(current->left); }
	if (current->right != NULL) { preOrder(current->right); }
}

BST *text2tree(string filename) {
//This function produces a tree, given a paragraph in a standard text format
	ifstream file;
	file.open(filename);
	string word, temp;
	map<string, int> wordMap;
	vector<string> wordVec; 
	//The vector will track unique words whilst the map will track occurences per word

	while (file >> temp) {
		temp.erase(remove_if(temp.begin(), temp.end(), &ispunct), temp.end()); 
		//It is necessary to remove punctuation to ensure words are added cleanly to the tree. This is essential for searching
		
		if (temp.size() > 0) {
			transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
			//This transform is used to ensure consistency to properly count word frequencies and removing search ambiguity

			word = temp;
			wordMap[word] += 1;

			if (wordMap[word] == 1) { //If the frequency of the word is one, it is unique: this should be added to the vector
				wordVec.push_back(word); 
			}
		}
	}

	file.close();

	BST *root = new BST;
	root->word = wordVec[0];
	root->freq = wordMap[wordVec[0]]; //We initialise the tree with a root using the first word found

	for (int i = 1; i < wordVec.size(); i++) {
	//For each word in the vector, a new node is created in heap memory and its pointer is given to the tree root for insertion
		BST *temp = new BST; 
		temp->word = wordVec[i];
		temp->freq = wordMap[wordVec[i]];
		root->insert(temp);
	}

	return root;
}

int main() {
	//Sample method
	BST *head;
	head = text2tree("draculaExtract.txt"); //I have used an extract from the public-domain novel, Dracula, for testing
	preOrder(head); 
	search("Dracula", head); //As one may expect, this search is successful

	return 0;
}