#include "MemberSystem.h"
#include "BoardGame.h"
#include "BorrowList.h"
#include "GameDictionary.h"
#include "Member.h"
#include "MemberDictionary.h"

#include "InputValidation.h"

#include <iomanip>
#include <ios>
#include <iostream>
#include <string>

bool memberDashboard(GameDictionary& games,MemberDictionary& members, BorrowList& loans, Member& member) {
    while (true) {
        std::cout << "1. Borrow a board game" << "\n";
        std::cout << "2. Return a board game" << "\n";
        std::cout << "3. Display borrow history" << "\n";
        std::cout << "4. Display all board games" << "\n";
        std::cout << "5. Leave a review" << "\n";
        std::cout << "6. Read reviews" << "\n";
        std::cout << "7. Log match" << "\n";
        std::cout << "8. View match logs" << "\n";
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
            getBorrowHistory(games, members, loans, member.getID());
        }
        else if (input == "4") {
            games.print();
        }
        else if (input == "5") {
            leaveReview(games, member);
        }
        else if (input == "6") {
            viewReviews(games, members);
        }
        else if (input == "7") {
            logMatch(games, member.getID());
        }
        else if (input == "8") {
            printMatches(games);
        }
        else if (input == "0") {
            return true;
        }
        else {
            std::cout << "Invalid input. Please try again." << "\n";
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

void getBorrowHistory(GameDictionary& games, MemberDictionary& members, BorrowList &loans, std::string borrowerID) {
    BorrowList borrowHistory = loans.findAll(borrowerID);
    if (borrowHistory.isEmpty()) {
        std::cout << "You have not borrowed anything." << "\n" << "\n";
        return;
    }

    const int TOTAL_WIDTH = 100;

    std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ') << "BORROW HISTORY\n";
    std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

    std::cout << std::left << std::setw(10) << "MEMBER ID"
        << " | " << std::setw(20) << "MEMBER NAME"
        << " | " << std::setw(8) << "GAME ID"
        << " | " << std::setw(20) << "GAME NAME"
        << " | " << std::setw(15) << "LOAN DATE"
        << " | " << std::setw(15) << "RETURN DATE"
        << "\n";

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    borrowHistory.print(games, members);

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
}

void leaveReview(GameDictionary& games, Member& member) {
    games.print();
    std::cout << "\n===== LEAVE GAME REVIEW =====\n";

    while (true) {
        std::string id = getString("Enter ID of game to review: ");
        BoardGame* foundBoardGame = nullptr;
        games.get(id, foundBoardGame);
        if (foundBoardGame == nullptr) {
            std::cout << "Game not found. Please try again." << "\n";
            continue;
        }

        std::cout << "Reviewing:" << foundBoardGame->getName() << "\n";
        int rating = -1;
        while (true) {
            rating = getInt("Enter your rating (1-5): ");
            if (rating < 1 || rating > 5) {
                std::cout << "Rating is out of range. Please try again." << "\n";
                continue;
            }
            break;
        }
        std::string reviewBody = getString("Enter your review: ");
        bool success = foundBoardGame->addReview(member.getID(), reviewBody, rating);
        if (success) {
            std::cout << rating << "* review added to " << foundBoardGame->getName() << "\n";
        }
        else {
            std::cout << "Error adding review. Operation cancelled.";
        }
        break;
    }
    std::cout << "==============================\n" << "\n";
}

void viewReviews(GameDictionary& games, MemberDictionary& members) {
    int TOTAL_WIDTH = 119;

    std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ') << "REVIEWED GAMES\n";
    std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

    std::cout << std::left << std::setw(8) << "ID"
        << " | " << std::setw(50) << "NAME"
        << " | " << std::setw(15) << "PLAYERS"
        << " | " << std::setw(15) << "PLAYTIME"
        << " | " << std::setw(6) << "YEAR"
        << " | " << "STATUS" << "\n";

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
    bool printed = games.printReviewed();
    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    if (!printed) {
        std::cout << "No reviews found.\n\n";
        return;
    }

    std::cout << "\n===== VIEW GAME REVIEWS =====\n";
    BoardGame* foundBoardGame = nullptr;

    while (true) {
        std::string id = getString("Enter ID of game: ");
        games.get(id, foundBoardGame);

        if (foundBoardGame == nullptr) {
            std::cout << "Game not found. Please try again.\n";
            continue;
        }
        break;
    }

    // =====================
    // NORMAL DISPLAY
    // =====================
    TOTAL_WIDTH = 119;

    std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ')
        << "REVIEWS FOR " << foundBoardGame->getName() << "\n";
    std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

    std::cout << std::left << std::setw(11) << "ReviewerID"
        << " | " << std::setw(30) << "Reviewer"
        << " | " << std::setw(15) << "Review Date"
        << " | " << std::setw(7) << "Rating"
        << " | " << "Body"
        << "\n";

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
    foundBoardGame->printReviews(members);
    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    // =====================
    // OPTIONAL SORTED VIEW
    // =====================
    int choice;
    std::cout << "\nEnter 1 to display reviews by highest rating: ";
    std::cin >> choice;

    if (!std::cin) {
        std::cin.clear();
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (choice == 1) {
        std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 16, ' ')
            << "REVIEWS (HIGHEST RATING FIRST)\n";
        std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

        std::cout << std::left << std::setw(11) << "ReviewerID"
            << " | " << std::setw(30) << "Reviewer"
            << " | " << std::setw(15) << "Review Date"
            << " | " << std::setw(7) << "Rating"
            << " | " << "Body"
            << "\n";

        std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
        foundBoardGame->printReviewsDescendingRating(members);
        std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
    }
}



void logMatch(GameDictionary& games, std::string memberID) {
    games.print();
    std::cout << "\n===== LOG MATCH =====\n";
    BoardGame* foundBoardGame = nullptr;
    std::string gameID;
    while (true) {
         gameID = getString("Enter ID of game you played: ");
        games.get(gameID, foundBoardGame);
        if (foundBoardGame == nullptr) {
            std::cout << "Game not found. Please try again." << "\n";
            continue;
        }
        break;
    }

    std::cout << "Logging match for " << foundBoardGame->getName() << "\n";
    std::string playerIDs = getString("Enter the IDs of the players (e.g M1,M2,M3): ");
    std::string winnerID = getString("Enter ID of the winner: ");
    int matchDuration = getInt("Enter duration of match (minutes): ");

    bool success = foundBoardGame->addMatch(memberID, gameID, matchDuration, playerIDs, winnerID);
    if (success) {
        std::cout << "Match logged." << "\n" << "\n";
    }
    else {
        std::cout << "Error logging match. Please try again." << "\n" << "\n";
    }
}

void printMatches(GameDictionary& games) {
    int TOTAL_WIDTH = 119;

    std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ') << "LOGGED GAMES\n";
    std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

    std::cout << std::left << std::setw(8) << "ID"
        << " | " << std::setw(50) << "NAME"
        << " | " << std::setw(15) << "PLAYERS"
        << " | " << std::setw(15) << "PLAYTIME"
        << " | " << std::setw(6) << "YEAR"
        << " | " << "STATUS" << "\n";

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    bool printed = games.printMatched();

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    if (!printed) {
        std::cout << "No matches logged." << "\n" << "\n";
        return;
    }


    std::cout << "\n===== VIEW MATCH LOGS =====\n";
    BoardGame* foundBoardGame = nullptr;
    std::string gameID;
    while (true) {
        gameID = getString("Enter ID of game: ");
        games.get(gameID, foundBoardGame);
        if (foundBoardGame == nullptr) {
            std::cout << "Game not found. Please try again." << "\n";
            continue;
        }
        break;
    }

    TOTAL_WIDTH = 119;

    std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ') << "MATCH LOGS FOR " << foundBoardGame->getName() << "\n";
    std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

    std::cout << std::left << std::setw(8) << "LoggerID"
        << " | " << std::setw(8) << "GameID"
        << " | " << std::setw(15) << "Match Date"
        << " | " << std::setw(15) << "Match Duration"
        << " | " << std::setw(15) << "Player count"
        << " | " << std::setw(15) << "PlayerIDs"
        << " | " << std::setw(8) << "WinnerID"
        << "\n";

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
    foundBoardGame->printMatches();
    std::cout << std::string(TOTAL_WIDTH, '-') << "\n" << "\n";
}