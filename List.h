#pragma once
#include <iostream>
#include <string>

template <typename T>
class List {
private:
    T* items;
    int capacity;
    int size;

public:
    List() : items(nullptr), capacity(0), size(0) {}
    List(int initialCapacity) : capacity(initialCapacity), size(0) {
        items = new T[capacity];
    }

    ~List() {
        delete[] items;
    }

    bool add(T item) {
        if (size < capacity) {
            items[size] = item;
            size++;
            return true;
        }
        return false;
    }

    T get(int index) const { return items[index]; }

    T& getRef(int index) {
        return items[index];
    }

    // void sortByGameName() {
    //     for (int i = 0; i < size - 1; i++) {
    //         for (int j = 0; j < size - i - 1; j++) {
    //             // BoardGame uses getName()
    //             if (items[j]->getName() > items[j + 1]->getName()) {
    //                 T temp = items[j];
    //                 items[j] = items[j + 1];
    //                 items[j + 1] = temp;
    //             }
    //         }
    //     }
    // }

    // void print() {
    //     for (int i = 0; i < size; i++) {
    //         items[i]->printInfo(); // Using your BoardGame method
    //     }
    // }

    int getLength() const { return size; }
};