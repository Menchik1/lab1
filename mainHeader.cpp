#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>

using namespace std;

struct HashTable {
    pair<string, string>* table; // Указатель на массив пар ключ-значение
    static const int TABLE_SIZE = 10; // Размер таблицы
    // Конструктор хеш-таблицы
    HashTable() {
        table = new pair<string, string>[TABLE_SIZE]; // Выделение памяти для таблицы
        for (int i = 0; i < TABLE_SIZE; ++i) {
            table[i] = {"key" + to_string(i + 1), "NULL"}; // Инициализация значений
        }
    }
    // Функция для установки значения по ключу
    void hset(const string& key, const string& value) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].first == key) { // Если ключ уже существует
                table[i].second = value; // Обновить значение
                return;
            }
        }
        // Сдвинуть элементы, чтобы освободить место для новой пары ключ-значение
        for (int i = TABLE_SIZE - 1; i > 0; --i) {
            table[i] = table[i - 1];
        }
        table[0] = {key, value}; // Добавить новую пару в начало
    }
    // Функция для получения значения по ключу
    string hget(const string& key) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].first == key) { // Если найден ключ
                return table[i].second; // Вернуть значение
            }
        }
        return "Key not found"; // Если ключ не найден
    }
    // Функция для удаления значения по ключу
    void hdel(const string& key) {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            if (table[i].first == key) { // Если найден ключ
                table[i].second = "NULL"; // Установить значение в "NULL"
                return;
            }
        }
        cout << "Key not found" << endl; // Если ключ не найден
    }
    // Функция для загрузки данных из файла
    void loadFromFile(const string& filename) {
        ifstream infile(filename); // Открытие файла для чтения
        if (!infile) { // Если файл не существует
            ofstream outfile(filename); // Создание нового файла
            for (int i = 0; i < TABLE_SIZE; ++i) {
                table[i] = {"key" + to_string(i + 1), "NULL"}; // Инициализация значений
                outfile << "[" << i << "] - (" << table[i].first << " : " << table[i].second << ")" << endl; // Запись в файл
            }
            outfile.close();
            cout << "File created and initialized with NULL values." << endl; // Сообщение о создании файла
        } else {
            string line;
            while (getline(infile, line)) { // Чтение строк из файла
                size_t startIndex = line.find('[');
                size_t endIndex = line.find(']');
                size_t startKey = line.find('(');
                size_t endKey = line.find(':');
                size_t endValue = line.find(')');

                // Проверка корректности индексов
                if (startIndex != string::npos && endIndex != string::npos &&
                    startKey != string::npos && endKey != string::npos &&
                    endValue != string::npos) {

                    int index = stoi(line.substr(startIndex + 1, endIndex - startIndex - 1)); // Извлечение индекса
                    string key = line.substr(startKey + 1, endKey - startKey - 2); // Извлечение ключа
                    string value = line.substr(endKey + 2, endValue - endKey - 2); // Извлечение значения

                    if (index >= 0 && index < TABLE_SIZE) { // Проверка индекса
                        table[index] = {key, value}; // Запись в таблицу
                    }
                }
            }
            infile.close(); // Закрытие файла
        }
    }
    // Функция для сохранения данных в файл
    void saveToFile(const string& filename) const {
        ofstream outfile(filename); // Открытие файла для записи
        if (!outfile) {
            cout << "Could not open the file for writing: " << filename << endl; // Сообщение об ошибке
            return;
        }
        for (int i = 0; i < TABLE_SIZE; ++i) {
            outfile << "[" << i << "] - (" << table[i].first << " : " << table[i].second << ")" << endl; // Запись в файл
        }
        outfile.close(); // Закрытие файла
    }
};
// Структура массива
struct Array {
    string* arr; // Указатель на массив строк
    size_t capacity; // Вместимость массива
    size_t size; // Текущий размер массива
    // Конструктор массива
    Array() : capacity(10), size(0) {
        arr = new string[capacity]; // Выделение памяти для массива
        for (size_t i = 0; i < capacity; i++) {
            arr[i] = "null"; // Инициализация значений
        }
    }
    size_t end_of_arr=capacity-1;
    // Функция для загрузки данных из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename); // Открытие файла для чтения
        if (file.is_open()) { // Если файл открыт
            string line;
            size_t index = 0;
            while (getline(file, line) && index < capacity) { // Чтение строк из файла
                size_t pos = line.find(" - "); // Поиск разделителя
                if (pos != string::npos) {
                    arr[index++] = line.substr(pos + 3); // Запись значения в массив
                }
            }
            size = index; // Обновление размера
            file.close(); // Закрытие файла
        } else {
            saveToFile(filename); // Создание нового файла
        }
    }
    // Функция для добавления значения в конец массива
    void addEnd(const string& value) {
        arr[end_of_arr] = value; // Запись значения
    }
    // Функция для добавления значения по индексу
    void addAtIndex(size_t index, const string& value) {
        if (index <= size) {
            arr[index] = value; // Запись значения
        } else {
            throw out_of_range("Index out of range"); // Исключение при выходе за пределы
        }
    }
    // Функция для удаления значения по индексу
    void removeAtIndex(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range"); // Исключение при выходе за пределы
        }
        arr[index] = "null"; // clear
        size--; // Уменьшение размера
    }
    // Функция для сохранения данных в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename); // Открытие файла для записи
        if (file.is_open()) {
            for (size_t i = 0; i < capacity; i++) {
                file << "[" << i << "] - " << (i < size ? arr[i] : "null") << endl; // Запись значений
            }
            file.close(); // Закрытие файла
        } else {
            cout << "Unable to open file for writing." << endl; // Сообщение об ошибке
        }
    }
};
// Узел для очереди
struct NodeQ {
    string value; // Значение узла
    NodeQ* next; // Указатель на следующий узел
};
// Структура очереди
struct Queue {
    NodeQ* front; // Указатель на передний элемент
    NodeQ* rear; // Указатель на задний элемент
    // Конструктор очереди
    Queue() {
        front = nullptr; // Инициализация указателей
        rear = nullptr;
    }
    // Функция для добавления элемента в очередь
    void push(const string& value) {
        NodeQ* newNodeQ = new NodeQ(); // Создание нового узла
        newNodeQ->value = value; // Запись значения
        newNodeQ->next = nullptr; // Установка указателя на следующий узел
        if (rear == nullptr) { // Если очередь пуста
            front = rear = newNodeQ; // Установка указателей
        } else {
            rear->next = newNodeQ; // Присоединение нового узла к концу
            rear = newNodeQ; // Обновление указателя на задний элемент
        }
        writeToFile(); // Сохранение состояния очереди в файл
    }
    // Функция для удаления элемента из очереди
    void pop() {
        if (front == nullptr) { // Если очередь пуста
            cout << "Queue is empty, nothing to remove." << endl; // Сообщение об ошибке
            return;
        }
        NodeQ* temp = front; // Сохранение переднего узла
        front = front->next; // Перемещение указателя на следующий узел
        if (front == nullptr) { // Если очередь стала пустой
            rear = nullptr; // Обнуление указателя на задний элемент
        }
        delete temp; // Освобождение памяти
        writeToFile(); // Сохранение состояния очереди в файл
    }
    // Функция для чтения элементов очереди
    void read() {
        if (front == nullptr) { // Если очередь пуста
            cout << "Queue is empty." << endl; // Сообщение об ошибке
            return;
        }
        NodeQ* temp = front; // Указатель на передний элемент
        while (temp) {
            cout << temp->value; // Вывод значения
            if (temp->next) cout << " <- "; // Разделитель
            temp = temp->next; // Переход к следующему узлу
        }
        cout << " <- NULL" << endl; // Завершение вывода
    }
    // Функция для записи состояния очереди в файл
    void writeToFile() {
        ofstream file("queue.txt"); // Открытие файла для записи
        if (!file.is_open()) {
            cout << "Unable to open file for writing." << endl; // Сообщение об ошибке
            return;
        }
        NodeQ* temp = front; // Указатель на передний элемент
        while (temp) {
            file << temp->value; // Запись значения
            if (temp->next) {
                file << " <- "; // Разделитель
            }
            temp = temp->next; // Переход к следующему узлу
        }
        file << " <- NULL" << endl; // Завершение записи
        file.close(); // Закрытие файла
    }
    // чтение файла
    void loadFromFile(const string& filename) {
        ifstream file(filename); // Открытие файла для чтения
        if (!file.is_open()) {
            return;
        }
        string value; // Переменная для хранения значения
        NodeQ* previous = nullptr; // Указатель на предыдущий узел
        while (file >> value) { // Чтение значений из файла
            if (value == "NULL") break; // Завершение при встрече NULL

            if (value == "<-") continue; // Игнорирование разделителя

            NodeQ* newNode = new NodeQ(); // Создание нового узла
            newNode->value = value; // Запись значения
            newNode->next = nullptr; // Установка указателя на следующий узел

            if (previous == nullptr) { // Если это первый узел
                front = newNode; // Установка указателя на передний элемент
            } else {
                previous->next = newNode; // Присоединение нового узла к предыдущему
            }

            previous = newNode; // Обновление указателя на предыдущий узел
            rear = newNode; // Обновление указателя на задний элемент
        }

        file.close(); // Закрытие файла
    }
};
struct Node2s {
    string data;        // Данные узла
    Node2s* prev;      // Указатель на предыдущий узел
    Node2s* next;      // Указатель на следующий узел
    // Конструктор для инициализации узла
    Node2s(const string& value) : data(value), prev(nullptr), next(nullptr) {}
};
// Структура для двусвязного списка
struct DoublyLinkedList {
    Node2s* head;      // Указатель на голову списка
    Node2s* tail;      // Указатель на хвост списка
    // Конструктор для инициализации списка
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}
    // Метод для добавления узла в начало списка
    void addToHead(const string& value) {
        Node2s* newNode = new Node2s(value); // Создаем новый узел
        if (!head) {                          // Если список пуст
            head = tail = newNode;            // Устанавливаем новый узел как голову и хвост
        } else {
            newNode->next = head;              // Связываем новый узел с головой
            head->prev = newNode;              // Устанавливаем указатель предыдущего узла для головы
            head = newNode;                    // Обновляем голову списка
        }
    }
    // Метод для добавления узла в конец списка
    void addToTail(const string& value) {
        Node2s* newNode = new Node2s(value); // Создаем новый узел
        if (!tail) {                          // Если список пуст
            head = tail = newNode;            // Устанавливаем новый узел как голову и хвост
        } else {
            newNode->prev = tail;              // Связываем новый узел с хвостом
            tail->next = newNode;              // Устанавливаем следующий узел для хвоста
            tail = newNode;                    // Обновляем хвост списка
        }
    }
    // Метод для удаления узла из начала списка
    void deleteFromHead() {
        if (!head) return;                    // Если список пуст, ничего не делаем
        Node2s* temp = head;                  // Сохраняем указатель на голову
        head = head->next;                    // Обновляем голову на следующий узел
        if (head) head->prev = nullptr;      // Если новый узел не пуст, сбрасываем указатель на предыдущий узел
        else tail = nullptr;                   // Если список стал пустым, сбрасываем хвост
        delete temp;                          // Удаляем старую голову
    }
    // Метод для удаления узла из конца списка
    void deleteFromTail() {
        if (!tail) return;                    // Если список пуст, ничего не делаем
        Node2s* temp = tail;                  // Сохраняем указатель на хвост
        tail = tail->prev;                    // Обновляем хвост на предыдущий узел
        if (tail) tail->next = nullptr;      // Если новый хвост не пуст, сбрасываем указатель на следующий узел
        else head = nullptr;                   // Если список стал пустым, сбрасываем голову
        delete temp;                          // Удаляем старую хвост
    }
    // Метод для удаления узла по значению
    void deleteByValue(const string& value) {
        Node2s* current = head;               // Начинаем с головы
        while (current) {                      // Проходим по списку
            if (current->data == value) {     // Если нашли узел с искомым значением
                if (current->prev) current->prev->next = current->next; // Обновляем указатель предыдущего узла
                if (current->next) current->next->prev = current->prev; // Обновляем указатель следующего узла
                if (current == head) head = current->next;            // Если удаляем голову, обновляем голову
                if (current == tail) tail = current->prev;            // Если удаляем хвост, обновляем хвост
                delete current;               // Удаляем узел
                return;
            }
            current = current->next;          // Переходим к следующему узлу
        }
    }
    // Метод для поиска узла по значению
    Node2s* findByValue(const string& value) {
        Node2s* current = head;               // Начинаем с головы
        while (current) {                      // Проходим по списку
            if (current->data == value) {     // Если нашли узел с искомым значением
                return current;                // Возвращаем указатель на узел
            }
            current = current->next;          // Переходим к следующему узлу
        }
        return nullptr;                       // Если не нашли, возвращаем nullptr
    }
