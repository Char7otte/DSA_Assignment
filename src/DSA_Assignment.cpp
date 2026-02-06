// Classes
#include "GameDictionary.h"
#include "MemberDictionary.h"
#include "BoardGame.h"
#include "Member.h"

// Functions
#include "FileUtilities.h"
#include "InputValidation.h"

#include<string>
#include<iostream>

//Account functions
Member* login(MemberDictionary& members);
bool adminDashboard(GameDictionary& games);
bool memberDashboard(GameDictionary& games);

// Admin functions
void createAndAddGameMenu(GameDictionary& games);
void deleteGameMenu(GameDictionary& games);

int main() {
    GameDictionary gameDict;
    readGameFile("./data/games.csv", gameDict);
    MemberDictionary memberDict;
    readMemberFile("./data/members.csv", memberDict);
    Member* loggedInAccount;

    while (true) {
        std::cout << "Welcome to the BGC Portal!" << "\n";
        std::cout << "1. Login" << "\n";
        std::cout << "0. Quit" << "\n";

        std::string input;
        std::getline(std::cin, input);
        if (input == "1") {
            while (true) {
                loggedInAccount = login(memberDict);
                if (loggedInAccount == nullptr) {
                    std::cout << "Invalid credentials. Please try again." << "\n";
                    continue;
                }
                break;
            }
            bool logout = false;
            while (!logout) {
                std::cout << "\n";
                std::cout << "Welcome, " << loggedInAccount->getName() << "!" << "\n";
                if (loggedInAccount->getIsAdmin()) {
                    logout = adminDashboard(gameDict);
                }
                else {
                    logout = memberDashboard(gameDict);
                }
            }

            return 0;
        }
        else if (input == "0") {
            std::cout << "Goodbye!";
            break;
        }
        else {
            std::cout << "Invalid input. Please try again.";
            continue;
        }
        return 0;
    }

    return 0;
};

Member* login(MemberDictionary& members) {
    std::string id;
    std::cout << "Enter your ID: ";
    std::getline(std::cin, id);

    Member* foundAccount;
    members.get(id, foundAccount);
    return foundAccount;
}

