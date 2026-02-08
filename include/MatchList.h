#pragma once

#include "List.h"
#include "InputValidation.h"

#include<string>
#include<sstream>
#include<istream>

struct MatchLog {
    std::string loggerID = "N/A";
    std::string gameID = "N/A";
    std::string matchDate = getTodayDate();
    int playerCount = -1;
    int matchDuration = -1;
    List<std::string> playerIDs{};
    std::string winnerID = "N/A";
};


class MatchList: public List<MatchLog>
{
public:
    MatchList();

    bool add(std::string loggerID, std::string gameID, int playerCount, int matchDuration, std::string playerIDs, std::string winnerID) {
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
};

