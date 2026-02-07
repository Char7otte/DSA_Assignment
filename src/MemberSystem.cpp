#include "MemberSystem.h"
#include "InputValidation.h"
#include "MasterHistoryLog.h"

bool memberDashboard(GameDictionary& games, Member& member, MasterHistoryLog& masterLog) {
    while (true) {
        std::cout << "1. Borrow a board game" << "\n";
        std::cout << "2. Return a board game" << "\n";
        std::cout << "3. Display borrow history" << "\n";
        std::cout << "4. Display all board games" << "\n";
        std::cout << "0. Logout" << "\n";
        std::string input;
        std::getline(std::cin, input);

        if (input == "1") {
            memberBorrowMenu(games, member, masterLog);
            masterLog.printAll();
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

void memberBorrowMenu(GameDictionary& games, Member& borrower, MasterHistoryLog& masterLog) {
    std::cout << "\n===== Borrow Game =====\n";

    // Show all games first
    games.print();

    while (true) {
        std::string gameID = getString("Enter Game ID to borrow: ");

        BoardGame* gameToBorrow = nullptr;
        games.get(gameID, gameToBorrow);
        if (gameToBorrow == nullptr) {
            std::cout << "Board Game ID not found. Please try again.\n";
            continue;
        }

        if (gameToBorrow->getIsBorrowed()) {
            std::cout << "This board game is being lent to someone else.\n";
            return;
        }

        std::string today = getTodayDate();

        if (!borrower.borrowGame(*gameToBorrow)|| !gameToBorrow->borrowGame(borrower.getID(),
            borrower.getName())) {
            std::cout << "Borrow request unsuccessful.\n";
            return;
        }

        bool logSuccess = masterLog.add(*gameToBorrow, borrower, today);
        if (!logSuccess) {
            std::cout << "Borrowed successfully, but failed to log history.\n";
            // Still treat as success from user perspective
        }

        std::cout << "Borrow successful!\n";
        std::cout << "You have borrowed " << gameToBorrow->getName() << " on " << today << "\n";

        return;
    }
}