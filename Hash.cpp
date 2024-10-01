#include <iostream>
#include <fstream>
#include <list>
#include <vector>
using namespace std;

// Structure for storing a key-value pair
struct KeyValuePair {
    string key;
    string value;
};

// Structure for the hash tabl
struct HashTable {
    // Size of the table
    static const int TABLE_SIZE = 10;

    // Array of lists for chaining
    vector<list<KeyValuePair>> table;

    HashTable() {
        table.resize(TABLE_SIZE);
    }

    // Hash function for a string (based on the remainder of the sum of ASCII values)
    int hash(const string& key) {
        int hashValue = 0;
        for (char c : key) {
            hashValue += c;
        }
        return hashValue % TABLE_SIZE;
    }

    // Adding an element (key-value pair)
    void insert(const string& key, const string& value) {
        int index = hash(key);
        for (auto& pair : table[index]) {
            if (pair.key == key) {
                pair.value = value;  // If the key already exists, update the value
                writeToFile();
                return;
            }
        }
        table[index].push_back({ key, value });
        writeToFile();
    }

    // Getting the value by key
    string get(const string& key) {
        int index = hash(key);
        for (const auto& pair : table[index]) {
            if (pair.key == key) {
                return pair.value;
            }
        }
        return "Key not found.";
    }

    // Removing an element by key
    void remove(const string& key) {
        int index = hash(key);
        auto& chain = table[index];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->key == key) {
                chain.erase(it);
                writeToFile();
                return;
            }
        }
        cout << "Key not found." << endl;
    }

    // Writing the current state of the hash table to a file
    void writeToFile() {
        ofstream file("HashTable.txt");

        for (int i = 0; i < TABLE_SIZE; ++i) {
            file << "[" << i << "]: ";
            for (const auto& pair : table[i]) {
                file << "(" << pair.key << ": " << pair.value << ") -> ";
            }
            file << "NULL\n";
        }

        file.close();
    }

    // Displaying the table on the screen
    void display() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            cout << "[" << i << "]: ";
            for (const auto& pair : table[i]) {
                cout << "(" << pair.key << ": " << pair.value << ") -> ";
            }
            cout << "NULL" << endl;
        }
    }
};

// Function for continuous command input
void Hash() {
    HashTable hashTable;
    string command;
    while (true) {
        cout << "Enter command (insert, get, remove, display, exit): ";
        cin >> command;

        if (command == "insert") {
            string key, value;
            cin >> key >> value;
            hashTable.insert(key, value);
            cout << "Added: (" << key << ": " << value << ")" << endl;
        } else if (command == "get") {
            string key;
            cin >> key;
            string value = hashTable.get(key);
            cout << "Value: " << value << endl;
        } else if (command == "remove") {
            string key;
            cin >> key;
            hashTable.remove(key);
            cout << "Removed element with key: " << key << endl;
        } else if (command == "display") {
            hashTable.display();
        } else if (command == "exit") {
            break;
        } else {
            cout << "Unknown command" << endl;
        }
    }
}

