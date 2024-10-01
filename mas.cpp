#include <iostream>
#include <fstream> 

using namespace std;

struct Array {
    string* arr; 
    size_t capacity; 
    size_t size; 

    // Constructor
    Array() : capacity(2), size(0) {
        arr = new string[capacity];
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                addEnd(line); // Add each line to the array
            }
            file.close();
        } else {
            cout << "Unable to open file for reading. Creating a new file with initial values." << endl;
            ofstream newFile(filename);
            newFile << "Initial value 1" << endl;
            newFile << "Initial value 2" << endl;
            newFile.close();
            cout << "New file created with initial values." << endl;
        }
    }

    // Method to resize the array
    void resize() {
        capacity *= 2; // Double the capacity
        string* newArr = new string[capacity];
        for (size_t i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }

    // Method to add an element at a specific index
    void addAtIndex(size_t index, const string& value) {
        if (index > size) {
            throw out_of_range("Index out of range");
        }
        if (size == capacity) {
            resize();
        }
        for (size_t i = size; i > index; i--) {
            arr[i] = arr[i - 1];
        }
        arr[index] = value;
        size++;
    }

    // Method to add an element at the end
    void addEnd(const string& value) {
        if (size == capacity) {
            resize();
        }
        arr[size++] = value;
    }

    // Method to remove an element at a specific index
    void removeAtIndex(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        for (size_t i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1];
        }
        size--;
    }

    // Method to replace an element at a specific index
    void replaceAtIndex(size_t index, const string& value) {
        if (index >= size) {
            throw out_of_range("Index out of range");
        }
        arr[index] = value;
    }

    // Method to get the current size
    size_t getSize() const {
        return size;
    }

    // Method to print elements
    void print() const {
        for (size_t i = 0; i < size; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
    }

    // Method to save data to a file
    void saveToFile(const string& filename) const {
        ofstream file(filename);
        if (file.is_open()) {
            for (size_t i = 0; i < size; i++) {
                file << arr[i] << endl; // Write each string to the file
            }
            file.close();
            cout << "Data successfully saved to " << filename << endl;
        } else {
            cout << "Unable to open file for writing." << endl;
        }
    }

    // Manual cleanup of the array
    void cleanup() {
        delete[] arr; // Free memory
        arr = nullptr; // Nullify the pointer
    }

};

void Massiv() {
    Array array;
    string command;

    // Load data from file at the start of the program
    array.loadFromFile("massiv.txt");

    while (true) {
        cout << "Enter command (add, addAt, replace, remove, print, exit): ";
        cin >> command;

        if (command == "add") {
            string value;
            cin >> ws; // Ignore whitespace
            getline(cin, value);
            array.addEnd(value);
            array.saveToFile("massiv.txt"); // Save data after adding
        } else if (command == "addAt") {
            size_t index;
            string value;
            cout << "Enter index and string to add: ";
            cin >> index;
            cin >> ws; // Ignore whitespace
            getline(cin, value);
            try {
                array.addAtIndex(index, value);
                array.saveToFile("massiv.txt"); // Save data after adding
            } catch (const out_of_range& e) {
                cout << e.what() << endl;
            }
        } else if (command == "replace") {
            size_t index;
            string value;
            cout << "Enter index and string to replace: ";
            cin >> index;
            cin >> ws; // Ignore whitespace
            getline(cin, value);
            try {
                array.replaceAtIndex(index, value);
                array.saveToFile("massiv.txt"); // Save data after replacing
            } catch (const out_of_range& e) {
                cout << e.what() << endl;
            }
        } else if (command == "remove") {
            size_t index;
            cout << "Enter index to remove: ";
            cin >> index;
            try {
                array.removeAtIndex(index);
                array.saveToFile("massiv.txt"); // Save data after removing
            } catch (const out_of_range& e) {
                cout << e.what() << endl;
            }
        } else if (command == "print") {
            cout << "Array elements: ";
            array.print();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Unknown command" << endl;
        }
    }
    array.cleanup();
}
