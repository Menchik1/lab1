#ifndef HEADER_STACK_HPP
#define HEADER_STACK_HPP

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
// Узел для стека
struct NodeSt {
    string value;  // Data type of the NodeSt - string
    NodeSt* next;
};

// Stack structure
struct Stack {
    NodeSt* top;  // Pointer to the top of the stack

    Stack() {
        top = nullptr;
    }

    // Adding an element to the stack (push)
    void push(const string& value) {
        NodeSt* newNodeSt = new NodeSt();
        newNodeSt->value = value;
        newNodeSt->next = top;  // New element points to the current top
        top = newNodeSt;  // Update the top of the stack
    }

    // Removing an element from the stack (pop)
    void pop() {
        if (top == nullptr) {
            cout << "Stack is empty, nothing to remove." << endl;
            return;
        }

        NodeSt* temp = top;
        top = top->next;  // Move the top to the next element
        delete temp;  // Delete the old top
    }

    // Reading all elements in the stack
    void read() {
        if (top == nullptr) {
            cout << "Stack is empty." << endl;
            return;
        }

        NodeSt* temp = top;
        while (temp) {
            cout << temp->value << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // Writing the current state of the stack to a file
    void writeToFile(const string& filename, const string& sourceFile) {
        // Check if Stack.txt is empty
        ifstream checkFile(filename);
        if (checkFile.peek() == ifstream::traits_type::eof()) {
            // If Stack.txt is empty, load from the specified source file
            loadFromFile(sourceFile); // Load initial state from the specified file
        }
        checkFile.close();

        ofstream file(filename, ios::trunc); // Open file in overwrite mode
        NodeSt* temp = top;

        while (temp) {
            file << temp->value;
            if (temp->next) { // Only add " -> " if there's a next element
                file << " -> ";
            }
            temp = temp->next;
        }

        file << " -> NULL\n";
        file.close();
    }

    // Load initial state from file
    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                stringstream ss(line);
                string value;
                vector<string> values; // Temporary vector to store values
                while (ss >> value) {
                    if (value == "->" || value == "NULL") continue; // Skip arrows and NULL
                    values.push_back(value); // Save values to the temporary vector
                }
                // Now push values to the stack in reverse order
                for (auto it = values.rbegin(); it != values.rend(); ++it) {
                    push(*it);
                }
            }
            file.close();
        }
    }
};
#endif
