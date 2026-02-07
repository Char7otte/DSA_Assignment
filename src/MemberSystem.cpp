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
            //memberReturnMenu(games, member, loans);
            loans.print();
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

        loans.print();

        std::cout << "Borrow successful!\n";
        std::cout << "You have borrowed " << gameToBorrow->getName() << " on " << getTodayDate() << "\n";

        return;
    }
}

//void memberReturnMenu(GameDictionary& games,
//    Member& returner,
//    MasterHistoryLog& loans) {
//    cout << "\n===== Return Game =====\n";
//
//    // 1) Show unreturned games from this member
//    returner.printUnreturnedGames();
//
//    // 2) Ask for game ID
//    while (true) {
//        std::string gameID = getString("Enter Game ID to return: ");
//
//        // 3) Retrieve game from dictionary
//        BoardGame* gameToReturn = nullptr;
//        games.get(gameID, gameToReturn);
//
//        if (gameToReturn == nullptr) {
//            cout << "Game ID not found. Please try again.\n";
//            continue;
//        }
//
//        // 4) Check if game is borrowed (overall)
//        if (!gameToReturn->getIsBorrowed()) {
//            cout << "This game is not currently borrowed (already returned).\n";
//            continue;
//        }
//
//        // 5) Return stage
//        string today = getTodayDate();
//
//        // Member tries to return (checks if THIS member borrowed it)
//        bool memberOk = returner.returnGame(*gameToReturn);
//        if (!memberOk) {
//            cout << "Return failed: This game is not currently borrowed by you.\n";
//            continue; // let them try again
//        }
//
//        // Game updates return date
//        bool gameOk = gameToReturn->returnGame();
//        if (!gameOk) {
//            cout << "Return failed unexpectedly (game state error).\n";
//            return;
//        }
//
//        // Update master history log
//        bool logOk = loans.markReturned(today, gameID);
//        if (!logOk) {
//            cout << "Returned, but history record not found to update.\n";
//            // You can still treat it as success for user experience
//        }
//
//        cout << "Return successful!\n";
//        cout << "You returned Game " << gameID << " on " << today << "\n";
//        return;
//    }
//}