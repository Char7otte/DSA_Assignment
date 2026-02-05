#include "Dictionary.h"

#include<iostream>

Dictionary::Dictionary() {};

Dictionary::~Dictionary() {
        for (int i = 0; i < MAX_SIZE; i++) {

            Node* current = items[i];

            //Go through the current index in case there are collisions
            while (current != nullptr) {
                Node* previous = current;     
                current = current->next;   
                delete previous;
            }

            items[i] = nullptr;
        }
}

// Modulo hash
int Dictionary::hash(const KeyType keyToHash) {
    if (keyToHash.empty()) {
        return 0;
    }

    int hashValue = 0;

    for (char c : keyToHash) {
        hashValue = (hashValue * 31 + c) % MAX_SIZE;
    }
    return hashValue;
};

// Add a new item with the specified key
bool Dictionary::add(const KeyType newKey, const ItemType newItem) {
    int index = hash(newKey);
    Node* temp = items[index];

    //Check if the dictionary already has an item with newKey.
    // KeyType is the ID of the item, which means the dictionary already contains a copy of the 'new' node.
    while (temp != nullptr) {
        if (temp->key == newKey) {
            std::cout << "Error. Identical ID found in dictionary." << "\n";
            return false;
        }
        temp = temp->next;
    }

    Node* newNode = new Node;
    newNode->key = newKey;
    newNode->item = newItem;

    //Unnecessary to handle if items[index] == nullptr, since next'll remain nullptr.
     newNode->next = items[index];
    items[index] = newNode;
    size++;
    return true;
};

// Remove an item with the specified key
bool Dictionary::remove(const KeyType keyOfItemToRemove) {
    int index = hash(keyOfItemToRemove);
    Node* temp = items[index];
    Node* previous = nullptr;

    while (temp != nullptr) {
        if (temp->key == keyOfItemToRemove) {
            if (previous == nullptr) { //If previous is nullptr, it means that the first node is being removed.
                items[index] = temp->next;  //Unnecessary to handle if there are no more items after, since it'll remain nullptr.
            }
            else {
                previous->next = temp->next;
            }
            delete temp;
            size--;
            return true;
        }
        previous = temp;
        temp = temp->next;
    }

    return false;
};

// Use a key to find its value
ItemType* Dictionary::get(const KeyType keyToFind) {
    int index = hash(keyToFind);
    Node* temp = items[index];

    while (temp != nullptr) {
        if (temp->key == keyToFind) {
            return &temp->item;
        }
        temp = temp->next;
    }
    return nullptr;
};

// Check if the dictionary contains a key
bool Dictionary::contains(const KeyType keyToContain) {
    int index = hash(keyToContain);
    Node* temp = items[index];
    
    while (temp != nullptr) {
        if (temp->key == keyToContain) {
            return true;
        }
        temp = temp->next;
    }
    return false;
};

bool Dictionary::isEmpty() {
    return size == 0;
};

int Dictionary::getLength() {
    return size;
};