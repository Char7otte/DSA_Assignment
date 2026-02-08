#pragma once

#include "Item.h"
#include "ReviewList.h"
#include "MatchList.h"

#include <string>

class MemberDictionary; //having to do this and do the include inside the implementation
                                       //to prevent a circular include in the big 26 is insane

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
    MatchList matchList{};

public:
    BoardGame(const std::string id,
        const std::string name,
        const int minPlayers,
        const int maxPlayers,
        const int minPlaytime,
        const int maxPlaytime,
        const int yearPublished);

    void print() override;

    void printAvailable();

    bool getIsBorrowed() const;

    bool borrowGame(std::string borrowerID, std::string borrowerName);

    bool returnGame();

    bool addReview(std::string reviewerID, std::string reviewBody, int rating);

    void printReviews(MemberDictionary& members);

    void printReviewsDescendingRating(MemberDictionary& members);

    bool hasReviews();

    bool printReviewed();

    bool addMatch(std::string loggerID, std::string gameID, int matchDuration, std::string playerIDs, std::string winnerID);

    void printMatches();

    bool hasMatches();

    bool printMatched();
};
