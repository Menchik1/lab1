#ifndef HEADER_SPISOK_HPP
#define HEADER_SPISOK_HPP

#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

struct NodeS {
    string value;      // Значение, хранящееся в узле
    NodeS* next;      // Указатель на следующий узел
};
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
#endif
