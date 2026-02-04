// #include "GameDictionary.h"
// #include <fstream>
// #include <sstream>
// #include <string>
// #include <iostream>
// #include <algorithm>
// #include <cctype>
// #include <vector>
// #include <climits>
// #ifdef _WIN32
// #include <windows.h>
// #endif
// using namespace std;
//
// static string getExecutableDir() {
// #ifdef _WIN32
//     char path[MAX_PATH];
//     DWORD len = GetModuleFileNameA(NULL, path, MAX_PATH);
//     if (len == 0 || len == MAX_PATH) return string();
//     string p(path, len);
//     size_t pos = p.find_last_of("/\\");
//     if (pos != string::npos) return p.substr(0, pos);
//     return string();
// #else
//     return string();
// #endif
// }
//
// static string joinPath(const string &a, const string &b) {
//     if (a.empty()) return b;
//     char sep = '\\';
//     if (!a.empty() && (a.back() == '/' || a.back() == '\\')) return a + b;
//     return a + sep + b;
// }
//
// bool loadGamesFromCSV(const string& filename, GameDictionary& dict) {
//     vector<string> candidates;
//     // 1) as provided (working directory)
//     candidates.push_back(filename);
// #ifdef BINARY_DIR
//     candidates.push_back(joinPath(BINARY_DIR, filename));
// #endif
// #ifdef _WIN32
//     {
//         string exeDir = getExecutableDir();
//         if (!exeDir.empty()) candidates.push_back(joinPath(exeDir, filename));
//     }
// #endif
// #ifdef SOURCE_DIR
//     candidates.push_back(joinPath(SOURCE_DIR, filename));
// #endif
//
//     ifstream file;
//     string openedPath;
//     for (const auto &p : candidates) {
//         file.clear();
//         file.open(p);
//         if (file.is_open()) { openedPath = p; break; }
//     }
//     if (!file.is_open()) {
//         cout << "Failed to open file: " << filename << "\nTried:" << endl;
//         for (const auto &p : candidates) cout << "  - " << p << endl;
//         return false;
//     } else {
//         cout << "Opening CSV: " << openedPath << endl;
//     }
//
//     string line;
//     int nextGameId = 1;
//
//     // skip header line
//     getline(file, line);
//
//     while (getline(file, line)) {
//         if (line.empty()) continue;
//
//         auto ltrim = [](string &s){ s.erase(s.begin(), find_if(s.begin(), s.end(), [](unsigned char ch){ return !isspace(ch); })); };
//         auto rtrim = [](string &s){ s.erase(find_if(s.rbegin(), s.rend(), [](unsigned char ch){ return !isspace(ch); }).base(), s.end()); };
//         auto trim = [&](string &s){ ltrim(s); rtrim(s); };
//         auto is_int = [&](const string &s){ if (s.empty()) return false; for(char c: s){ if (!(c=='-'||c=='+'||isdigit(static_cast<unsigned char>(c)))) return false; } return true; };
//
//         try {
//             GameInfo game;
//             game.id = nextGameId++;   // 🔑 auto-generated ID
//
//             string name;
//             string rest;
//
//             // Handle possible quoted name containing commas
//             if (!line.empty() && line[0] == '"') {
//                 size_t pos = 1;
//                 string collected;
//                 bool closed = false;
//                 while (pos < line.size()) {
//                     if (line[pos] == '"') {
//                         if (pos + 1 < line.size() && line[pos + 1] == '"') {
//                             collected.push_back('"');
//                             pos += 2; // skip escaped quote
//                         } else {
//                             closed = true;
//                             ++pos; // move past closing quote
//                             break;
//                         }
//                     } else {
//                         collected.push_back(line[pos++]);
//                     }
//                 }
//                 if (!closed) continue; // malformed
//                 // Next char should be comma
//                 if (pos < line.size() && line[pos] == ',') ++pos;
//                 name = collected;
//                 rest = (pos < line.size()) ? line.substr(pos) : string();
//             } else {
//                 // name up to first comma
//                 size_t comma = line.find(',');
//                 if (comma == string::npos) continue;
//                 name = line.substr(0, comma);
//                 rest = line.substr(comma + 1);
//             }
//
//             trim(name);
//             game.name = name;
//
//             // Now parse the remaining numeric fields according to CSV header:
//             // minplayers,maxplayers,maxplaytime,minplaytime,yearpublished
//             string token;
//             stringstream ss(rest);
//
//             // minplayers
//             if (!getline(ss, token, ',')) continue;
//             trim(token);
//             if (!is_int(token)) continue;
//             game.minPlayers = stoi(token);
//
//             // maxplayers
//             if (!getline(ss, token, ',')) continue;
//             trim(token);
//             if (!is_int(token)) continue;
//             game.maxPlayers = stoi(token);
//
//             // maxplaytime
//             if (!getline(ss, token, ',')) continue;
//             trim(token);
//             if (!is_int(token)) continue;
//             game.maxPlayTime = stoi(token);
//
//             // minplaytime
//             if (!getline(ss, token, ',')) continue;
//             trim(token);
//             if (!is_int(token)) continue;
//             game.minPlayTime = stoi(token);
//
//             // yearpublished
//             if (!getline(ss, token, ',')) continue;
//             trim(token);
//             if (!is_int(token)) continue;
//             game.yearPublished = stoi(token);
//
//             game.isBorrowed = false;
//             game.borrowedBy = "";
//             game.borrowDate = "";
//
//             // use ID as hash key
//             string key = to_string(game.id);
//             dict.add(key, game);
//         } catch (const exception&) {
//             // Skip malformed lines
//             continue;
//         }
//     }
//
//     file.close();
//     return true;
// }
//
// // -------- Interactive add helpers --------
// static string promptLine(const string &message) {
//     cout << message;
//     string s;
//     getline(cin, s);
//     return s;
// }
//
// static int promptInt(const string &message, int minVal = INT_MIN, int maxVal = INT_MAX) {
//     while (true) {
//         cout << message;
//         string s;
//         getline(cin, s);
//         string t = s;
//         // trim
//         t.erase(t.begin(), find_if(t.begin(), t.end(), [](unsigned char ch){ return !isspace(ch); }));
//         t.erase(find_if(t.rbegin(), t.rend(), [](unsigned char ch){ return !isspace(ch); }).base(), t.end());
//         bool ok = !t.empty();
//         for (char c : t) {
//             if (!(c=='-' || c=='+' || isdigit(static_cast<unsigned char>(c)))) { ok = false; break; }
//         }
//         if (ok) {
//             try {
//                 long val = stol(t);
//                 if (val < minVal || val > maxVal) {
//                     cout << "Please enter a number between " << minVal << " and " << maxVal << ".\n";
//                     continue;
//                 }
//                 return static_cast<int>(val);
//             } catch (...) { /* fallthrough to retry */ }
//         }
//         cout << "Invalid number, try again.\n";
//     }
// }
//
// static void addGameInteractive(GameDictionary &dict) {
//     cout << "\n=== Add a new game ===\n";
//     int id = promptInt("Enter game ID (integer): ");
//     string name = promptLine("Enter game name: ");
//     int minPlayers = promptInt("Enter min players: ", 1, 100);
//     int maxPlayers = promptInt("Enter max players: ", minPlayers, 200);
//     int minPlay = promptInt("Enter min play time (minutes): ", 0, 10000);
//     int maxPlay = promptInt("Enter max play time (minutes): ", minPlay, 10000);
//     int year = promptInt("Enter year published: ", 1800, 2100);
//
//     GameInfo game{};
//     game.id = id;
//     game.name = name;
//     game.minPlayers = minPlayers;
//     game.maxPlayers = maxPlayers;
//     game.minPlayTime = minPlay;
//     game.maxPlayTime = maxPlay;
//     game.yearPublished = year;
//     game.isBorrowed = false;
//     game.borrowedBy = "";
//     game.borrowDate = "";
//
//     string key = to_string(game.id);
//     if (dict.add(key, game)) {
//         cout << "Game added successfully with key=" << key << "\n";
//     } else {
//         cout << "A game with key=" << key << " already exists. Not added.\n";
//     }
// }
//
// int main(){
//     GameDictionary games;
//     if (loadGamesFromCSV("games.csv", games)) {
//         cout << "Games loaded successfully!" << endl;
//         games.print();
//     }
//
//     // Interactive add loop
//     while (true) {
//         cout << "\nDo you want to add a new game? (y/n): ";
//         string ans;
//         if (!getline(cin, ans)) break;
//         if (!ans.empty() && (ans[0]=='y' || ans[0]=='Y')) {
//             addGameInteractive(games);
//             cout << "\nCurrent dictionary state:\n";
//             games.print();
//         } else {
//             break;
//         }
//     }
//
//     return 0;
// }
//

