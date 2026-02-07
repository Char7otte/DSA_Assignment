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
            BoardGame* boardGame = temp->item;
            boardGame->print();
            temp = temp->next;
        }
    }

    std::cout << std::string(85, '=') << "\n";
}

void GameDictionary::printAvailable() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* temp = items[i];

        while (temp != nullptr) {
            BoardGame* boardGame = temp->item;
            boardGame->printAvailable();
            temp = temp->next;
        }
    }
}