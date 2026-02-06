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

        BoardGame* newBoardGame = new BoardGame(
            std::to_string(iteration),
            name,
            std::stoi(minPlayers),
            std::stoi(maxPlayers),
            std::stoi(minPlaytime),
            std::stoi(maxPlaytime),
            std::stoi(yearPublished)
        );

        gameDict.add(std::to_string(iteration), newBoardGame);
        iteration++;
    }

    inputFile.close();
    gameDict.print();

    std::cout << "\n";
    std::cout << "File read successfully." << "\n";
}

void readMemberFile(const std::string& fileName, MemberDictionary& memberDict) {
    std::cout << "Reading " << fileName << "\n";

    Member* m1 = new Member("M001", "board_king99", "pass123", "Alice Smith");
    Member* m2 = new Member("M002", "dice_roller", "secret77", "Bob Jones");
    Member* m3 = new Member("M003", "meeple_queen", "p@ssword", "Charlie Day");
    memberDict.add("M001", m1);
    memberDict.add("M002", m2);
    memberDict.add("M003", m3);

    memberDict.print();

    std::cout << "\n";
    std::cout << "File read successfully." << "\n";
}