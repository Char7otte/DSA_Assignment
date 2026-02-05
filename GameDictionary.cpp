#include "GameDictionary.h"

#include<iostream>
#include<iomanip>

GameDictionary::GameDictionary() {}

void GameDictionary::print() {
    const int idWidth = 10;
    const int nameWidth = 25;
    const int playersWidth = 12;
    const int timeWidth = 15;
    const int yearWidth = 8;
    const int statusWidth = 12;

    std::cout << "\n" << std::string(85, '=') << "\n";
    std::cout << "                         GAME INVENTORY LIST" << "\n";
    std::cout << std::string(85, '=') << "\n";

    if (size == 0) {
        std::cout << "| No games found in the dictionary." << std::setw(50) << " |" << "\n";
        std::cout << std::string(85, '=') << "\n";
        return;
    }

    // Header
    std::cout << std::setw(idWidth) << "ID"
        << std::setw(nameWidth) << "NAME"
        << std::setw(playersWidth) << "PLAYERS"
        << std::setw(timeWidth) << "PLAYTIME"
        << std::setw(yearWidth) << "YEAR"
        << std::setw(statusWidth) << "STATUS" << "\n";

    std::cout << std::string(85, '-') << "\n";

    // Content
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* temp = items[i];

        while (temp != nullptr) {
            Item* boardGame = temp->item;
            boardGame->print();
            temp = temp->next;
        }
    }

    std::cout << std::string(85, '=') << "\n";
}

//void GameDictionary::print() {


//
//    // Traverse the Hash Map
//    for (int i = 0; i < MAX_SIZE; i++) {
//        Node* current = items[i];
//
//        while (current != nullptr) {
//            const ItemType& game = current->item;
//
//            // Formatting Players string (e.g., "2-4")
//            std::string playerRange = std::to_string(game->minPlayers) + "-" + std::to_string(game.maxPlayers);
//
//            // Formatting Playtime string (e.g., "30-60m")
//            std::string timeRange = to_string(game.minPlayTime) + "-" + to_string(game.maxPlayTime) + "m";
//
//            cout << left << setw(idWidth) << current->key
//                 << setw(nameWidth) << (game.name.length() > 22 ? game.name.substr(0, 22) + "..." : game.name)
//                 << setw(playersWidth) << playerRange
//                 << setw(timeWidth) << timeRange
//                 << setw(yearWidth) << game.yearPublished
//                 << setw(statusWidth) << (game.isBorrowed ? "Borrowed" : "Available")
//                 << endl;
//
//            current = current->next;
//        }
//    }
//
//    cout << string(85, '=') << endl;
//}

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