void loadFromFile(const string& filename) {
    ifstream file(filename);               // Открываем файл для чтения
    if (!file.is_open()) {                 // Проверяем, удалось ли открыть файл
        return;                            // Если не удалось, выходим
    }

    string line;                           // Переменная для хранения строк из файла
    while (getline(file, line)) {          // Читаем файл построчно

        // Разделяем строку на значения по символу '<'
        stringstream ss(line);             // Создаем строковый поток для разбора
        string value;                      // Переменная для хранения каждого значения
        while (getline(ss, value, '<')) {  // Разделяем строку по символу '<'
            // Убираем символы '>', '-' и пробелы
            size_t gtPos = value.find('>');
            if (gtPos != string::npos) {
                value = value.substr(0, gtPos); // Оставляем только часть до '>'
            }

            // Убираем символ '-'
            value.erase(remove(value.begin(), value.end(), '-'), value.end());

            // Убираем лишние пробелы
            value.erase(remove_if(value.begin(), value.end(), ::isspace), value.end());

            // Добавляем значение только если оно не пустое
            if (!value.empty()) {
                addToTail(value);            // Добавляем значение в список
            }
        }
    }
    file.close();                           // Закрываем файл после чтения
}
    // Метод для сохранения данных в файл
    void saveToFile(const string& filename) {
        ofstream file(filename, ios::out);     // Открываем файл в режиме перезаписи
        if (head) {                            // Проверяем, есть ли данные в списке
            Node2s* current = head;            // Начинаем с головы
            while (current) {                   // Проходим по списку
                file << current->data;          // Записываем данные узла в файл
                if (current->next) {            // Если есть следующий узел
                    file << " <- ";             // Добавляем разделитель
                }
                current = current->next;        // Переходим к следующему узлу
            }
        }
    }
};
// Структура узла односвязного списка
struct NodeS {
    string value;      // Значение, хранящееся в узле
    NodeS* next;      // Указатель на следующий узел
};
// Структура односвязного списка
struct Spisok {
    NodeS* head;      // Указатель на голову списка
    // Конструктор, инициализирующий голову списка как nullptr
    Spisok() {
        head = nullptr;
    }
    // чтение из файла
    void loadFromFile(const string& filename) {
        ifstream file(filename); // Открытие файла для чтения
        if (file.is_open()) {    // Проверка, успешно ли открыт файл
            string line;         // Переменная для хранения строки
            while (getline(file, line)) { // Чтение файла построчно
                stringstream ss(line); // Создание потока для разбора строки
                string value;          // Переменная для хранения значения
                while (ss >> value) { // Чтение значений из строки
                    if (value == "->" || value == "nullptr") continue; // Игнорирование стрелок и nullptr
                    addTail(value); // Добавление значения в конец списка
                }
            }
            file.close(); // Закрытие файла после чтения
        }
    }
    // Метод для записи текущего состояния списка в файл
    void writeToFile(const string& filename) {
        ofstream file(filename); // Открытие файла для записи
        if (file.is_open()) {    // Проверка, успешно ли открыт файл
            NodeS* temp = head;  // Указатель на текущий узел
            while (temp) {       // Проход по всем узлам списка
                file << temp->value << " -> "; // Запись значения узла в файл
                temp = temp->next; // Переход к следующему узлу
            }
            file << "nullptr\n"; // Завершение записи с указанием конца списка
            file.close(); // Закрытие файла после записи
        } else {
            cout << "Error opening file for writing." << endl; // Сообщение об ошибке, если файл не открыт
        }
    }
    // Метод для добавления элемента в голову списка
    void addHead(string value) {
        NodeS* newNodeS = new NodeS(); // Создание нового узла
        newNodeS->value = value; // Установка значения узла
        newNodeS->next = head; // Указатель на текущую голову списка
        head = newNodeS; // Обновление головы списка
    }
    // Метод для добавления элемента в конец списка
    void addTail(string value) {
        NodeS* newNodeS = new NodeS(); // Создание нового узла
        newNodeS->value = value; // Установка значения узла
        newNodeS->next = nullptr; // Указатель на следующий узел равен nullptr
        if (!head) { // Если список пуст
            head = newNodeS; // Установка нового узла как головы списка
        } else {
            NodeS* temp = head; // Указатель на текущий узел
            while (temp->next) { // Поиск последнего узла
                temp = temp->next; // Переход к следующему узлу
            }
            temp->next = newNodeS; // Добавление нового узла в конец списка
        }
    }
    // Метод для удаления элемента из головы списка
    void removeHead() {
        if (!head) return; // Если список пуст, ничего не делать
        NodeS* temp = head; // Указатель на текущую голову
        head = head->next; // Обновление головы на следующий узел
        delete temp; // Освобождение памяти узла
    }
    // Метод для удаления элемента из конца списка
    void removeTail() {
        if (!head) return; // Если список пуст, ничего не делать
        if (!head->next) { // Если в списке только один узел
            delete head; // Освобождение памяти
            head = nullptr; // Обновление головы на nullptr
        } else {
            NodeS* temp = head; // Указатель на текущий узел
            while (temp->next->next) { // Поиск предпоследнего узла
                temp = temp->next; // Переход к следующему узлу
            }
            delete temp->next; // Освобождение памяти последнего узла
            temp->next = nullptr; // Обновление указателя на следующий узел
        }
    }
    // Метод для удаления элемента по значению
    void removeByValue(string value) {
        if (!head) return; // Если список пуст, ничего не делать
        if (head->value == value) { // Если значение в голове совпадает
            removeHead(); // Удаление головы
            return; // Выход из метода
        }
        NodeS* temp = head; // Указатель на текущий узел
        while (temp->next && temp->next->value != value) { // Поиск узла с заданным значением
            temp = temp->next; // Переход к следующему узлу
        }
        if (temp->next) { // Если узел найден
            NodeS* toDelete = temp->next; // Указатель на узел для удаления
            temp->next = temp->next->next; // Пропуск узла для удаления
            delete toDelete; // Освобождение памяти
        }
    }
    // Метод для поиска элемента по значению
    bool search(string value) {
        NodeS* temp = head; // Указатель на текущий узел
        while (temp) { // Проход по всем узлам списка
            if (temp->value == value) { // Если значение найдено
                return true; // Возвращаем true
            }
            temp = temp->next; // Переход к следующему узлу
        }
        return false; // Если значение не найдено, возвращаем false
    }
    // Метод для чтения всех элементов списка и вывода их на экран
    void read() {
        NodeS* temp = head; // Указатель на текущий узел
        while (temp) { // Проход по всем узлам списка
            cout << temp->value << " -> "; // Вывод значения узла
            temp = temp->next; // Переход к следующему узлу
        }
        cout << "nullptr" << endl; // Завершение вывода
    }
    // Метод для очистки памяти
    void cleanup() {
        while (head) { // Пока список не пуст
            removeHead(); // Удаление головы
        }
    }
};
// Узел для бинарного дерева
struct NodeT {
    int data; // Данные узла
    NodeT* left = nullptr; // Указатель на левую ветку
    NodeT* right = nullptr; // Указатель на правую ветку
};
// Функция для вставки узла в бинарное дерево
void Insert(NodeT*& root, int key) {
    NodeT* newNode = new NodeT(); // Создание нового узла
    newNode->data = key; // Запись значения
    if (root == nullptr) { // Если дерево пустое
        root = newNode; // Установка нового узла как корня
        return;
    }
    queue<NodeT*> q; // Очередь для обхода дерева
    q.push(root); // Добавление корня в очередь
    while (!q.empty()) { // Пока очередь не пуста
        NodeT* temp = q.front(); // Получение переднего узла
        q.pop(); // Удаление переднего узла из очереди
        if (key < temp->data) { // Если ключ меньше текущего узла
            if (temp->left) { // Если левое поддерево существует
                q.push(temp->left); // Добавление левого узла в очередь
            } else {
                temp->left = newNode; // Вставка нового узла в левое поддерево
                return;
            }
        } else { // Если ключ больше или равен текущему узлу
            if (temp->right) { // Если правое поддерево существует
                q.push(temp->right); // Добавление правого узла в очередь
            } else {
                temp->right = newNode; // Вставка нового узла в правое поддерево
                return;
            }
        }
    }
}
// Функция для удаления узла из бинарного дерева
NodeT* DeleteNode(NodeT* root, int key) {
    if (root == nullptr) return root; // Если дерево пустое, вернуть

    if (key < root->data) { // Если ключ меньше текущего узла
        root->left = DeleteNode(root->left, key); // Рекурсивный вызов для левого поддерева
    } else if (key > root->data) { // Если ключ больше текущего узла
        root->right = DeleteNode(root->right, key); // Рекурсивный вызов для правого поддерева
    } else { // Если найден узел для удаления
        if (root->left == nullptr) { // Если нет левого поддерева
            NodeT* temp = root->right; // Сохранение правого поддерева
            delete root; // Освобождение памяти
            return temp; // Возврат правого поддерева
        } else if (root->right == nullptr) { // Если нет правого поддерева
            NodeT* temp = root->left; // Сохранение левого поддерева
            delete root; // Освобождение памяти
            return temp; // Возврат левого поддерева
        }
        NodeT* temp = root->right; // Сохранение правого поддерева
        while (temp && temp->left != nullptr) { // Поиск минимального узла
            temp = temp->left; // Переход к левому поддереву
        }
        root->data = temp->data; // Замена данных текущего узла на данные минимального
        root->right = DeleteNode(root->right, temp->data); // Удаление минимального узла
    }
    return root; // Возврат корня
}
// Функция для обхода бинарного дерева в симметричном порядке
void InOrder(NodeT* root, ostream& out) {
    if (root) {
        InOrder(root->left, out); // Рекурсивный вызов для левого поддерева
        out << root->data << " "; // Вывод данных узла
        InOrder(root->right, out); // Рекурсивный вызов для правого поддерева
    }
}

