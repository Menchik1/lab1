#ifndef HEADER_HASH_HPP
#define HEADER_HASH_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <vector>

using namespace std;

struct NodeH {
    string key;
    string value;
    NodeH* next;

    NodeH(const string& k, const string& v) : key(k), value(v), next(nullptr) {} // Конструктор
};

struct Hash {
    static const int tableSize = 10;
    NodeH* table[tableSize];

    // Конструктор
    Hash() {
        for (int i = 0; i < tableSize; i++) {
            table[i] = nullptr; // Инициализируем массив нулями
        }
    }

    // Хеш-функция
    int hashFunction(const string& key) {
        int hash = 0;
        for (char ch : key) {
            hash += ch; // Суммируем ASCII значения символов
        }
        return hash % tableSize; // Возвращаем индекс в пределах размера таблицы
    }

    // Добавление элемента
    void hset(const string& key, const string& value) {
        int index = hashFunction(key);
        NodeH* newNode = new NodeH(key, value);

        // Если ячейка пуста, добавляем новый узел
        if (!table[index]) {
            table[index] = newNode;
        } else {
            NodeH* current = table[index];

            // Проверяем, существует ли ключ
            while (current) {
                if (current->key == key) {
                    current->value = value; // Обновляем значение
                    delete newNode; // Удаляем временный узел
                    return; // Выходим, если обновили значение
                }
                // Если достигли конца цепочки
                if (!current->next) {
                    break; // Прерываем цикл
                }
                current = current->next; // Переходим к следующему узлу
            }

            // Если ключ не найден, добавляем новый узел в конец цепочки
            current->next = newNode;
        }
    }

    // Получение значения по ключу
    string hget(const string& key) {
        int index = hashFunction(key);
        NodeH* current = table[index];
        while (current) {
            if (current->key == key) {
                return current->value; // Возвращаем значение, если ключ найден
            }
            current = current->next;
        }
        return "Ключ не найден"; // Если ключ не найден
    }

    // Удаление элемента по ключу
    void hdel(const string& key) {
        int index = hashFunction(key);
        NodeH* current = table[index];
        NodeH* previous = nullptr;

        while (current) {
            if (current->key == key) {
                if (previous) {
                    previous->next = current->next; // Удаляем узел из цепочки
                } else {
                    table[index] = current->next; // Если это первый узел
                }
                delete current; // Освобождаем память
                return;
            }
            previous = current;
            current = current->next;
        }
        cout << "Ключ не найден для удаления" << endl; // Если ключ не найден
    }

    // Вывод всех элементов хеш-таблицы
    void printTableH() {
        for (int i = 0; i < tableSize; i++) {
            if (table[i]) {
                NodeH* current = table[i];
                while (current) {
                    cout << "{" << current->key << ": " << current->value << "} ";
                    current = current->next;
                }
                cout << endl;
            }
        }
    }

    // Запись хеш-таблицы в файл
    void writeToFile(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Не удалось открыть файл для записи." << endl;
            return;
        }

        for (int i = 0; i < tableSize; i++) {
            NodeH* current = table[i];
            while (current) {
                file << current->key << " " << current->value << endl;
                current = current->next;
            }
        }

        file.close();
    }

    // Чтение хеш-таблицы из файла
    void readFromFileH(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Не удалось открыть файл для чтения." << endl;
            return;
        }

        clearH(); // Очищаем таблицу перед загрузкой новых данных

        string key, value;
        while (file >> key >> value) {
            hset(key, value);
        }

        file.close();
    }

    // Загрузка данных из файла hash.txt
    void loadFromFile(const string& filename = "hash.txt") {
        readFromFileH(filename); // Используем уже существующий метод для чтения из файла
    }

    // Освобождение памяти вручную
    void clearH() {
        for (int i = 0; i < tableSize; i++) {
            NodeH* current = table[i];
            while (current) {
                NodeH* temp = current;
                current = current->next;
                delete temp; // Освобождаем память
            }
            table[i] = nullptr; // Обнуляем указатели
        }
    }
};

#endif
