#include "GameDictionary.h"
#include<iostream>

// Constructor
GameDictionary::GameDictionary() {
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = nullptr;
    }
    size = 0;
}

// Destructor
GameDictionary::~GameDictionary() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* current = items[i];
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        items[i] = nullptr;
    }
}

// Hash Function
// Simple modulo hash
int GameDictionary::hash(KeyType key) {
    if (key.empty()) {
        return -1;
    }
    int hashValue = 0;

    for (auto character : key) {
        hashValue = (hashValue * 31 + character) % MAX_SIZE;
    }
    return hashValue ;
}
// Add new item
bool GameDictionary::add(KeyType newKey, ItemType newItem) {
    int index = hash(newKey);

    // items[index] is the current top node, items are list of topnode
    Node* current = items[index];

    //Check whether the key enter by the user is already exist
    while (current != nullptr) {
        if (current->key == newKey) {
            //println("Duplicate key, {} alreay exist",newKey);
            cout << "Duplicate key, " << newKey << " already exists" << endl;

            return false; // Duplicate key
        }
        current = current->next;
    }

    // Create new node
    Node* newNode = new Node;

    // key value is the key value given by the user
    newNode->key = newKey;

    // newItem is the item value given by the user
    newNode->item = newItem;
    newNode->next = items[index];

    // Insert at head (faster)
    items[index] = newNode;
    size++;

    return true;
}

// Remove an item
void GameDictionary::remove(KeyType key) {

    int index = hash(key);

    // The current top node
    Node* current = items[index];
    Node* prev = nullptr;

    while (current != nullptr) {

        // Found the node to remove
        if (current->key == key) {

            // It is the only node in the position
            if (prev == nullptr) {
                // Removing the first node in the chain, use current->next, because the
                // might be another node behind it
                items[index] = current->next; // first node
            }
            else {
                // Removing a node in the middle or end
                prev->next = current->next;
            }
            delete current;
            size--;
            return;

        }

        prev = current;
        current = current->next;

    }
}

// Get item by key
ItemType GameDictionary::get(KeyType key) {
    int index = hash(key);

    Node* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            return current->item;
        }
        current = current->next;
    }

    return "";
}

// Check if key exists
bool GameDictionary::contains(KeyType key) {
    int index = hash(key);
    Node* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Check if empty
bool GameDictionary::isEmpty() {
    return size == 0;
}

// Get number of items
int GameDictionary::getLength() {
    return size;
}

// Print Game contents
void GameDictionary::print() {

    cout << "Game contents:" << endl;

    for (int i = 0; i < MAX_SIZE; i++) {
        if (items[i] != nullptr) {
            cout << "Index " << i << ": ";
            Node* current = items[i];
            while (current != nullptr) {
                cout << "[" << current->key << ", " << current->item << "] -> ";
                current = current->next;
            }
            cout << "NULL" << endl;
        }
    }
}
