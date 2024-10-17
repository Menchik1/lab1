#ifndef HEADER_TREE_HPP
#define HEADER_TREE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
struct NodeT {
    int data; // Данные узла
    NodeT* left = nullptr; // Указатель на левую ветку
    NodeT* right = nullptr; // Указатель на правую ветку
    int height = 1; // Высота узла
};

// Функция для получения высоты узла
int GetHeight(NodeT* node) {
    return node ? node->height : 0;
}

// Функция для получения баланса узла
int GetBalance(NodeT* node) {
    return node ? GetHeight(node->left) - GetHeight(node->right) : 0;
}

// Функция для правого вращения
NodeT* RightRotate(NodeT* y) {
    NodeT* x = y->left;
    NodeT* T2 = x->right;

    // Выполняем вращение
    x->right = y;
    y->left = T2;

    // Обновляем высоты
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;

    return x; // Новый корень
}

// Функция для левого вращения
NodeT* LeftRotate(NodeT* x) {
    NodeT* y = x->right;
    NodeT* T2 = y->left;

    // Выполняем вращение
    y->left = x;
    x->right = T2;

    // Обновляем высоты
    x->height = max(GetHeight(x->left), GetHeight(x->right)) + 1;
    y->height = max(GetHeight(y->left), GetHeight(y->right)) + 1;

    return y; // Новый корень
}

// Функция для вставки узла в AVL-дерево
NodeT* Insert(NodeT* root, int key) {
    if (root == nullptr) {
        return new NodeT{key}; // Создание нового узла
    }

    if (key < root->data) {
        root->left = Insert(root->left, key); // Вставка в левое поддерево
    } else {
        root->right = Insert(root->right, key); // Вставка в правое поддерево
    }

    // Обновляем высоту текущего узла
    root->height = 1 + max(GetHeight(root->left), GetHeight(root->right));

    // Балансировка узла
    int balance = GetBalance(root);

    // Если узел становится несбалансированным, то есть 4 случая

    // Левый левый случай
    if (balance > 1 && key < root->left->data) {
        return RightRotate(root);
    }

    // Правый правый случай
    if (balance < -1 && key > root->right->data) {
        return LeftRotate(root);
    }

    // Левый правый случай
    if (balance > 1 && key > root->left->data) {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    // Правый левый случай
    if (balance < -1 && key < root->right->data) {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root; // Возврат (может быть) нового корня
}

// Функция для удаления узла из AVL-дерева
NodeT* DeleteNode(NodeT* root, int key) {
    if (root == nullptr) return root; // Если дерево пустое, вернуть

    if (key < root->data) {
        root->left = DeleteNode(root->left, key); // Рекурсивный вызов для левого поддерева
    } else if (key > root->data) {
        root->right = DeleteNode(root->right, key); // Рекурсивный вызов для правого поддерева
    } else {
        // Если найден узел для удаления
        if (root->left == nullptr) {
            NodeT* temp = root->right;
            delete root;
            return temp; // Возврат правого поддерева
        } else if (root->right == nullptr) {
            NodeT* temp = root->left;
            delete root;
            return temp; // Возврат левого поддерева
        }
        NodeT* temp = root->right; // Сохранение правого поддерева
        while (temp && temp->left != nullptr) { // Поиск минимального узла
            temp = temp->left;
        }
        root->data = temp->data; // Замена данных текущего узла на данные минимального
        root->right = DeleteNode(root->right, temp->data); // Удаление минимального узла
    }

    // Обновляем высоту текущего узла
    root->height = 1 + max(GetHeight(root->left), GetHeight(root->right));

    // Балансировка узла
    int balance = GetBalance(root);

    // Если узел становится несбалансированным, то есть 4 случая

    // Левый левый случай
    if (balance > 1 && GetBalance(root->left) >= 0) {
        return RightRotate(root);
    }

    // Правый правый случай
    if (balance < -1 && GetBalance(root->right) <= 0) {
        return LeftRotate(root);
    }

    // Левый правый случай
    if (balance > 1 && GetBalance(root->left) < 0) {
        root->left = LeftRotate(root->left);
        return RightRotate(root);
    }

    // Правый левый случай
    if (balance < -1 && GetBalance(root->right) > 0) {
        root->right = RightRotate(root->right);
        return LeftRotate(root);
    }

    return root; // Возврат (может быть) нового корня
}

// Функция для обхода бинарного дерева в симметричном порядке
void InOrder(NodeT* root, ostream& out) {
    if (root) {
        InOrder(root->left, out);
        out << root->data << " ";
        InOrder(root->right, out);
    }
}

// Функция для печати бинарного дерева
void PrintTree(NodeT* root, ostream& out, int space = 0) {
    if (root == nullptr) return;
    space += 10;
    PrintTree(root->right, out, space);
    out << endl;
    for (int i = 10; i < space; i++) {
        out << " ";
    }
    out << root->data << "\n";
    PrintTree(root->left, out, space);
}

// Запись в файл
void UpdateFile(NodeT* root) {
    ofstream outFile("tree.txt", ios::trunc);
    if (!outFile) {
        cout << "Could not open file for writing!" << endl;
        return;
    }
    PrintTree(root, outFile);
    outFile.close();
}

// Функция для загрузки данных из файла в бинарное дерево
void LoadFromFile(NodeT*& root) {
    ifstream inFile("elements_tree.txt");
    if (!inFile) {
        return;
    }
    string action;
    int value;
    while (inFile >> action >> value) {
        if (action == "insert") {
            root = Insert(root, value);
        } else if (action == "delete") {
            root = DeleteNode(root, value);
        }
    }
    inFile.close();
}

// Функция для запоминания команд
void LogAction(const string& action, int value) {
    ofstream logFile("elements_tree.txt", ios::app);
    if (!logFile) {
        cout << "Could not open file for logging!" << endl;
        return;
    }
    logFile << action << " " << value << endl;
    logFile.close();
};
#endif
