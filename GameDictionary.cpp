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
        return 0; // avoid invalid index
    }
    int hashValue = 0;

    for (auto character : key) {
        hashValue = (hashValue * 31 + character) % MAX_SIZE;
    }
    return hashValue;
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
            // cout << "Duplicate key, " << newKey << " already exists" << endl;

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
bool GameDictionary::remove(KeyType key) {
    int index = hash(key);

    Node* current = items[index];
    Node* prev = nullptr;

    while (current != nullptr) {
        if (current->key == key) {
            if (prev == nullptr) {
                items[index] = current->next;
            } else {
                prev->next = current->next;
            }

            delete current;
            size--;
            return true;   // ✅ deleted successfully
        }

        prev = current;
        current = current->next;
    }

    return false; // ❌ not found
}

// Get item by key
ItemType* GameDictionary::get(KeyType key) {
    int index = hash(key);
    Node* current = items[index];

    while (current != nullptr) {
        if (current->key == key) {
            return &(current->item);  // address of stored object
        }
        current = current->next;
    }

    return nullptr;
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
void GameDictionary::print() {
    cout << "\n========== Game List ==========\n";

    if (size == 0) {
        cout << "No games found.\n";
        cout << "===============================\n";
        return;
    }


    for (int i = 0; i < MAX_SIZE; i++) {
        Node* current = items[i];

        while (current != nullptr) {
            const ItemType& game = current->item;

                cout  << "Game ID: " << current->key   // key is the id string
                 << " | Name: " << game.name
                 << " | Players: " << game.minPlayers << "-" << game.maxPlayers
                 << " | Playtime: " << game.minPlayTime << "-" << game.maxPlayTime << " mins"
                 << " | Year: " << game.yearPublished
                 << " | Status: " << (game.isBorrowed ? "Borrowed" : "Available")
                 << "\n";
            current = current->next;
        }
    }

    cout << "===============================\n";
}

// Print Game contents
// void GameDictionary::print() {
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



// games storage most important,
// the admin want to see the games are burrowed but not returned yet.
// create a linked list just for it
// the member should not need to access the burrowing record of a game, does the user need to
// access their record of borrowing？
// tasks created a list of games burrow not return.
// the user have
//an array that will automatically resize if the borrowing record is too much in both games and the members
// an linkedlist for burrowed games not return
// memeber id and name, date borrow and return.
// games id and name, date borrow and return