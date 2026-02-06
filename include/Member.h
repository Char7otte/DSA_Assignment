#pragma once

//
// Created by gongy on 4/2/2026.
//

#include <iostream>
#include <array>

#include "Item.h"
#include "BoardGame.h"

struct BorrowLog: public DateLog {
    std::string gameId = "N/A";
    std::string gameName = "N/A";
    bool isReturned = false;
};

class Member: public Item {
    bool isAdmin = false;
    BorrowLog borrowHistory[10];
    int borrowCount = 0;

public:
    Member();
    Member(const std::string id, const std::string name);
    Member(const std::string id, const std::string name, const bool isAdmin);

    void print() override;

    std::string getName();

    //bool borrowGame(BoardGame& game, string borrowDate);
    //bool returnGame(BoardGame& game, string returnDate);
    //void printUnreturnedGames() const;
    //void printBorrowHistory() const;
};
