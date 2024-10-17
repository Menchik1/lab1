#ifndef HEADER_DLIST_HPP
#define HEADER_DLIST_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

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
#endif
