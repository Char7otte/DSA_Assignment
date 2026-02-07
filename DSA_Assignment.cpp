
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
#include "AdminSystem.h"
#include "MemberSystem.h"

using namespace std;





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
