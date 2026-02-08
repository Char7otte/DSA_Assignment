#include "FileUtilities.h"
#include "BoardGame.h"
#include "GameDictionary.h"
#include "Member.h"
#include "MemberDictionary.h"

#include<string>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>

void readGameFile(const std::string& fileName, GameDictionary& gameDict) {
    std::cout << "Reading " << fileName << "\n";

    std::ifstream inputFile(fileName);
    std::string line, name, minPlayers, maxPlayers, minPlaytime, maxPlaytime, yearPublished;
    std::getline(inputFile, line);
    int iteration = 1;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);

        //In case the board game's name has a comma, quotes will be placed around the name.
        if (ss.peek() == '"') {
            ss >> std::quoted(name);
            if (ss.peek() == ',') ss.ignore();
        }
        else {
            std::getline(ss, name, ',');
        }
        std::getline(ss, minPlayers, ',');
        std::getline(ss, maxPlayers, ',');
        std::getline(ss, maxPlaytime, ',');
        std::getline(ss, minPlaytime, ',');
        std::getline(ss, yearPublished, ',');

        std::string id = "G" + std::to_string(iteration);

        BoardGame* newBoardGame = new BoardGame(
            id,
            name,
            std::stoi(minPlayers),
            std::stoi(maxPlayers),
            std::stoi(minPlaytime),
            std::stoi(maxPlaytime),
            std::stoi(yearPublished)
        );

        gameDict.add(id, newBoardGame);
        iteration++;
    }

    gameDict.setLargestID(iteration);

    inputFile.close();
    gameDict.print();

    std::cout << "\n";
    std::cout << "File read successfully." << "\n" << "\n";
}

//void readGameFile(const std::string& fileName, GameDictionary& gameDict) {
//    std::cout << "Reading " << fileName << "\n";
//
//    BoardGame* b1 = new BoardGame("G1", "12 Days", 3, 5, 15, 15, 2011);
//    BoardGame* b2 = new BoardGame("G2", "Rat - a - Tat Cat", 2, 6, 10, 10, 1995);
//    BoardGame* b3 = new BoardGame("G3", "Yedo", 2, 5, 180, 120, 2012);
//
//    gameDict.add("G1", b1);
//    gameDict.add("G2", b2);
//    gameDict.add("G3", b3);
//
//    gameDict.setLargestID(3);
//    gameDict.print();
//
//    std::cout << "\n";
//    std::cout << "File read successfully." << "\n" << "\n";
//}

void readMemberFile(const std::string& fileName, MemberDictionary& memberDict) {
    std::cout << "Reading " << fileName << "\n";

    Member* m1 = new Member("M1", "Alice Smith", true);
    Member* m2 = new Member("M2", "Bob Jones", false);
    Member* m3 = new Member("M3", "Charlie Day");
    memberDict.add("M1", m1);
    memberDict.add("M2", m2);
    memberDict.add("M3", m3);

    memberDict.setLargestID(3);
    memberDict.print();

    std::cout << "\n";
    std::cout << "File read successfully." << "\n" << "\n";
}