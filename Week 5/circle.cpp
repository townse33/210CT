#include <iostream>
#include <string>

using namespace std;

struct circleLL {
//Circular linked list, links to itself by default
	string data;
	circleLL *next = this;

	void insert(circleLL *node) {
	//Linked list tail insertion method
		circleLL *currentNode = this;
		while (currentNode->next != this) { //Terminates loop when node that links to head is reached, i.e. the current tail
			currentNode = currentNode->next;
		}
		node->next = this; 
		//New node is initialised to point to head, and the next pointer for the current tail is changed to the new node: including it in the list
		currentNode->next = node;
		return;
	}

	void rotate(int n, string name) {
	//Children's circle counting game function
		circleLL *currentNode = this;

		while (currentNode->data != name) { //Iterate through list until name of starting child is found
			currentNode = currentNode->next;
		}

		while (currentNode->next != currentNode) {
			for (int i = 0; i < n - 1; i++) { //Just before we iterate to the child to be eliminated, we terminate the loop
				currentNode = currentNode->next;
			}
			//This allows us to change the node previous to it to point to the node after it, excluding it from the list
			currentNode->next = currentNode->next->next;
			currentNode = currentNode->next; 
		}

		cout << currentNode->data << endl;
		return;
	}
};



int main() {
	//Example method
	circleLL a, b, c, d;
	a.data = "Diana"; b.data = "Michael"; c.data = "David"; d.data = "Mary";
	a.insert(&b); a.insert(&c); a.insert(&d); //All nodes are inserted from 'a' to maintain order of nodes
	a.rotate(4, "Diana"); //Function outputs 'Michael' regardless of which node the method is called from
	return 0;
}