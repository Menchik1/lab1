#ifndef HEADER_ARRAY_HPP
#define HEADER_ARRAY_HPP

#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
struct Array {
    string* arr; // Указатель на массив строк
    size_t capacity; // Вместимость массива
    size_t size; // Текущий размер массива

    // Конструктор массива
    Array() : capacity(10), size(0) {
        arr = new string[capacity]; // Выделение памяти для массива
    }

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
        if (size >= capacity) {
            resize(); // Увеличение размера массива, если необходимо
        }
        arr[size++] = value; // Запись значения и увеличение размера
    }

    // Функция для увеличения размера массива
    void resize() {
        capacity *= 2; // Увеличиваем вместимость вдвое
        string* newArr = new string[capacity]; // Новый массив
        for (size_t i = 0; i < size; i++) {
            newArr[i] = arr[i]; // Копируем старые данные
        }
        delete[] arr; // Освобождаем старый массив
        arr = newArr; // Указываем на новый массив
    }

    // Функция для добавления значения по индексу
    void addAtIndex(size_t index, const string& value) {
        if (index <= size) {
            if (size >= capacity) {
                resize(); // Увеличение размера массива, если необходимо
            }
            for (size_t i = size; i > index; i--) {
                arr[i] = arr[i - 1]; // Сдвиг элементов вправо
            }
            arr[index] = value; // Запись значения
            size++; // Увеличиваем размер
        } else {
            throw out_of_range("Index out of range"); // Исключение при выходе за пределы
        }
    }

    // Функция для удаления значения по индексу
    void removeAtIndex(size_t index) {
        if (index >= size) {
            throw out_of_range("Index out of range"); // Исключение при выходе за пределы
        }
        for (size_t i = index; i < size - 1; i++) {
            arr[i] = arr[i + 1]; // Сдвиг элементов влево
        }
        arr[--size] = ""; // Уменьшаем размер и очищаем последний элемент
    }

    // Функция для сохранения данных в файл
    void saveToFile(const string& filename) const {
        ofstream file(filename); // Открытие файла для записи
        if (file.is_open()) {
            for (size_t i = 0; i < size; i++) {
                file << "[" << i << "] - " << arr[i] << endl; // Запись значений
            }
            file.close(); // Закрытие файла
        } else {
            cout << "Unable to open file for writing." << endl; // Сообщение об ошибке
        }
    }
};

#endif