#include <fstream>
#include <sstream>
#include <vector>
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

int main() {

    // Create dictionary
    GameDictionary gameDict;

    // Create BoardGame objects
    BoardGame g1("1", "Catan", 3, 4, 60, 120, 1995);
    BoardGame g2("2", "Monopoly", 2, 6, 60, 180, 1935);
    BoardGame g3("3", "Chess", 2, 2, 10, 60, 1975);

    // Add games (key = game ID as string)
    gameDict.add("G001", g1);
    gameDict.add("G002", g2);
    gameDict.add("G003", g3);
    gameDict.print();

    BoardGame* game = gameDict.get("G001");
    game->borrowGame("U001", "Alice", "2026-02-01");
    game->printInfo();
    game->checkIfBorrowedAndPrintLatest();
    game->returnGame("2026-02-05");
    game->borrowGame("U002", "Bob", "2026-02-01");
    game->checkIfBorrowedAndPrintLatest();
    game->printBurrowHistory();

    // cout << "=== All games in dictionary ===\n";
    // gameDict.print();
    //
    // // Retrieve game by ID and borrow it
    // cout << "\n=== Borrowing G002 ===\n";
    // BoardGame* game = gameDict.get("G002");
    //
    // if (game != nullptr) {
    //     game->borrowGame("U001", "Alice", "2026-02-01");
    //     game->checkIfBorrowedAndPrintLatest();
    // } else {
    //     cout << "Game G002 not found.\n";
    // }
    //
    // // Return the game
    // cout << "\n=== Returning G002 ===\n";
    // game = gameDict.get("G002");
    // if (game != nullptr) {
    //     game->returnGame("2026-02-05");
    // }
    //
    // // Check status again
    // cout << "\n=== Checking G002 status ===\n";
    // game = gameDict.get("G002");
    // if (game != nullptr) {
    //     game->checkIfBorrowedAndPrintLatest();
    //     game->printBurrowHistory();
    // }
    //
    // // Try retrieving a non-existing game
    // cout << "\n=== Retrieve non-existing game ===\n";
    // BoardGame* missing = gameDict.get("G999");
    //
    // if (missing == nullptr) {
    //     cout << "Game G999 not found.\n";
    // }

    return 0;
};
