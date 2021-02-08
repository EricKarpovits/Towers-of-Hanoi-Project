#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

class Stack {

    private:

        // Node pointer head
        Node *head;
        int numberOfStartingNodes;

    public:

        // Constructor
        Stack();
        // Destructor
        ~Stack();

        // Methods
        void push(int number);
        int pop();
        bool isEmpty(int numberOfNodes);
        bool isFull();
        int getValue(int whichValue);
        void clearList();
        apvector<int> getAllValues();
        void addDisk();
        void discardDisk();
        int getNumberOfNodes();
        void populateSourcePeg();
        int getNumberOfStatingNodes();
};

#endif // STACK_H_INCLUDED
