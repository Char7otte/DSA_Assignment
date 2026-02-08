#pragma once

#include "Item.h"

#include <string>

class BoardGame;

struct BorrowLogMember: public DateLog {
    std::string gameID = "N/A";
    std::string gameName = "N/A";
    std::string returnDate = "NOT RETURNED";
};

class Member: public Item {
    bool isAdmin = false;
    static constexpr int MAX_SIZE = 5;
    BorrowLogMember borrowHistory[MAX_SIZE];
    int borrowCount = 0;

public:
    Member();
    Member(const std::string id, const std::string name);
    Member(const std::string id, const std::string name, const bool isAdmin);
    /*~Member()*/ //Unnecessary since borrowHistory isn't an array of pointers and will clear itself up

    void print() override;

    std::string getName();
    bool getIsAdmin() const; // shout out to the compiler for detecting that this one function can be made const

    bool borrowGame(BoardGame& game);

    bool returnGame(BoardGame& game);

    void printLoans() const;

    bool hasLoans() const;
};
