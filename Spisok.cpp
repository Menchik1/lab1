#include <iostream>
#include <fstream>

using namespace std;
// Node structure
struct Node {
    string value;
    Node* next;
};

// Singly linked list structure
struct Spisok {
    Node* head;

    Spisok() {
        head = nullptr;
    }

    // Add element to the head
    void addHead(string value) {
        Node* newNode = new Node();
        newNode->value = value;
        newNode->next = head;
        head = newNode;
        writeToFile();
    }

    // Add element to the tail
    void addTail(string value) {
        Node* newNode = new Node();
        newNode->value = value;
        newNode->next = nullptr;

        if (!head) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
        writeToFile();
    }

    // Remove element from the head
    void removeHead() {
        if (!head) return;
        Node* temp = head;
        head = head->next;
        delete temp;
        writeToFile();
    }

    // Remove element from the tail
    void removeTail() {
        if (!head) return;

        if (!head->next) {
            delete head;
            head = nullptr;
        } else {
            Node* temp = head;
            while (temp->next->next) {
                temp = temp->next;
            }
            delete temp->next;
            temp->next = nullptr;
        }
        writeToFile();
    }

    // Remove element by value
    void removeByValue(string value) {
        if (!head) return;

        if (head->value == value) {
            removeHead();
            return;
        }

        Node* temp = head;
        while (temp->next && temp->next->value != value) {
            temp = temp->next;
        }

        if (temp->next) {
            Node* toDelete = temp->next;
            temp->next = temp->next->next;
            delete toDelete;
        }
        writeToFile();
    }


    // Read all elements in the list
    void read() {
        Node* temp = head;
        while (temp) {
            cout << temp->value << " -> ";
            temp = temp->next;
        }
        cout << "nullptr" << endl;
    }

    // Write current state of the list to a file
    void writeToFile() {
        ofstream file("Spisok.txt");
        Node* temp = head;
        while (temp) {
            file << temp->value << " -> ";
            temp = temp->next;
        }
        file << "nullptr\n";
        file.close();
    }
};

// Function for continuous command input
void Spisokk() {
    Spisok list;
    string command;
    while (true) {
        cout << "Enter command(addHead, addTail, removeHead, removeTail, read, exit): ";
        cin >> command;
        if (command == "addHead") {
            string value;
            cin >> value;
            list.addHead(value);
            cout << "Added to head: " << value << endl;
        } else if (command == "addTail") {
            string value;
            cin >> value;
            list.addTail(value);
            cout << "Added to tail: " << value << endl;
        } else if (command == "removeHead") {
            list.removeHead();
            cout << "Removed element from head" << endl;
        } else if (command == "removeTail") {
            list.removeTail();
            cout << "Removed element from tail" << endl;
        }
         else if (command == "read") {
            list.read();
        } 
         else if (command == "exit") {
            break; 
        } else {
            cout << "Unknown command" << endl;
        }
    }
}
