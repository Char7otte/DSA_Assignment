#include "MatchList.h"
#include "List.h"

#include <istream>
#include <sstream>
#include <string>

MatchList::MatchList() {}

bool MatchList::add(std::string loggerID, std::string gameID, int playerCount, int matchDuration, std::string playerIDs, std::string winnerID) {
    MatchLog log;

    log.loggerID = loggerID;
    log.gameID = gameID;
    log.playerCount = playerCount;
    log.matchDuration = matchDuration;
    log.winnerID = winnerID;

    std::stringstream ss(playerIDs);
    std::string individualID;

    while (std::getline(ss >> std::ws, individualID, ',')) {
        log.playerIDs.add(individualID);
    }

    return List<MatchLog>::add(log);
}