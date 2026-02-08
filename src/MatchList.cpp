#include "MatchList.h"
#include "List.h"

#include <istream>
#include <sstream>
#include <string>
#include<iomanip>
#include <ios>
#include <iostream>

MatchList::MatchList() {}

bool MatchList::add(std::string loggerID, std::string gameID, int matchDuration, std::string playerIDs, std::string winnerID) {
    MatchLog log;

    log.loggerID = loggerID;
    log.gameID = gameID;
    log.matchDuration = matchDuration;
    log.winnerID = winnerID;

    std::stringstream ss(playerIDs);
    std::string individualID;

    while (std::getline(ss >> std::ws, individualID, ',')) {
        log.playerIDs.add(individualID);
    }

    return List<MatchLog>::add(log);
}

void MatchList::print() {
    if (isEmpty()) {
        std::cout << "No reviews found." << "\n";
        return;
    }

    Node* temp = firstNode;
    while (temp != nullptr) {
        if (!temp) break; //Static analyzer warns if this ain't here
        MatchLog* match = &temp->item;

        std::string playerIDs = "";

        auto tempPlayerID = match->playerIDs.get();
        int iteration = 0;
        while (tempPlayerID != nullptr) {
            // Add a comma before each ID after the first ID
            if (iteration > 0) {
                playerIDs += ",";
            }

            playerIDs += tempPlayerID->item;
            iteration++;
            tempPlayerID = tempPlayerID->next;
        }

        std::cout << std::left << std::setw(8) << match->loggerID
            << " | " << std::setw(8) << match->gameID
            << " | " << std::setw(15) << match->matchDate
            << " | " << std::setw(15) << match->matchDuration
            << " | " << std::setw(15) << iteration
            << " | " << std::setw(15) << playerIDs
            << " | " << std::setw(8) << match->winnerID
            << "\n";

        temp = temp->next;
    }
}