
// int main() {
//     ifstream file("games.csv");  // your CSV file
//     vector<Game> games;
//
//     if (!file.is_open()) {
//         cout << "Failed to open file\n";
//         return 1;
//     }
//
//     string line;
//
//     // Skip header line
//     getline(file, line);
//
//     while (getline(file, line)) {
//         stringstream ss(line);
//         string field;
//         Game game;
//
//         getline(ss, game.id, ',');
//         getline(ss, game.name, ',');
//
//         getline(ss, field, ',');
//         game.minPlayers = stoi(field);
//
//         getline(ss, field, ',');
//         game.maxPlayers = stoi(field);
//
//         getline(ss, field, ',');
//         game.maxPlayTime = stoi(field);
//
//         getline(ss, field, ',');
//         game.minPlayTime = stoi(field);
//
//         getline(ss, field, ',');
//         game.yearPublished = stoi(field);
//
//         games.push_back(game);
//     }
//
//     file.close();
//
//     // Test print
//     for (const Game& g : games) {
//         cout << g.id << " | "
//              << g.name << " | "
//              << g.minPlayers << "-" << g.maxPlayers
//              << " | " << g.yearPublished << endl;
//     }
//
//     return 0;
// }
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <limits> // for numeric_limits
#include "Member.h"
#include "GameDictionary.h"
#include "BoardGame.h"
#include "MasterHistoryLog.h"
#include "MemeberDictionary.h"
#include "List.h"

using namespace std;

std::string getCurrentDate() {
    // 1. Get the current system time
    auto now = std::chrono::system_clock::now();

    // 2. Convert to a time_t object (standard C time)
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // 3. Convert to local time structure
    std::tm* localTime = std::localtime(&currentTime);

    // 4. Use stringstream to format it (YYYY-MM-DD)
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d");

    return ss.str();
}

void createAndAddGameMenu(GameDictionary& gameDict) {
    cout << "\n===== Add New Board Game =====\n";
    string id, name;
    int minPlayers, maxPlayers, minPlayTime, maxPlayTime, yearPublished;

    // --- Input: Game ID ---
    while (true) {
        cout << "Enter Game ID (e.g., G004): ";
        cin >> id;
        if (id.empty()) {
            cout << "Game ID cannot be empty.\n";
            continue;
        }
        if (gameDict.contains(id)) {
            cout << "This Game ID already exists. Please enter a different ID.\n";
            continue;
        }
        break;
    }

    // clear newline before getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // --- Input: Game Name ---
    while (true) {
        cout << "Enter Game Name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Game name cannot be empty.\n";
            continue;
        }
        break;
    }

    // --- Numeric inputs with basic validation ---
    auto readInt = [](const string& prompt) {
        int x;
        while (true) {
            cout << prompt;
            if (cin >> x) return x;

            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    };

    minPlayers = readInt("Enter Min Players: ");
    maxPlayers = readInt("Enter Max Players: ");
    while (maxPlayers < minPlayers) {
        cout << "Max Players cannot be less than Min Players.\n";
        maxPlayers = readInt("Enter Max Players again: ");
    }

    minPlayTime = readInt("Enter Min Play Time (minutes): ");
    maxPlayTime = readInt("Enter Max Play Time (minutes): ");
    while (maxPlayTime < minPlayTime) {
        cout << "Max Play Time cannot be less than Min Play Time.\n";
        maxPlayTime = readInt("Enter Max Play Time again: ");
    }

    yearPublished = readInt("Enter Year Published: ");

    // --- Create and add ---
    BoardGame newGame(id, name, minPlayers, maxPlayers, minPlayTime, maxPlayTime, yearPublished);

    if (gameDict.add(id, newGame)) {
        cout << "\n Game added successfully!\n";
    } else {
        cout << "\n Failed to add game (duplicate key or other issue).\n";
    }
    cout << "==============================\n";
}

void deleteGameMenu(GameDictionary& gameDict) {
    cout << "\n===== Delete Board Game =====\n";
    gameDict.print();
    cout << "Enter Game ID to delete (e.g., G001): ";

    string id;
    cin >> id;
    BoardGame* game = gameDict.get(id);
    if (game == nullptr) {
        cout << "Game ID " << id << " not found. Nothing deleted.\n";

    }else {
        if (game->checkIsBorrowed()) {
            cout << "Game: " << game->getName() << " has been borrowed by other member.\n";
        }else {
            gameDict.remove(id);
            cout << "Game deleted successfully!\n";
        }
    }
    cout << "=============================\n";
}

