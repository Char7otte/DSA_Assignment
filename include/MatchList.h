#pragma once

#include "List.h"
#include "InputValidation.h"

#include<string>

struct MatchLog {
    std::string loggerID = "N/A";
    std::string gameID = "N/A";
    std::string matchDate = getTodayDate();
    int matchDuration = -1;
    std::string playerIDs = "N/A";
    std::string winnerID = "N/A";
};


class MatchList: public List<MatchLog>
{
public:
    MatchList();

    bool add(std::string loggerID, std::string gameID, int matchDuration, std::string playerIDs, std::string winnerID);
    void print();
};

