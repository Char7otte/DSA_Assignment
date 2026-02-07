#include "FileUtilities.h"

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

    inputFile.close();
    gameDict.print();

    std::cout << "\n";
    std::cout << "File read successfully." << "\n" << "\n";
}

//void readGameFile(const std::string& fileName, GameDictionary& gameDict) {
//    std::cout << "Reading " << fileName << "\n";
//
//    BoardGame* b1 = new BoardGame("G001", "12 Days", 3, 5, 15, 15, 2011);
//    BoardGame* b2 = new BoardGame("G002","Rat - a - Tat Cat", 2, 6, 10, 10, 1995);
//    BoardGame* b3 = new BoardGame("G003", "Yedo", 2, 5, 180, 120, 2012);
//
//    gameDict.add("G001", b1);
//    gameDict.add("G002", b2);
//    gameDict.add("G003", b3);
//
//    gameDict.print();
//
//    std::cout << "\n";
//        std::cout << "File read successfully." << "\n" << "\n";
//}

void readMemberFile(const std::string& fileName, MemberDictionary& memberDict) {
    std::cout << "Reading " << fileName << "\n";

    Member* m1 = new Member("M001",  "Alice Smith", true);
    Member* m2 = new Member("M002", "Bob Jones", false);
    Member* m3 = new Member("M003", "Charlie Day");
    memberDict.add("M001", m1);
    memberDict.add("M002", m2);
    memberDict.add("M003", m3);

    memberDict.print();

    std::cout << "\n";
    std::cout << "File read successfully." << "\n" << "\n";
}