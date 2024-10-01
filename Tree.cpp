#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct Node {
    string value;
    Node* left;
    Node* right;

    Node(string val) : value(val), left(nullptr), right(nullptr) {}
};

struct FullBinaryTree {
    Node* root;

    FullBinaryTree() : root(nullptr) {}

    void add(const string& value) {
        if (!root) {
            root = new Node(value);
        } else {
            queue<Node*> q;
            q.push(root);

            while (!q.empty()) {
                Node* current = q.front();
                q.pop();

                if (!current->left) {
                    current->left = new Node(value);
                    break;
                } else {
                    q.push(current->left);
                }

                if (!current->right) {
                    current->right = new Node(value);
                    break;
                } else {
                    q.push(current->right);
                }
            }
        }
        writeToFile();
    }

    bool search(const string& value) {
        if (!root) return false;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            if (current->value == value) {
                return true;
            }

            if (current->left) q.push(current->left);
            if (current->right) q.push(current->right);
        }

        return false;
    }

    Node* getLastNode() {
        if (!root) return nullptr;

        queue<Node*> q;
        q.push(root);
        Node* lastNode = nullptr;

        while (!q.empty()) {
            lastNode = q.front();
            q.pop();

            if (lastNode->left) q.push(lastNode->left);
            if (lastNode->right) q.push(lastNode->right);
        }

        return lastNode;
    }

    void remove(const string& value) {
        if (!root) {
            cout << "The tree is empty, nothing to remove." << endl;
            return;
        }

        if (root->value == value && !root->left && !root->right) {
            // If the tree consists of only one node, and this is the node to be removed
            delete root;
            root = nullptr;
            writeToFile();
            return;
        }

        queue<Node*> q;
        q.push(root);
        Node* toDelete = nullptr;
        Node* parent = nullptr;

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            // Find the node to delete
            if (current->value == value) {
                toDelete = current;
            }

            if (current->left) {
                parent = current;
                q.push(current->left);
            }

            if (current->right) {
                parent = current;
                q.push(current->right);
            }
        }

        if (toDelete) {
            Node* lastNode = getLastNode();

            if (lastNode) {
                // Replace the value of the node to delete with the value of the last node
                toDelete->value = lastNode->value;

                // Remove the last node
                if (parent && parent->right == lastNode) {
                    delete parent->right;
                    parent->right = nullptr;
                } else if (parent && parent->left == lastNode) {
                    delete parent->left;
                    parent->left = nullptr;
                }

                writeToFile();
            }
        } else {
            cout << "Element not found." << endl;
        }
    }

    // Recursive tree reading (in-order traversal)
    void inorder(Node* node, ostream& out) {
        if (!node) return;
        inorder(node->left, out);
        out << node->value << " ";
        inorder(node->right, out);
    }

    // Read the tree
    void read() {
        if (!root) {
            cout << "The tree is empty." << endl;
            return;
        }
        inorder(root, cout);
        cout << endl;
    }

    // Write the tree to a file
    void writeToFile() {
        ofstream file("tree.txt");
        if (!root) {
            file << "The tree is empty." << endl;
        } else {
            inorder(root, file);
        }
        file.close();
    }
};

// Function for continuous command input
void Tree() {
    FullBinaryTree tree;
    string command;
    while (true) {
        cout << "Enter command (add, search, remove, read, exit): ";
        cin >> command;
        if (command == "add") {
            string value;
            cin >> value;
            tree.add(value);
            cout << "Added: " << value << endl;
        } 
        else if (command == "search") {
            string value;
            cin >> value;
            bool found = tree.search(value);
            if (found) {
                cout << "Element found: " << value << endl;
            } else {
                cout << "Element not found." << endl;
            }
        } 
        else if (command == "remove") {
            string value;
            cin >> value;
            tree.remove(value);
            cout << "Removed: " << value << endl;
        } 
        else if (command == "read") {
            cout << "Tree: ";
            tree.read();
        } 
        else if (command == "exit") {
            break;
        } 
        else {
            cout << "Unknown command." << endl;
        }
    }
}
