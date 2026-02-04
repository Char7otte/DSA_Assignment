//
// Created by gongy on 4/
#include "MemeberDictionary.h"
#include<iostream>

// Constructor
MemberDictionary::MemberDictionary() {
    for (int i = 0; i < MAX_SIZE; i++) {
        items[i] = nullptr;
    }
    size = 0;
}

MemberDictionary::~MemberDictionary() {
    for (int i = 0; i < MAX_SIZE; i++) {

        MemberNode* current = items[i];
        while (current != nullptr) {

            MemberNode* temp = current;
            current = current->next;
            delete temp;
        }
        items[i] = nullptr;
    }
}

// // Hash Function
// // Simple modulo hash
int MemberDictionary::hash(KeyType key) {
    if (key.empty()) {
        return 0; // avoid invalid index
    }
    int hashValue = 0;

    for (auto character : key) {
        hashValue = (hashValue * 31 + character) % MAX_SIZE;
    }
    return hashValue;
}
// // Add new item
bool MemberDictionary::addMember(KeyType newKey, MemberItemType newItem) {
    int index = hash(newKey);

    // items[index] is the current top node, items are list of topnode

    MemberNode* current = items[index];

    //Check whether the key enter by the user is already exist
    while (current != nullptr) {
        if (current->key == newKey) {
            //println("Duplicate key, {} alreay exist",newKey);
            // cout << "Duplicate key, " << newKey << " already exists" << endl;

            return false; // Duplicate key
        }
        current = current->next;
    }

    // Create new node

    MemberNode* newNode = new MemberNode;

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

// // Remove an item
// bool MemberDictionary::remove(KeyType key) {
//     int index = hash(key);
//
//     Node* current = items[index];
//     Node* prev = nullptr;
//
//     while (current != nullptr) {
//         if (current->key == key) {
//             if (prev == nullptr) {
//                 items[index] = current->next;
//             } else {
//                 prev->next = current->next;
//             }
//
//             delete current;
//             size--;
//             return true;   // ✅ deleted successfully
//         }
//
//         prev = current;
//         current = current->next;
//     }
//
//     return false; // ❌ not found
// }

// // Get item by key
MemberItemType* MemberDictionary::getMember(KeyType key) {
    int index = hash(key);

    MemberNode* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            return &(current->item);  // address of stored object
        }
        current = current->next;
    }

    return nullptr;
}

// Check if key exists
bool MemberDictionary::containsMember(KeyType key) {
    int index = hash(key);

    MemberNode* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            return true;
        }
        current = current->next;
    }

    return false;
}

// Check if empty
bool MemberDictionary::isEmpty() {
    return size == 0;
}

// Get number of items

int MemberDictionary::getLength() {
    return size;
}

//void MemeberDictionary::print() {
//     cout << "\n========== Game List ==========\n";
//
//     if (size == 0) {
//         cout << "No games found.\n";
//         cout << "===============================\n";
//         return;
//     }
//
//
//     for (int i = 0; i < MAX_SIZE; i++) {
//         Node* current = items[i];
//
//         while (current != nullptr) {
//             const ItemType& game = current->item;
//
//                 cout  << "Game ID: " << current->key   // key is the id string
//                  << " | Name: " << game.name
//                  << " | Players: " << game.minPlayers << "-" << game.maxPlayers
//                  << " | Playtime: " << game.minPlayTime << "-" << game.maxPlayTime << " mins"
//                  << " | Year: " << game.yearPublished
//                  << " | Status: " << (game.isBorrowed ? "Borrowed" : "Available")
//                  << "\n";
//             current = current->next;
//         }
//     }
//
//     cout << "===============================\n";
// }

// Print Game contents
// void MemberDictionary::print() {
//
//     cout << "Game contents:" << endl;
//
//     for (int i = 0; i < MAX_SIZE; i++) {
//         if (items[i] != nullptr) {
//             cout << "Index " << i << ": ";
//             Node* current = items[i];
//             while (current != nullptr) {
//                 const ItemType &game = current->item;
//                 cout << "[key=" << current->key
//                      << ", id=" << game.id
//                      << ", name=\"" << game.name << "\""
//                      // << ", players=" << g.minPlayers << "-" << g.maxPlayers
//                      // << ", playtime=" << g.minPlayTime << "-" << g.maxPlayTime
//                      // << ", year=" << g.yearPublished
//                      // << ", borrowed=" << (g.isBorrowed ? "yes" : "no")
//                      << "] -> ";
//
//                 current = current->next;
//             }
//             cout << "NULL" << endl;
//         }
//     }
// }