void createMemberMenu(MemberDictionary& memberDict) {
    std::cout << "\n===== Create Member =====\n";

    std::string memberId;
    std::string memberName;

    // Member ID (no spaces)
    while (true) {
        std::cout << "Enter Member ID (e.g., M001): ";
        std::cin >> memberId;

        if (memberId.empty()) {
            std::cout << "Member ID cannot be empty.\n";
            continue;
        }

        // If you have containsMember(), use it:
        if (memberDict.containsMember(memberId)) {
            std::cout << "This Member ID already exists.\n";
            continue;
        }

        break;
    }

    // clear newline before getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Member name (can contain spaces)
    while (true) {
        std::cout << "Enter Member Name: ";
        std::getline(std::cin, memberName);

        if (memberName.empty()) {
            std::cout << "Member name cannot be empty.\n";
            continue;
        }
        break;
    }

    // Create and add
    Member member(memberId, memberName);

    // Your required call style:
    // memberDict.addMember("M001", member);
    // but since memberId is the key, use:
    bool ok = memberDict.addMember(memberId, member);

    if (ok) {
        std::cout << "Member " << memberId << " created successfully.\n";
    } else {
        std::cout << "Failed to create member (duplicate ID or other issue).\n";
    }

    std::cout << "=========================\n";
}

void memberBorrowMenu(GameDictionary& gameDict, Member& selectedMember, MasterHistoryLog& historyList) {
    cout << "\n===== Borrow Game =====\n";

    // Show all games first
    gameDict.print();

    while (true) {
        cout << "\nEnter Game ID to borrow (or 0 to cancel): ";
        string gameId;
        cin >> gameId;

        if (gameId == "0") {
            cout << "Cancelled.\n";
            return;
        }

        // Retrieve game (pointer)
        BoardGame* game = gameDict.get(gameId);
        if (game == nullptr) {
            cout << "Game ID not found. Please try again.\n";
            continue;
        }

        // Check if already borrowed
        if (game->checkIsBorrowed()) {
            cout << "⚠️ This game is already borrowed. Please choose another.\n";
            continue;
        }

        string today = getCurrentDate();

        // ✅ Member borrows (Member will call game.borrowGame internally)
        bool memberOk = selectedMember.borrowGame(*game, today);

        if (!memberOk) {
            cout << "Borrow failed unexpectedly.\n";
            return;
        }

        // ✅ Log history AFTER successful borrow
        bool logOk = historyList.add(*game, selectedMember, today);
        if (!logOk) {
            cout << "Borrowed successfully, but failed to log history.\n";
        }

        cout << "Borrow successful!\n";
        cout << selectedMember.getName() << " borrowed " << gameId
             << " on " << today << "\n";
        return;
    }
}

void memberReturnMenu(GameDictionary& gameDict, Member& selectedMember, MasterHistoryLog& historyList) {
    cout << "\n===== Return Game =====\n";

    // 1) Show unreturned games from this member
    selectedMember.printUnreturnedGames();

    while (true) {
        cout << "\nEnter Game ID to return (or 0 to cancel): ";
        string gameId;
        cin >> gameId;

        if (gameId == "0") {
            cout << "Cancelled.\n";
            return;
        }

        // 2) Retrieve game from dictionary
        BoardGame* game = gameDict.get(gameId);
        if (game == nullptr) {
            cout << "Game ID not found. Please try again.\n";
            continue;
        }

        // 3) Check global game status first (fast feedback)
        if (!game->checkIsBorrowed()) {
            cout << "This game is not currently borrowed (already returned).\n";
            continue;
        }

        string today = getCurrentDate();

        // ✅ Member returns (Member will call game.returnGame internally)
        bool memberOk = selectedMember.returnGame(*game, today);

        if (!memberOk) {
            cout << "Return failed: This game is not currently borrowed by you.\n";
            continue;
        }

        // ✅ Update master history log
        bool logOk = historyList.markReturned(today, gameId);
        if (!logOk) {
            cout << "Returned, but history record not found to update.\n";
        }

        cout << "Return successful!\n";
        cout << "You returned Game " << gameId << " on " << today << "\n";
        return;
    }
}

