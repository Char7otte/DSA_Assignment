#include <iostream>
#include <fstream>
#include<string>
#include<sstream>
#include<iomanip>

#include "List.h"
#include "BoardGame.h"
#include "member.h"

List readDataFile(std::string fileName);

int main()
{
    List boardGamesList = readDataFile("games.csv");
    return 0;
}

List readDataFile(std::string fileName) {
    List newList;
    std::cout << "Reading games.csv" << "\n";

    std::ifstream inputFile(fileName);
    std::string line, name, minPlayers, maxPlayers, minPlaytime, maxPlaytime, yearPublished;
    std::getline(inputFile, line);
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

        BoardGame newBoardGame(
            name,
            std::stoi(minPlayers),
            std::stoi(maxPlayers),
            std::stoi(minPlaytime),
            std::stoi(maxPlaytime),
            std::stoi(yearPublished)
        );

        newList.add(newBoardGame);

    }

    inputFile.close();
    newList.printAll();

    std::cout << "\n";
    std::cout << "File read successfully." << "\n";

    return newList;
}