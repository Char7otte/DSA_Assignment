#include "GameDictionary.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

bool loadGamesFromCSV(const string& filename, GameDictionary& dict) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Failed to open file: " << filename << endl;
        return false;
    }

    string line;
    int nextGameId = 1;

    // skip header line
    getline(file, line);

    while (getline(file, line)) {
        if (line.empty()) continue;

        string token;
        stringstream ss(line);

        GameInfo game;
        game.id = nextGameId++;   // 🔑 auto-generated ID

        // name
        getline(ss, game.name, ',');

        // minplayers
        getline(ss, token, ',');
        game.minPlayers = stoi(token);

        // maxplayers
        getline(ss, token, ',');
        game.maxPlayers = stoi(token);

        // minplaytime
        getline(ss, token, ',');
        game.minPlayTime = stoi(token);

        // maxplaytime
        getline(ss, token, ',');
        game.maxPlayTime = stoi(token);

        // yearpublished
        getline(ss, token, ',');
        game.yearPublished = stoi(token);

        game.isBorrowed = false;
        game.borrowedBy = "";
        game.borrowDate = "";

        // use ID as hash key
        string key = to_string(game.id);
        dict.add(key, game);
    }

    file.close();
    return true;
}


int main(){
    GameDictionary games;
    if (loadGamesFromCSV("games.csv", games)) {
        cout << "Games loaded successfully!" << endl;
        games.print();
    }

}

