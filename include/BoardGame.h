#pragma once

#include "Item.h"

#include <string>
#include<array>
#include<iostream>

struct LoanInfo : public DateLog {
    std::string borrowerID = "N/A";
    std::string borrowerName = "N/A";
};

class BoardGame : public Item {
private:
    int minPlayers = 0;
    int maxPlayers = 0;
    int minPlaytime = 0;
    int maxPlaytime = 0;
    int yearPublished = 0;
    bool isBorrowed = false;
    LoanInfo loanInfo = {};
    int historyCount = 0;

public:
    BoardGame(const std::string id,
        const std::string name,
        const int minPlayers,
        const int maxPlayers,
        const int minPlaytime,
        const int maxPlaytime,
        const int yearPublished);

    BoardGame(const std::string id,
        const std::string name,
        const int minPlayers,
        const int maxPlayers,
        const int minPlaytime,
        const int maxPlaytime,
        const int yearPublished,
        const bool isBorrowed);

    void print() override {
        std::cout << "Game ID: " << id
            << " | Name: " << name
            << " | Players: " << minPlayers << "-" << maxPlayers
            << " | Playtime: " << minPlaytime << "-" << maxPlaytime << " mins"
            << " | Year: " << yearPublished
            << " | Status: " << (isBorrowed ? "Borrowed" : "Available")
            << "\n";
    }

    bool getIsBorrowed();

    bool borrowGame(std::string borrowerID, std::string borrowerName);

    //bool borrowGame(std::string borrowerId, std::string borrowerName, std::string date);
    //bool returnGame(std::string returnDate);

    //UsageRecord getLastestBorrowRecord();

    //// // set the game to be borrowed
    //// void markAvailable(string borrowDate);
    ////
    //// // set the game to be returned
    //// void markBorrowed(string returnDate);

    //void printInfo() const;
    //void printBorrowHistory();
    //void checkIfBorrowedAndPrintLatest() const;
};
