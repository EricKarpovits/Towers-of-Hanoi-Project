#include "declarations.h"

// Constructor
Stack::Stack(){

    head = NULL;
}

// Destructor - Deletes all the reamining linked lists if there are any remaining
Stack::~Stack(){

    clearList();
}

// Push a number by creating a new node
void Stack::push(int userNum) {

    // Creating a new node and setting info equal to the data
    Node *newnode = new Node;
    newnode->info = userNum;
    newnode->next = head;
    // Head will always be the new node
    head = newnode;
}

// Pop a number out of the linked list
int Stack::pop() {

    // Check if there is atleast 1 not to pop a number from
    if (!isEmpty(1)) {
        int value = head->info;
        Node *temp = head;
        head = head->next;
        // Deletes the node to release memory
        delete temp;
        // Make head point to next node
        return value;
    // I played around with throwing exceptions for a learning experience but the method has to return something but cannot
    // return a number as it would cause bugs. Therefore normall is empty is checked before calling the method pop(), but if
    // it is called it will throw an exception instead of returning a number
   } else {
        cout << red << "The link list is empty, cannot pop" << endl << white;
        throw "Invalid pop() operation";
    }
}

// Checks if the linked list is empty based on the number of nodes as the arguement
bool Stack::isEmpty(int numberOfNodes) {

    Node *temp = head;
    for(int i = 0; i < numberOfNodes; i++) {
        if(temp == NULL) {
            return true;
        }
        temp = temp->next;
    }
    return false;
}

// Checks if the stack is full
bool Stack::isFull() {

    int counter = 0;
    Node *temp = head;

    while(temp != NULL) {
        counter++;
        temp = temp->next;
    }

    if (counter >= DISKS_COUNT) {
        return true;
    } else {
        return false;
    }
}

// Gets the info of the node based on which index
int Stack::getValue(int index) {

    Node *temp = head;
    int info;

    for (int i = 0; i <= index; i++) {
        if (temp == NULL) {
            // Once again the method throws and exception instead of returing a number as it would cause bugs; basically just
            // an extra layer of protection
            throw "Invalid index for getValue()";
        } else {
            if (i == index){
                info = temp->info;
            }
            temp = temp->next;
        }
    }
    return info;
}

// Method which clears the linked list - used by the destructor too
void Stack::clearList() {

    // Create node pointer that iterates through each node and deletes them
    Node* node = head;

    while (node != NULL) {
        Node* temp = node->next;
        delete node;
        node = temp;
    }
    numberOfStartingNodes = 0;

    head = NULL;
}

// Gets the info of all the nodes in the linked list and returns an integer ap vector for Towers of Hanoi
apvector<int> Stack::getAllValues() {

    apvector<int> values;

    Node *node = head;

    int i = 0;
    while (node != NULL) {
        values.resize(i+1);
        values[i] = node->info;
        node = node->next;
        i++;
    }
    return values;
}

// Increase the number of disks if the user clicks increase
void Stack::addDisk() {

    Node *temp = head;
    Node *prev = temp;
    int prevValue = head->info;

    if (!isFull()) {
        while (temp != NULL) {
            prev = temp;
            prevValue = temp->info;
            temp = temp->next;
        }
        temp = new Node;
        temp->info = prevValue + 1;
        temp->next = NULL;
        prev->next = temp;
        numberOfStartingNodes++;
    }
}

// Decrease the numbers of nodes by 1
void Stack::discardDisk() {

    Node *temp = head;
    Node *prev = temp;

    if (!isEmpty(4)) {
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        delete temp;
        prev->next = NULL;
        numberOfStartingNodes--;
    }
}

int Stack::getNumberOfNodes() {

    Node *temp = head;
    int counter = 0;

    while(temp != NULL){
        counter ++;
        temp = temp->next;
    }

    return counter;
}

// This added method populates the source peg with 3 disks
void Stack::populateSourcePeg() {

    for (int i = NUMBER_OF_STARTING_DISKS - 1; i > -1 ; i--) {
        push(i);
    }
    numberOfStartingNodes = 3;
}

int Stack::getNumberOfStatingNodes() {

    return numberOfStartingNodes;
}
