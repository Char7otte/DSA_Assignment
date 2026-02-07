#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <array>
#include <string>
#include <iostream>
#include "List.h"
using namespace std;

struct UsageRecord {
    string borrowerId;
    string borrowerName;
    string borrowDate;
    string returnDate;
};

struct Review {
    string reviewerId;
    string reviewerName;
    int rating;
    string review;
};

class BoardGame {
public:

    BoardGame()
        : id("0"), name(""), minPlayers(0), maxPlayers(0),
          minPlayTime(0), maxPlayTime(0), yearPublished(0),
          isBorrowed(false),borrowHistory(10), reviews(10), historyCount(0) {}


    string id;
    string name;
    int minPlayers;
    int maxPlayers;
    int minPlayTime;
    int maxPlayTime;
    int yearPublished;
    bool isBorrowed;


    List<UsageRecord> borrowHistory;
    List<Review> reviews;
    int historyCount;

public:
    BoardGame(string id, string name, int minP, int maxP,
              int minTime, int maxTime, int year);

    string getID() const;
    string getName() const;

    bool borrowGame(string borrowerId, string borrowerName, string date);
    bool returnGame(string returnDate);

    bool checkIsBorrowed();

    UsageRecord getLastestBorrowRecord();

    // // set the game to be borrowed
    // void markAvailable(string borrowDate);
    //
    // // set the game to be returned
    // void markBorrowed(string returnDate);

    // void printInfo() const;
    // void printBorrowHistory();
    // void checkIfBorrowedAndPrintLatest() const;
};

#endif
