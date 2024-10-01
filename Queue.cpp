#include <iostream>
#include <fstream>

using namespace std;
// Node structure
struct Node {
    string value;  // Changed value type to string
    Node* next;
};

// Queue structure
struct Queue {
    Node* front;
    Node* rear;

    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    // Adding an element to the queue (push)
    void push(const string& value) {
        Node* newNode = new Node();
        newNode->value = value;
        newNode->next = nullptr;

        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }

        writeToFile();
    }

    // Removing an element from the queue (pop)
    void pop() {
        if (front == nullptr) {
            cout << "Queue is empty, nothing to remove." << endl;
            return;
        }

        Node* temp = front;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        writeToFile();
    }

    // Reading all elements in the queue
    void read() {
        if (front == nullptr) {
            cout << "Queue is empty." << endl;
            return;
        }

        Node* temp = front;
        while (temp) {
            cout << temp->value << " <- ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    // Writing the current state of the queue to a file
    void writeToFile() {
        ofstream file("queue.txt");
        Node* temp = front;

        while (temp) {
            file << temp->value << " <- ";
            temp = temp->next;
        }

        file << "NULL\n";
        file.close();
    }
};

// Function for continuous command input
void Queuee() {
    Queue queue;
    string command;
    while (true) {
        cout << "Enter command(push, pop, read, exit): ";
        cin >> command;

        if (command == "push") {
            string value;
            cin >> value;
            queue.push(value);
            cout << "Added to queue: " << value << endl;
        } else if (command == "pop") {
            queue.pop();
            cout << "Removed element from queue" << endl;
        } else if (command == "read") {
            cout << "Queue: ";
            queue.read();
        } else if (command == "exit") {
            break;
        }
         else {
            cout << "Unknown command" << endl;
            cout<<endl;
        }
    }
}
