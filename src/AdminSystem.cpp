#include "AdminSystem.h"

#include "InputValidation.h"
#include "BorrowList.h"

#include<iomanip>

bool adminDashboard(GameDictionary& games, MemberDictionary& members, BorrowList& loans) {
    while (true) {
        std::cout << "1. Add a new board game" << "\n";
        std::cout << "2. Remove a board game" << "\n";
        std::cout << "3. Add a new member" << "\n";
        std::cout << "4. Display borrow history log" << "\n";
        std::cout << "5. Display all board games" << "\n";
        std::cout << "6. Display all members" << "\n";
        std::cout << "0. Logout" << "\n";
        std::string input;
        std::getline(std::cin, input);

        if (input == "1") {
            createAndAddGameMenu(games);
        }
        else if (input == "2") {
            deleteGameMenu(games);
        }
        else if (input == "3") {
            createMemberMenu(members);
        }
        else if (input == "4") {
            displayHistory(games, members, loans);
        }
        else if (input == "5") {
            games.print();
        }
        else if (input == "6") {
            members.print();
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

void createAndAddGameMenu(GameDictionary& gameDict) {
    std::cout << "\n===== Add New Board Game =====\n";
    std::string id, name;
    int minPlayers, maxPlayers, minPlaytime, maxPlaytime, yearPublished;

    // --- Input: Game ID ---
    while (true) {
        std::cout << "Enter Game ID (e.g. G004): ";
        std::getline(std::cin, id);
        if (id.empty()) {
            std::cout << "Game ID cannot be empty.\n";
            continue;
        }
        if (gameDict.get(id)) {
            std::cout << "This Game ID already exists. Please enter a different ID.\n";
            continue;
        }
        break;
    }

    // Get name
    name = getString("Enter Game Name: ");

    //Get players
    while (true) {
        minPlayers = getInt("Enter Min Players: ");
        maxPlayers = getInt("Enter Max Players: ");
        if (maxPlayers >= minPlayers) {
            break;
        }
        std::cout << "Max Players cannot be less than Min Players. Please try again.\n";
    }

    // Get playtime
    while (true) {
        minPlaytime = getInt("Enter Min Playtime (minutes): ");
        maxPlaytime = getInt("Enter Max Playtime (minutes): ");
        if (maxPlaytime >= minPlaytime) {
            break;
        }
        std::cout << "Max Playtime cannot be less than Min Playtime.\n";
    }

    // Get year
    yearPublished = getInt("Enter Year Published: ");

    // --- Create and add ---
    BoardGame* newGame = new BoardGame(id, name, minPlayers, maxPlayers, minPlaytime, maxPlaytime, yearPublished);

    if (gameDict.add(id, newGame)) {
        std::cout << "Game added successfully!\n";
    }
    else {
        std::cout << "\n Failed to add game. Please try again.\n";
    }
    std::cout << "==============================\n" << "\n";
}

void deleteGameMenu(GameDictionary& games) {
    std::cout << "\n===== Delete Board Game =====\n";
    games.print();
    std::string id;

    while (true) {
        id = getString("Enter Game ID to delete (e.g. G001): ");
        BoardGame* gameToRemove = nullptr;
        games.get(id, gameToRemove);
        if (gameToRemove != nullptr) {
            if (gameToRemove->getIsBorrowed()) {
                std::cout << gameToRemove->getName() << " is being lent to someone and is unable to be removed.\n";
                return;
            }
            else {
                std::string removedGameName = gameToRemove->getName();
                if (games.remove(id)) {
                    std::cout << removedGameName << " has been removed." << "\n" << "\n";
                    return;
                }
                std::cout << removedGameName << " could not be removed. Please try again" << "\n";
            }
        }
        std::cout << id << " not found. Please try again." << "\n";
    }
}

void createMemberMenu(MemberDictionary& members) {
    std::cout << "\n===== Create Member =====\n";

    std::string newMemberID, newMemberName;
    bool isAdmin;

    while (true) {
        newMemberID = getString("Enter Member ID (e.g., M001): ");

        if (members.get(newMemberID)) {
            std::cout << "This Member ID already exists.\n";
            continue;
        }
        break;
    }

    newMemberName = getString("Enter Member Name: ");

    Member* newMember = new Member(newMemberID, newMemberName);

    if (members.add(newMemberID, newMember)) {
        std::cout << newMemberName << " has been added.\n";
    }
    else {
        std::cout << "Failed to add " << newMemberName << " . Please try again.\n";
    }

    std::cout << "==============================\n" << "\n";
}

void displayHistory(GameDictionary& games, MemberDictionary& members, BorrowList& loans) {
    if (loans.isEmpty()) {
        std::cout << "Borrow log is empty." << "\n" << "\n";
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

    loans.print(games, members);

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n" << "\n";
}