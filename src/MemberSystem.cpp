#include "MemberSystem.h"
#include "InputValidation.h"

#include <iomanip>

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
            getBorrowHistory(member.getID(), loans);
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
            continue;
        }

        bool memberSuccess = borrower.borrowGame(*gameToBorrow); //This fails if member tries to borrow too many games
        if (!memberSuccess) {
            std::cout << "You have borrowed too many games. Return some to borrow more." << "\n" << "\n";
            return;
        }
        bool gameSuccess = gameToBorrow->borrowGame(borrower.getID(), borrower.getName());
        bool logSuccess = loans.add(borrower.getID(), gameID);

        std::cout << "You have borrowed " << gameToBorrow->getName() << ".\n" << "\n";

        return;
    }
}

void memberReturnMenu(GameDictionary& games, Member& returner, BorrowList& loans) {
    if (!returner.hasLoans()) {
        std::cout << "You have not borrowed anything." << "\n" << "\n";
        return;
    }

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

        std::cout << "You have returned " << gameToReturn->getName() << ".\n" << "\n";
        return;
    }
}

void getBorrowHistory(std::string borrowerID, BorrowList &loans) {
    BorrowList borrowHistory = loans.findAll(borrowerID);
    if (borrowHistory.isEmpty()) {
        std::cout << "You have not borrowed anything." << "\n" << "\n";
        return;
    }

    const int TOTAL_WIDTH = 100;

    std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ') << "BORROW HISTORY\n";
    std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

    std::cout << std::left << std::setw(10) << "MEMBER ID"
        << " | " << std::setw(8) << "GAME ID"
        << " | " << std::setw(15) << "LOAN DATE"
        << " | " << std::setw(15) << "RETURN DATE"
        << "\n";

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    borrowHistory.print();

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n" << "\n";
}