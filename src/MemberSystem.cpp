#include "MemberSystem.h"
#include "InputValidation.h"

bool memberDashboard(GameDictionary& games, Member& member, BorrowList& loans) {
    while (true) {
        std::cout << "1. Borrow a board game" << "\n";
        std::cout << "2. Return a board game" << "\n";
        std::cout << "3. Display borrow history" << "\n";
        std::cout << "4. Display all board games" << "\n";
        std::cout << "0. Logout" << "\n";
        std::string input;
        std::getline(std::cin, input);

        if (input == "1") {
            memberBorrowMenu(games, member, loans);
        }
        else if (input == "2") {
            memberReturnMenu(games, member, loans);
        }
        else if (input == "3") {
            std::cout << "Display your borrow history";
        }
        else if (input == "4") {
            games.print();
        }
        else if (input == "0") {
            return true;
        }
        else {
            std::cout << "Invalid input. Please try again.";
        }
    }
    return false;
}

void memberBorrowMenu(GameDictionary& games, Member& borrower, BorrowList& loans) {
    std::cout << "\n===== Borrow Game =====\n";

    // Show all games first
    games.printAvailable();

    while (true) {
        std::string gameID = getString("Enter Game ID to borrow: ");

        BoardGame* gameToBorrow = nullptr;
        games.get(gameID, gameToBorrow);
        if (gameToBorrow == nullptr) {
            std::cout << "Board Game ID not found. Please try again.\n";
            continue;
        }

        if (gameToBorrow->getIsBorrowed()) {
            std::cout << "This board game has been lent to someone else.\n";
            return;
        }

        bool memberSuccess = borrower.borrowGame(*gameToBorrow);
        bool gameSuccess = gameToBorrow->borrowGame(borrower.getID(), borrower.getName());
        bool logSuccess = loans.add(borrower.getID(), gameID);

        std::cout << "You have borrowed " << gameToBorrow->getName() << ".\n" << "\n";

        return;
    }
}

void memberReturnMenu(GameDictionary& games, Member& returner, BorrowList& loans) {
    std::cout << "\n===== Return Game =====\n";
    returner.printLoans();
    std::string date = getTodayDate(); //Used multiple times in this function

    // 2) Ask for game ID
    while (true) {
        std::string gameID = getString("Enter Game ID to return: ");

        // 3) Retrieve game from dictionary
        BoardGame* gameToReturn = nullptr;
        games.get(gameID, gameToReturn);

        if (gameToReturn == nullptr) {
            std::cout << "Game ID not found. Please try again.\n";
            continue;
        }

        // Check if this is the same user that borrowed the game
        bool memberSuccess = returner.returnGame(*gameToReturn);
        if (!gameToReturn->getIsBorrowed() || !memberSuccess) {
            std::cout << "You did not borrow this game. Please try again.\n";
            continue;
        }

        bool gameSuccess = gameToReturn->returnGame();

        bool logSuccess = loans.returnGame(returner.getID(), gameID);

        std::cout << "Return successful!\n";
        std::cout << "You returned Game " << gameID << " on " << date << "\n";
        return;
    }
}