bool adminDashboard(GameDictionary& games) {
    while (true) {
        std::cout << "1. Add a new board game" << "\n";
        std::cout << "2. Remove a board game" << "\n";
        std::cout << "3. Add a new member" << "\n";
        std::cout << "4. Display borrow history log" << "\n";
        std::cout << "5. Display all board games" << "\n";
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
            std::cout << "Add a new member";
        }
        else if (input == "4") {
            std::cout << "Display borrow history log";
        }
        else if (input == "5") {
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
        std::cout << "\n Game added successfully!\n";
    }
    else {
        std::cout << "\n Failed to add game. Please try again.\n";
    }
    std::cout << "==============================\n";
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

//
//std::string getCurrentDate() {
//    // 1. Get the current system time
//    auto now = std::chrono::system_clock::now();
//
//    // 2. Convert to a time_t object (standard C time)
//    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
//
//    // 3. Convert to local time structure
//    std::tm* localTime = std::localtime(&currentTime);
//
//    // 4. Use stringstream to format it (YYYY-MM-DD)
//    std::stringstream ss;
//    ss << std::put_time(localTime, "%Y-%m-%d");
//
//    return ss.str();
//}
//void createMemberMenu(MemberDictionary& memberDict) {
//    std::cout << "\n===== Create Member =====\n";
//
//    std::string memberId;
//    std::string memberName;
//
//    // Member ID (no spaces)
//    while (true) {
//        std::cout << "Enter Member ID (e.g., M001): ";
//        std::cin >> memberId;
//
//        if (memberId.empty()) {
//            std::cout << "Member ID cannot be empty.\n";
//            continue;
//        }
//
//        // If you have containsMember(), use it:
//        if (memberDict.containsMember(memberId)) {
//            std::cout << "This Member ID already exists.\n";
//            continue;
//        }
//
//        break;
//    }
//
//    // clear newline before getline
//    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//
//    // Member name (can contain spaces)
//    while (true) {
//        std::cout << "Enter Member Name: ";
//        std::getline(std::cin, memberName);
//
//        if (memberName.empty()) {
//            std::cout << "Member name cannot be empty.\n";
//            continue;
//        }
//        break;
//    }
//
//    // Create and add
//    Member member(memberId, memberName);
//
//    // Your required call style:
//    // memberDict.addMember("M001", member);
//    // but since memberId is the key, use:
//    bool ok = memberDict.addMember(memberId, member);
//
//    if (ok) {
//        std::cout << "Member " << memberId << " created successfully.\n";
//    }
//    else {
//        std::cout << "Failed to create member (duplicate ID or other issue).\n";
//    }
//
//    std::cout << "=========================\n";
//}


//
//void memberBorrowMenu(GameDictionary& gameDict,
//                      Member& selectedMember,
//                      MasterHistoryLog& historyList) {
//    cout << "\n===== Borrow Game =====\n";
//
//    // Show all games first
//    gameDict.print();
//
//    while (true) {
//        cout << "\nEnter Game ID to borrow (or 0 to cancel): ";
//        string gameId;
//        cin >> gameId;
//
//        if (gameId == "0") {
//            cout << "Cancelled.\n";
//            return;
//        }
//
//        // Retrieve game (pointer)
//        BoardGame* game = gameDict.get(gameId);
//        if (game == nullptr) {
//            cout << "Game ID not found. Please try again.\n";
//            continue;
//        }
//
//        // Check if already borrowed
//        if (game->checkIsBorrowed()) {
//            cout << "⚠️ This game is already borrowed. Please choose another.\n";
//            continue;
//        }
//
//        // Borrow stage
//        string today = getCurrentDate();
//
//        // Member borrows (Member takes BoardGame&)
//        bool memberOk = selectedMember.borrowGame(*game, today);
//
//        // Game records borrow
//        bool gameOk = game->borrowGame(selectedMember.getID(),
//                                       selectedMember.getName(),
//                                       today);
//
//        if (!memberOk || !gameOk) {
//            cout << "Borrow failed unexpectedly.\n";
//            return;
//        }
//
//        // NEW: Add to master history log using your new method
//        bool logOk = historyList.add(*game, selectedMember, today);
//        if (!logOk) {
//            cout << "Borrowed successfully, but failed to log history.\n";
//            // Still treat as success from user perspective
//        }
//
//        cout << "Borrow successful!\n";
//        cout << selectedMember.getName() << " borrowed " << gameId
//             << " on " << today << "\n";
//
//        return;
//    }
//}
//void memberReturnMenu(GameDictionary& gameDict,
//                      Member& selectedMember,
//                      MasterHistoryLog& historyList) {
//    cout << "\n===== Return Game =====\n";
//
//    // 1) Show unreturned games from this member
//    selectedMember.printUnreturnedGames();
//
//    // 2) Ask for game ID
//    while (true) {
//        cout << "\nEnter Game ID to return (or 0 to cancel): ";
//        string gameId;
//        cin >> gameId;
//
//        if (gameId == "0") {
//            cout << "Cancelled.\n";
//            return;
//        }
//
//        // 3) Retrieve game from dictionary
//        BoardGame* game = gameDict.get(gameId);
//
//        if (game == nullptr) {
//            cout << "Game ID not found. Please try again.\n";
//            continue;
//        }
//
//        // 4) Check if game is borrowed (overall)
//        if (!game->checkIsBorrowed()) {
//            cout << "This game is not currently borrowed (already returned).\n";
//            continue;
//        }
//
//        // 5) Return stage
//        string today = getCurrentDate();
//
//        // Member tries to return (checks if THIS member borrowed it)
//        bool memberOk = selectedMember.returnGame(*game, today);
//        if (!memberOk) {
//            cout << "Return failed: This game is not currently borrowed by you.\n";
//            continue; // let them try again
//        }
//
//        // Game updates return date
//        bool gameOk = game->returnGame(today);
//        if (!gameOk) {
//            cout << "Return failed unexpectedly (game state error).\n";
//            return;
//        }
//
//        // Update master history log
//        bool logOk = historyList.markReturned(today, gameId);
//        if (!logOk) {
//            cout << "Returned, but history record not found to update.\n";
//            // You can still treat it as success for user experience
//        }
//
//        cout << "Return successful!\n";
//        cout << "You returned Game " << gameId << " on " << today << "\n";
//        return;
//    }
//}
//void DisplayBorrowedGames(Member& selectedMember) {}
//void adminMenu(GameDictionary& gameDict, MemberDictionary& memberDict, MasterHistoryLog& historyList) {
//    int choice;
//
//    while (true) {
//        std::cout << "\n========= Admin Menu =========\n";
//        std::cout << "1) Add Game\n";
//        std::cout << "2) Delete Game\n";
//        std::cout << "3) View All Games\n";
//        std::cout << "4) Create Member\n";
//        std::cout << "5) Summary of All Borrowing Records\n";
//        std::cout << "6) Summary of Unreturned Games\n";
//        std::cout << "0) Logout\n";
//        std::cout << "Choose: ";
//
//        if (!(std::cin >> choice)) {
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            std::cout << "Invalid input.\n";
//            continue;
//        }
//
//        if (choice == 1) {
//            createAndAddGameMenu(gameDict);
//        } else if (choice == 2) {
//            deleteGameMenu(gameDict);
//        } else if (choice == 3) {
//            gameDict.print();
//        } else if (choice == 4) {
//            createMemberMenu(memberDict);
//        } else if (choice == 5) {
//            historyList.printAll();
//        } else if (choice == 6) {
//            historyList.printUnreturned();
//        } else if (choice == 0) {
//            std::cout << "Logging out...\n";
//            break;
//        } else {
//            std::cout << "Invalid option.\n";
//        }
//    }
//}
//
//void memberMenu(GameDictionary& gameDict,
//                MemberDictionary& memberDict,
//                MasterHistoryLog& historyList) {
//    cout << "\n======= Member Login =======\n";
//    cout << "Enter your Member ID (e.g., M001) (or 0 to cancel): ";
//
//    string memberId;
//    cin >> memberId;
//
//    if (memberId == "0") {
//        cout << "Cancelled.\n";
//        return;
//    }
//
//    Member* selectedMemberPtr = memberDict.getMember(memberId);
//    if (selectedMemberPtr == nullptr) {
//        cout << "Member ID not found.\n";
//        return;
//    }
//
//    Member& selectedMember = *selectedMemberPtr;
//
//    cout << "Welcome, " << selectedMember.getName()
//         << " (" << selectedMember.getID() << ")\n";
//
//    int choice;
//
//    while (true) {
//        cout << "\n========= Member Menu =========\n";
//        cout << "1) Borrow Game\n";
//        cout << "2) Return Game\n";
//        cout << "3) Summary of Games Borrowed\n";
//        cout << "0) Logout\n";
//        cout << "Choose: ";
//
//        if (!(cin >> choice)) {
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cout << "Invalid input.\n";
//            continue;
//        }
//
//        if (choice == 1) {
//            memberBorrowMenu(gameDict, selectedMember, historyList);
//        } else if (choice == 2) {
//            memberReturnMenu(gameDict, selectedMember, historyList);
//        }else if (choice == 3){
//            selectedMember.printBorrowHistory();
//        } else if (choice == 0) {
//            cout << "Logging out...\n";
//            return;
//        } else {
//            cout << "Invalid option.\n";
//        }
//    }
//}
//
//void mainMenu(GameDictionary& gameDict, MemberDictionary& memberDict, MasterHistoryLog& historyList) {
//    int role;
//
//    while (true) {
//        cout << "\n======= Login =======\n";
//        cout << "1) Admin\n";
//        cout << "2) Member\n";
//        cout << "0) Exit\n";
//        cout << "Choose: ";
//
//        if (!(cin >> role)) {
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cout << "Invalid input.\n";
//            continue;
//        }
//
//        if (role == 1) {
//            adminMenu(gameDict, memberDict,historyList);
//        } else if (role == 2) {
//            memberMenu(gameDict, memberDict, historyList);
//        } else if (role == 0) {
//            cout << "Bye!\n";
//            break;
//        } else {
//            cout << "Invalid option.\n";
//        }
//    }
//}