#include "GameDictionary.h"
#include "BoardGame.h"
#include "Dictionary.h"

#include<iostream>
#include<iomanip>
#include <ios>
#include <string>

GameDictionary::GameDictionary() {}

void GameDictionary::print() {
    const int TOTAL_WIDTH = 119;

    std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ') << "GAME INVENTORY LIST\n";
    std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

    std::cout << std::left << std::setw(8) << "ID"
        << " | " << std::setw(50) << "NAME"
        << " | " << std::setw(15) << "PLAYERS"
        << " | " << std::setw(15) << "PLAYTIME"
        << " | " << std::setw(6) << "YEAR"
        << " | " << "STATUS" << "\n";

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    if (size == 0) {
        // Center the empty message within the table width
        std::cout << std::setw(TOTAL_WIDTH) << "| No games found in the dictionary." << " |\n";
        std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
        return;
    }

    // Content
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* temp = items[i];

        while (temp != nullptr) {
            BoardGame* boardGame = temp->item;
            boardGame->print();
            temp = temp->next;
        }
    }

    std::cout << std::string(TOTAL_WIDTH, '=') << "\n" << "\n";
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

bool GameDictionary::printReviewed() {
    bool printed = false;
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* temp = items[i];

        while (temp != nullptr) {
            BoardGame* boardGame = temp->item;
            bool success = boardGame->printReviewed();
            if (success) {
                printed = true;
            }
            temp = temp->next;
        }
    }
    return printed;
}