// Функция для печати бинарного дерева
void PrintTree(NodeT* root, ostream& out, int space = 0) {
    if (root == nullptr) return; // Если узел пустой, ничего не делать
    space += 10; // Увеличение отступа
    PrintTree(root->right, out, space); // Рекурсивный вызов для правого поддерева
    out << endl; // Переход на новую строку
    for (int i = 10; i < space; i++) {
        out << " "; // Печать отступов
    }
    out << root->data << "\n"; // Печать данных узла
    PrintTree(root->left, out, space); // Рекурсивный вызов для левого поддерева
}

// запись в файл
void UpdateFile(NodeT* root) {
    ofstream outFile("tree.txt", ios::trunc); // Открытие файла для записи с обнулением
    if (!outFile) {
        cout << "Could not open file for writing!" << endl; // Сообщение об ошибке
        return;
    }
    PrintTree(root, outFile); // Печать дерева в файл
    outFile.close(); // Закрытие файла
}
// Функция для загрузки данных из файла в бинарное дерево
void LoadFromFile(NodeT*& root) {
    ifstream inFile("elements_tree.txt"); // Открытие файла для чтения
    if (!inFile) {
        return;
    }
    string action; // Переменная для хранения действия
    int value; // Переменная для хранения значения
    while (inFile >> action >> value) { // Чтение пары действие-значение
        if (action == "insert") {
            Insert(root, value); // Вставка узла
        } else if (action == "delete") {
            root = DeleteNode(root, value); // Удаление узла
        }
    }
    inFile.close(); // Закрытие файла
}
// Функция для запоминания команд
void LogAction(const string& action, int value) {
    ofstream logFile("elements_tree.txt", ios::app); // Открытие файла
    if (!logFile) {
        cout << "Could not open file for logging!" << endl; // Сообщение об ошибке
        return;
    }
    logFile << action << " " << value << endl; // Запись действия в файл
    logFile.close(); // Закрытие файла
}
// Узел для стека
struct NodeSt {
    string value; // Значение узла
    NodeSt* next; // Указатель на следующий узел
};
// Структура стека
struct Stack {
    NodeSt* top; // Указатель на верхний элемент стека
    // Конструктор стека
    Stack() {
        top = nullptr; // Инициализация указателя на верхний элемент
    }
    // Функция для добавления элемента в стек
    void push(const string& value) {
        NodeSt* newNodeSt = new NodeSt(); // Создание нового узла
        newNodeSt->value = value; // Запись значения
        newNodeSt->next = top; // Присоединение нового узла к вершине стека
        top = newNodeSt; // Обновление указателя на верхний элемент
    }
    // Функция для удаления элемента из стека
    void pop() {
        if (top == nullptr) { // Если стек пустой
            cout << "Stack is empty, nothing to remove." << endl; // Сообщение об ошибке
            return;
        }
        NodeSt* temp = top; // Сохранение верхнего узла
        top = top->next; // Перемещение указателя на следующий узел
        delete temp; // Освобождение памяти
    }
    // Функция для чтения элементов стека
    void read() {
        if (top == nullptr) { // Если стек пустой
            cout << "Stack is empty." << endl; // Сообщение об ошибке
            return;
        }
        NodeSt* temp = top; // Указатель на верхний узел
        while (temp) {
            cout << temp->value << " -> "; // Вывод значения
            temp = temp->next; // Переход к следующему узлу
        }
        cout << "NULL" << endl; // Завершение вывода
    }
    // Функция для записи состояния стека в файл
    void writeToFile(const string& filename, const string& sourceFile) {
        ifstream checkFile(filename); // Проверка существования файла
        if (checkFile.peek() == ifstream::traits_type::eof()) { // Если файл пустой
            loadFromFile(sourceFile); // Загрузка из исходного файла
        }
        checkFile.close(); // Закрытие файла
        ofstream file(filename, ios::trunc); // Открытие файла для записи с обнулением
        NodeSt* temp = top; // Указатель на верхний узел
        while (temp) {
            file << temp->value; // Запись значения в файл
            if (temp->next) {
                file << " -> "; // Разделитель
            }
            temp = temp->next; // Переход к следующему узлу
        }
        file << " -> NULL\n"; // Завершение записи
        file.close(); // Закрытие файла
    }
    // Функция для чтения файла
    void loadFromFile(const string& filename) {
        ifstream file(filename); // Открытие файла для чтения
        if (file.is_open()) { // Если файл открыт
            string line;
            while (getline(file, line)) { // Чтение строк из файла
                stringstream ss(line); // Создание строки потока
                string value;
                while (ss >> value) { // Чтение значений из строки
                    if (value == "->" || value == "NULL") continue; // Игнорирование разделителей
                    push(value); // Добавление значения в стек
                }
            }
        }
    }
};
#endif
