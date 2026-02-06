#include "MemberSystem.h"

bool memberDashboard(GameDictionary& games) {
    while (true) {
        std::cout << "1. Borrow a board game" << "\n";
        std::cout << "2. Return a board game" << "\n";
        std::cout << "3. Add a new member" << "\n";
        std::cout << "4. Display all board games" << "\n";
        std::cout << "0. Logout" << "\n";
        std::string input;
        std::getline(std::cin, input);

        if (input == "1") {
            std::cout << "Borrow a board game";
        }
        else if (input == "2") {
            std::cout << "Return a board game";
        }
        else if (input == "3") {
            std::cout << "Display your borrow history";
        }
        else if (input == "4") {
            games.print();
        }
        else if (input == "0") {
            break;
        }
        else {
            std::cout << "Invalid input. Please try again.";
        }
    }
    return false;
}