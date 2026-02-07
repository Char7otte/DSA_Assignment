#pragma once

#include "Item.h"
#include "ReviewList.h"
#include "InputValidation.h"

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
    LoanInfo loanInfo = {}; //This is a struct because the board game only needs to store who is currently borrowing em
    ReviewList reviewList{}; //This is a list storing structs because there can be multiple reviews

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

    void print() override;

    void printAvailable();

    bool getIsBorrowed();

    bool borrowGame(std::string borrowerID, std::string borrowerName);

    bool returnGame();

    bool addReview(std::string reviewerID, std::string reviewBody, int rating);

    void printReviews();

    bool hasReviews();

    bool printReviewed();
};
