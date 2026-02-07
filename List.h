// #pragma once
// #include <iostream>
// #include <string>
// using namespace std;
//
// template <typename T>
// class List {
// private:
//     T* items;
//     int capacity;
//     int size;
//
// public:
//     List() : items(nullptr), capacity(0), size(0) {}
//     List(int initialCapacity) : capacity(initialCapacity), size(0) {
//         items = new T[capacity];
//     }
//
//     ~List() {
//         delete[] items;
//     }
//
//     bool add(T item) {
//         if (size < capacity) {
//             items[size] = item;
//             size++;
//             return true;
//         }
//         return false;
//     }
//
//     T get(int index) const { return items[index]; }
//
//     T& getRef(int index) {
//
//         return items[index];
//
//     }
//
//     // void sortByGameName() {
//     //     for (int i = 0; i < size - 1; i++) {
//     //         for (int j = 0; j < size - i - 1; j++) {
//     //             // BoardGame uses getName()
//     //             if (items[j]->getName() > items[j + 1]->getName()) {
//     //                 T temp = items[j];
//     //                 items[j] = items[j + 1];
//     //                 items[j + 1] = temp;
//     //             }
//     //         }
//     //     }
//     // }
//
//     void print() {
//         for (int i = 0; i < size; i++) {
//             //items[i]->printInfo(); // Using your BoardGame method
//             cout << items[i] << endl;
//         }
//     }
//
//     int getLength() const { return size; }
// };

#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class List {
private:
    T* items;
    int capacity;
    int size;

    void resize(int newCapacity) {
        if (newCapacity <= capacity) return;
        T* newItems = new T[newCapacity];
        for (int i = 0; i < size; i++) {
            newItems[i] = items[i];
        }
        delete[] items;
        items = newItems;
        capacity = newCapacity;
    }

public:
    // Constructors
    List() : items(nullptr), capacity(0), size(0) {}

    List(int initialCapacity) : items(nullptr), capacity(0), size(0) {
        if (initialCapacity < 1) initialCapacity = 1;
        capacity = initialCapacity;
        items = new T[capacity];
    }

    // Destructor
    ~List() {
        delete[] items;
    }

    // Copy constructor (deep copy)
    List(const List& other) : items(nullptr), capacity(other.capacity), size(other.size) {
        items = new T[capacity];
        for (int i = 0; i < size; i++) {
            items[i] = other.items[i];
        }
    }

    // Copy assignment (deep copy)
    List& operator=(const List& other) {
        if (this == &other) return *this;

        delete[] items;

        capacity = other.capacity;
        size = other.size;

        items = new T[capacity];
        for (int i = 0; i < size; i++) {
            items[i] = other.items[i];
        }
        return *this;
    }

    // Move constructor
    List(List&& other) noexcept : items(other.items), capacity(other.capacity), size(other.size) {
        other.items = nullptr;
        other.capacity = 0;
        other.size = 0;
    }

    // Move assignment
    List& operator=(List&& other) noexcept {
        if (this == &other) return *this;

        delete[] items;

        items = other.items;
        capacity = other.capacity;
        size = other.size;

        other.items = nullptr;
        other.capacity = 0;
        other.size = 0;

        return *this;
    }

    bool add(const T& item) {
        if (capacity == 0) resize(1);
        if (size >= capacity) resize(capacity * 2);

        items[size] = item;
        size++;
        return true;
    }

    T get(int index) const {
        if (index < 0 || index >= size) {
            throw out_of_range("List::get index out of range");
        }
        return items[index];
    }

    T& getRef(int index) {
        if (index < 0 || index >= size) {
            throw out_of_range("List::getRef index out of range");
        }
        return items[index];
    }

    void print() const {
        for (int i = 0; i < size; i++) {
            cout << items[i] << endl; // only works if T supports <<
        }
    }

    int getLength() const { return size; }
};