void memberAddReviewMenu(GameDictionary& gameDict, Member& selectedMember) {
    cout << "\n===== Add Review =====\n";

    // 1) Show all games
    gameDict.print();

    while (true) {
        cout << "\nEnter Game ID to review (or 0 to cancel): ";
        string gameId;
        cin >> gameId;

        if (gameId == "0") {
            cout << "Cancelled.\n";
            return;
        }

        // 2) Retrieve game
        BoardGame* game = gameDict.get(gameId);
        if (game == nullptr) {
            cout << "Game ID not found. Please try again.\n";
            continue;
        }

        // 3) Get rating (1-10)
        int rating;
        while (true) {
            cout << "Enter rating (1-10): ";
            cin >> rating;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            if (rating < 1 || rating > 10) {
                cout << "Rating must be between 1 and 10.\n";
                continue;
            }

            // clear newline before getline for review text
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        // 4) Get review text
        string reviewText;
        while (true) {
            cout << "Enter review text: ";
            getline(cin, reviewText);

            if (reviewText.empty()) {
                cout << "Review text cannot be empty.\n";
                continue;
            }
            break;
        }

        // 5) Add review into game reviewHistory
        string today = getCurrentDate();

        bool ok = game->addReview(
            selectedMember.getID(),
            selectedMember.getName(),
            today,
            reviewText,
            rating
        );

        if (!ok) {
            cout << "Failed to add review.\n";
            return;
        }

        cout << "Review added successfully!\n";
        cout << selectedMember.getName() << " reviewed " << game->getName()
             << " (" << gameId << ") on " << today
             << " with rating " << rating << "/10.\n";

        return;
    }
}

void memberViewReviewMenu(GameDictionary& gameDict) {
    cout << "\n===== View Game Reviews =====\n";

    // 1) Show all games
    gameDict.print();

    while (true) {
        cout << "\nEnter Game ID to view reviews (or 0 to cancel): ";
        string gameId;
        cin >> gameId;

        if (gameId == "0") {
            cout << "Cancelled.\n";
            return;
        }

        // 2) Retrieve game
        BoardGame* game = gameDict.get(gameId);
        if (game == nullptr) {
            cout << "Game ID not found. Please try again.\n";
            continue;
        }

        // 3) Display reviews
        game->displayReviews();
        return;
    }
}

void adminMenu(GameDictionary& gameDict, MemberDictionary& memberDict, MasterHistoryLog& historyList) {
    int choice;

    while (true) {
        std::cout << "\n========= Admin Menu =========\n";
        std::cout << "1) Add Game\n";
        std::cout << "2) Delete Game\n";
        std::cout << "3) View All Games\n";
        std::cout << "4) Create Member\n";
        std::cout << "5) Summary of All Borrowing Records\n";
        std::cout << "6) Summary of Unreturned Games\n";
        std::cout << "0) Logout\n";
        std::cout << "Choose: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        if (choice == 1) {
            createAndAddGameMenu(gameDict);
        } else if (choice == 2) {
            deleteGameMenu(gameDict);
        } else if (choice == 3) {
            gameDict.print();
        } else if (choice == 4) {
            createMemberMenu(memberDict);
        } else if (choice == 5) {
            historyList.printAll();
        } else if (choice == 6) {
            historyList.printUnreturned();
        } else if (choice == 0) {
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}

void memberMenu(GameDictionary& gameDict,
                MemberDictionary& memberDict,
                MasterHistoryLog& historyList) {
    cout << "\n======= Member Login =======\n";
    cout << "Enter your Member ID (e.g., M001) (or 0 to cancel): ";

    string memberId;
    cin >> memberId;

    if (memberId == "0") {
        cout << "Cancelled.\n";
        return;
    }

    Member* selectedMemberPtr = memberDict.getMember(memberId);
    if (selectedMemberPtr == nullptr) {
        cout << "Member ID not found.\n";
        return;
    }

    Member& selectedMember = *selectedMemberPtr;

    cout << "Welcome, " << selectedMember.getName()
         << " (" << selectedMember.getID() << ")\n";

    int choice;

    while (true) {
        cout << "\n========= Member Menu =========\n";
        cout << "1) Borrow Game\n";
        cout << "2) Return Game\n";
        cout << "3) Summary of Games Borrowed\n";
        cout << "4) Add Review\n";          // ✅ NEW
        cout << "5) View Game Reviews\n";   // ✅ NEW
        cout << "0) Logout\n";
        cout << "Choose: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 1) {
            memberBorrowMenu(gameDict, selectedMember, historyList);
        }
        else if (choice == 2) {
            memberReturnMenu(gameDict, selectedMember, historyList);
        }
        else if (choice == 3) {
            selectedMember.printBorrowHistory();
        }
        else if (choice == 4) {
            memberAddReviewMenu(gameDict, selectedMember);   // ✅ NEW
        }
        else if (choice == 5) {
            memberViewReviewMenu(gameDict);                  // ✅ NEW
        }
        else if (choice == 0) {
            cout << "Logging out...\n";
            return;
        }
        else {
            cout << "Invalid option.\n";
        }
    }
}

int main() {

    GameDictionary gameDict;
    MemberDictionary memberDict;
    MasterHistoryLog historyList;

    // Create BoardGame objects
    BoardGame g1("G001", "Catan", 3, 4, 60, 120, 1995);
    BoardGame g2("G002", "Monopoly", 2, 6, 60, 180, 1935);
    BoardGame g3("G003", "Chess", 2, 2, 10, 60, 1975);
    gameDict.add("G001", g1);
    gameDict.add("G002", g2);
    gameDict.add("G003", g3);

    Member member("M001", "John");
    Member member2("M002", "Jane");
    Member member3("M003", "Bob");
    memberDict.addMember("M001",member);
    memberDict.addMember("M002",member2);
    memberDict.addMember("M003",member3);

    int role;

    while (true) {
        cout << "\n======= Login =======\n";
        cout << "1) Admin\n";
        cout << "2) Member\n";
        cout << "0) Exit\n";
        cout << "Choose: ";

        if (!(cin >> role)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (role == 1) {
            adminMenu(gameDict, memberDict,historyList);
        } else if (role == 2) {
            memberMenu(gameDict, memberDict, historyList);
        } else if (role == 0) {
            cout << "Bye!\n";
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
};
