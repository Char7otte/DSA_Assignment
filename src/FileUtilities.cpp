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

//void readGameFile(const std::string& fileName, GameDictionary& gameDict) {
//    std::cout << "Reading " << fileName << "\n";
//
//    std::ifstream inputFile(fileName);
//    std::string line, name, minPlayers, maxPlayers, minPlaytime, maxPlaytime, yearPublished;
//    std::getline(inputFile, line);
//    int iteration = 1;
//    while (std::getline(inputFile, line)) {
//        std::stringstream ss(line);
//
//        //In case the board game's name has a comma, quotes will be placed around the name.
//        if (ss.peek() == '"') {
//            ss >> std::quoted(name);
//            if (ss.peek() == ',') ss.ignore();
//        }
//        else {
//            std::getline(ss, name, ',');
//        }
//        std::getline(ss, minPlayers, ',');
//        std::getline(ss, maxPlayers, ',');
//        std::getline(ss, maxPlaytime, ',');
//        std::getline(ss, minPlaytime, ',');
//        std::getline(ss, yearPublished, ',');
//
//        std::string id = "G" + std::to_string(iteration);
//
//        BoardGame* newBoardGame = new BoardGame(
//            id,
//            name,
//            std::stoi(minPlayers),
//            std::stoi(maxPlayers),
//            std::stoi(minPlaytime),
//            std::stoi(maxPlaytime),
//            std::stoi(yearPublished)
//        );
//
//        gameDict.add(id, newBoardGame);
//        iteration++;
//    }
//
//    gameDict.setLargestID(iteration);
//
//    inputFile.close();
//    gameDict.print();
//
//    std::cout << "\n";
//    std::cout << "File read successfully." << "\n" << "\n";
//}

void readGameFile(const std::string& fileName, GameDictionary& gameDict) {
    std::cout << "Reading " << fileName << "\n";

    BoardGame* b1 = new BoardGame("G1", "12 Days", 3, 5, 15, 15, 2011);
    BoardGame* b2 = new BoardGame("G2", "Rat - a - Tat Cat", 2, 6, 10, 10, 1995);
    BoardGame* b3 = new BoardGame("G3", "Yedo", 2, 5, 180, 120, 2012);

    gameDict.add("G1", b1);
    gameDict.add("G2", b2);
    gameDict.add("G3", b3);

    gameDict.setLargestID(3);
    gameDict.print();

    std::cout << "\n";
    std::cout << "File read successfully." << "\n" << "\n";
}

void readMemberFile(const std::string& fileName, MemberDictionary& memberDict) {
    std::cout << "Reading " << fileName << "\n";

    Member* m1 = new Member("M1", "Alice Smith", true);
    Member* m2 = new Member("M2", "Bob Jones", false);
    Member* m3 = new Member("M3", "Charlie Day");
    Member* m4 = new Member("M4", "David Green");

    
    memberDict.add("M1", m1);
    memberDict.add("M2", m2);
    memberDict.add("M3", m3);
    memberDict.add("M4", m4);

    memberDict.setLargestID(4);
    memberDict.print();

    std::cout << "\n";
    std::cout << "File read successfully." << "\n" << "\n";
}

void addSampleReviews_G1(GameDictionary& games) {
    BoardGame* game = nullptr;
    games.get("G1", game);

    if (game == nullptr) {
        std::cout << "Game G1 not found.\n";
        return;
    }

    // Allowed member IDs
    const std::string memberIds[3] = { "M2", "M3", "M4" };

    // Sample ratings & bodies
    const int ratings[10] = { 5, 4, 3, 5, 2, 1, 4, 5, 3, 4 };
    const std::string bodies[10] = {
        "Excellent game, highly recommended",
        "Very fun with friends",
        "Decent but could be better",
        "Amazing replay value",
        "Not bad but a bit slow",
        "Did not enjoy it much",
        "Good strategy elements",
        "One of my favourites",
        "Okay for casual play",
        "Solid overall experience"
    };

    for (int i = 0; i < 10; i++) {
        // Rotate members: M2 ¡ú M3 ¡ú M4 ¡ú M2 ...
        std::string reviewerId = memberIds[i % 3];

        bool success = game->addReview(
            reviewerId,
            bodies[i],
            ratings[i]
        );

        if (!success) {
            std::cout << "Failed to add review " << (i + 1) << "\n";
        }
    }
    std::cout << "10 sample reviews added to G1 (M2, M3, M4).\n";
}