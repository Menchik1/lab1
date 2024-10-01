#include <iostream>
#include <fstream>
using namespace std;

// Node structure
struct Node {
    string value;  // Data type of the node - string
    Node* next;
};

// Stack structure
struct Stack {
    Node* top;  // Pointer to the top of the stack

    Stack() {
        top = nullptr;
    }

    // Adding an element to the stack (push)
    void push(const string& value) {
        Node* newNode = new Node();
        newNode->value = value;
        newNode->next = top;  // New element points to the current top
        top = newNode;  // Update the top of the stack
        writeToFile();
    }

    // Removing an element from the stack (pop)
    void pop() {
        if (top == nullptr) {
            cout << "Stack is empty, nothing to remove." << endl;
            return;
        }

        Node* temp = top;
        top = top->next;  // Move the top to the next element
        delete temp;  // Delete the old top
        writeToFile();
    }

    // Reading all elements in the stack
    void read() {
        if (top == nullptr) {
            cout << "Stack is empty." << endl;
            return;
        }

        Node* temp = top;
        while (temp) {
            cout << temp->value << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // Writing the current state of the stack to a file
    void writeToFile() {
        ofstream file("Stack.txt");
        Node* temp = top;

        while (temp) {
            file << temp->value << " -> ";
            temp = temp->next;
        }

        file << "NULL\n";
        file.close();
    }
};

// Function for continuous command input
void Stackk() {
    Stack stack;
    string command;
    while (true) {
        cout << "Enter command(push, pop, read, exit): ";
        cin >> command;

        if (command == "push") {
            string value;
            cin >> value;
            stack.push(value);
            cout << "Added to stack: " << value << endl;
        } else if (command == "pop") {
            stack.pop();
            cout << "Removed element from stack" << endl;
        } else if (command == "read") {
            cout << "Stack: ";
            stack.read();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Unknown command" << endl;
        }
    }
}


