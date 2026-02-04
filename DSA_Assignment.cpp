
#include <fstream>
#include <sstream>
#include <string>


// struct Game {
//     string id;
//     string name;
//     int minPlayers;
//     int maxPlayers;
//     int maxPlayTime;
//     int minPlayTime;
//     int yearPublished;
// };
//
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
#include "GameDictionary.h"
#include "BoardGame.h"

using namespace std;
#include "Member.h"
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <limits> // for numeric_limits

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
    cout << "Enter Game ID to delete (e.g., G001): ";

    string id;
    cin >> id;

    bool deleted = gameDict.remove(id);

    if (deleted) {
        cout << "Game " << id << " deleted successfully.\n";
    } else {
        cout << "❌ Game ID " << id << " not found. Nothing deleted.\n";
    }

    cout << "=============================\n";
}

void adminMenu(GameDictionary& gameDict) {
    int choice;

    while (true) {
        cout << "\n========= Admin Menu =========\n";
        cout << "1) Add Game\n";
        cout << "2) Delete Game\n";
        cout << "3) View All Games\n";
        cout << "0) Logout\n";
        cout << "Choose: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 1) {
            createAndAddGameMenu(gameDict);   // ✅ your previous function
        } else if (choice == 2) {
            deleteGameMenu(gameDict);
        } else if (choice == 3) {
            gameDict.print();
        } else if (choice == 0) {
            cout << "Logging out...\n";
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }
}

void mainMenu(GameDictionary& gameDict) {
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
            adminMenu(gameDict);
        } else if (role == 2) {
            cout << "Member menu not implemented yet.\n";
        } else if (role == 0) {
            cout << "Bye!\n";
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }
}

int main() {

    // Create dictionary
    GameDictionary gameDict;
    Member member("M001","Alice");

    // Create BoardGame objects
    BoardGame g1("G001", "Catan", 3, 4, 60, 120, 1995);
    BoardGame g2("G002", "Monopoly", 2, 6, 60, 180, 1935);
    BoardGame g3("G003", "Chess", 2, 2, 10, 60, 1975);

    // Add games (key = game ID as string)
    gameDict.add("G001", g1);
    gameDict.add("G002", g2);
    gameDict.add("G003", g3);
    // gameDict.print();
    mainMenu(gameDict);



    return 0;
};
