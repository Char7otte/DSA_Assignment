#pragma once

//
// Created by gongy on 4/2/2026.
//

#include <iostream>
#include <array>

#include "Item.h"
#include "BoardGame.h"

struct BorrowLog: public DateLog {
    std::string gameID = "N/A";
    std::string gameName = "N/A";
    std::string returnDate = "NOT RETURNED";
};

class Member: public Item {
    bool isAdmin = false;
    static constexpr int MAX_SIZE = 5;
    BorrowLog borrowHistory[MAX_SIZE];
    int borrowCount = 0;

public:
    Member();
    Member(const std::string id, const std::string name);
    Member(const std::string id, const std::string name, const bool isAdmin);

    void print() override;

    std::string getName();
    bool getIsAdmin();

    bool borrowGame(BoardGame& game);

    bool returnGame(BoardGame& game);

    void printLoans();
    //void printBorrowHistory() const;
};
