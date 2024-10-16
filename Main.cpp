#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <string>
#include "header.hpp"

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Usage: " << argv[0] << " --file <filename> --query '<query>'" << endl;
        return 1;
    }

    string filename;
    string query;

    for (int i = 1; i < argc; i++) {
        if (string(argv[i]) == "--file") {
            filename = argv[++i];
        } else if (string(argv[i]) == "--query") {
            query = argv[++i];
        }
    }

    HashTable db;
    Array array;
    Queue queue;
    DoublyLinkedList list; 
    Spisok spisok; 
    Stack stack;
    NodeT* root = nullptr;
    
    try {
        db.loadFromFile("hash.txt");
        array.loadFromFile("mass.txt");
        queue.loadFromFile("queue.txt");
        list.loadFromFile("DoubleLinkedList.txt"); 
        spisok.loadFromFile(filename); 
        stack.loadFromFile("Stack.txt");
        LoadFromFile(root);
        UpdateFile(root);

        // Process the action
        if (!query.empty()) {
            if (query.find("Queue") == 0) {
                istringstream queryStream(query);
                string dataType, action;
                queryStream >> dataType >> action;

                if (action == "push") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    queue.push(value);
                    cout << "Added to queue: " << value << endl;
                } else if (action == "pop") {
                    queue.pop();
                    cout << "Removed element from queue" << endl;
                } else if (action == "read") {
                    cout << "Queue: ";
                    queue.read();
                } else {
                    cout << "Unknown action for Queue" << endl;
                }
            } else if (query.find("Mass") == 0) {
                istringstream queryStream(query);
                string dataType, action;
                queryStream >> dataType >> action;

                if (action == "pushend") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    array.addEnd(value);
                    array.saveToFile("mass.txt");
                    cout << "Added to array: " << value << endl;
                } else if (action == "pushindex") {
                    string key, value;
                    queryStream >> key >> value;
                    size_t index = stoi(key);
                    array.addAtIndex(index, value);
                    array.saveToFile("mass.txt");
                    cout << "Added to array at index " << index << ": " << value << endl;
                } else if (action == "remove") {
                    string key;
                    queryStream >> key;
                    size_t index = stoi(key);
                    array.removeAtIndex(index);
                    array.saveToFile("mass.txt");
                    cout << "Removed from array at index " << index << endl;
                } else {
                    cout << "Unknown action for Array" << endl;
                }
            } else if (query.find("Stack") == 0) {
                istringstream queryStream(query);
                string dataType, action;
                queryStream >> dataType >> action;

                if (action == "push") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    stack.push(value);
                    cout << "Added to stack: " << value << endl;
                } else if (action == "pop") {
                    stack.pop();
                    cout << "Removed element from stack" << endl;
                } else if (action == "read") {
                    cout << "Stack: ";
                    stack.read();
                } else {
                    cout << "Unknown action for Stack" << endl;
                }
            } else if (query.find("Hash") == 0) {
                istringstream queryStream(query);
                string dataType, action;
                queryStream >> dataType >> action;

                string key, value;
                queryStream >> key;

                if (action == "HSET") {
                    queryStream >> value;
                    db.hset(key, value);
                    cout << "Set key: " << key << " with value: " << value << endl;
                } else if (action == "HGET") {
                    string result = db.hget(key);
                    cout << "Value for key " << key << ": " << result << endl;
                } else if (action == "HDEL") {
                    db.hdel(key);
                    cout << "Deleted value for key: " << key << endl;
                } else {
                    cout << "Unknown action for HashTable" << endl;
                }
            } else if (query.find("DList") == 0) {
                istringstream queryStream(query);
                string dataType, action;
                queryStream >> dataType >> action;

                if (action == "Sp2Head") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    list.addToHead(value);
                    cout << "Added to head: " << value << endl;
                } else if (action == "Sp2Tail") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    list.addToTail(value);
                    cout << "Added to tail: " << value << endl;
                } else if (action == "DelHead") {
                    list.deleteFromHead();
                    cout << "Deleted from head" << endl;
                } else if (action == "DelTail") {
                    list.deleteFromTail();
                    cout << "Deleted from tail" << endl;
                } else if (action == "DelValue") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    list.deleteByValue(value);
                    cout << "Deleted value: " << value << endl;
                } else if (action == "FindValue") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    Node2s* found = list.findByValue(value);
                    if (found) {
                        cout << "Found value: " << found->data << endl;
                    } else {
                        cout << "Value not found" << endl;
                    }
                } else {
                    cout << "Unknown action for DoublyLinkedList" << endl;
                }
            } else if (query.find("Spisok") == 0) { // Обработка действий для односвязного списка
                istringstream queryStream(query);
                string dataType, action;
                queryStream >> dataType >> action;

                if (action == "addHead") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    spisok.addHead(value);
                    cout << "Added to head of Spisok: " << value << endl;
                } else if (action == "addTail") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    spisok.addTail(value);
                    cout << "Added to tail of Spisok: " << value << endl;
                } else if (action == "removeHead") {
                    spisok.removeHead();
                    cout << "Removed from head of Spisok" << endl;
                } else if (action == "removeTail") {
                    spisok.removeTail();
                    cout << "Removed from tail of Spisok" << endl;
                } else if (action == "removeByValue") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    spisok.removeByValue(value);
                    cout << "Removed value from Spisok: " << value << endl;
                } else if (action == "search") {
                    string value;
                    queryStream >> ws; // Ignore whitespaces
                    getline(queryStream, value);
                    bool found = spisok.search(value);
                    cout << (found ? "Value found in Spisok." : "Value not found in Spisok.") << endl;
                } else {
                    cout << "Unknown action for Spisok" << endl;
                }
            } else if (query.find("Tree") == 0) {
                istringstream queryStream(query);
                string dataType, action;
                queryStream >> dataType >> action;
                if (action.find("TINSERT") == 0) {
                    string valueStr;
                    queryStream >> ws; 
                    getline(queryStream, valueStr);
                    if (!valueStr.empty()) {
                        int value = stoi(valueStr);
                        Insert(root, value);
                        cout << "Inserted " << value << " into the tree." << endl;
                        UpdateFile(root);
                        LogAction("insert", value);
                    } else {
                        cout << "Error: No valid input for TINSERT." << endl;
                    }
                } else if (action.find("TDELETE") == 0) {
                    string valueStr;
                    queryStream >> ws; 
                    getline(queryStream, valueStr);
                    if (!valueStr.empty()) {
                        int value = stoi(valueStr);
                        root = DeleteNode(root, value);
                        cout << "Deleted " << value << " from the tree." << endl;
                        UpdateFile(root);
                        LogAction("delete", value);
                    } else {
                        cout << "Error: No valid input for TDELETE." << endl;
                    }
                } else if (action == "PRINT") {
                    cout << "Tree structure:" << endl;
                    PrintTree(root, cout);
                    cout << "InOrder traversal: ";
                    //InOrder(root, cout);
                    cout << endl;
                } else {
                    cout << "Unknown action for Tree." << endl;
                }
            }  
        } else {
            cout << "Unknown action" << endl;
        }

        db.saveToFile("hash.txt");
        array.saveToFile("mass.txt");
        queue.writeToFile();
        list.saveToFile("DoubleLinkedList.txt");
        spisok.writeToFile(filename);
        stack.writeToFile("Stack.txt", filename);
        UpdateFile(root);

    } catch (const invalid_argument& e) {
        cout << "Invalid argument: " << e.what() << endl;
        return 1;
    } catch (const out_of_range& e) {
        cout << "Index out of range: " << e.what() << endl;
        return 1;
    }
    return 0;
}
