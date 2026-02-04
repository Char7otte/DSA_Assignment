#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <array>
#include <string>
#include <iostream>

using namespace std;

struct UsageRecord {
    string borrowerId;
    string borrowerName;
    string borrowDate;
    string returnDate;
};

class BoardGame {
public:

    BoardGame()
        : id("0"), name(""), minPlayers(0), maxPlayers(0),
          minPlayTime(0), maxPlayTime(0), yearPublished(0),
          isBorrowed(false), historyCount(0) {}


    string id;
    string name;
    int minPlayers;
    int maxPlayers;
    int minPlayTime;
    int maxPlayTime;
    int yearPublished;
    bool isBorrowed;

    static const int MAX_HISTORY = 10;
    array<UsageRecord, MAX_HISTORY> borrowHistory;
    int historyCount;

public:
    BoardGame(string id, string name, int minP, int maxP,
              int minTime, int maxTime, int year);

    string getID() const;
    string getName() const;

    bool borrowGame(string borrowerId, string borrowerName, string date);
    bool returnGame(string returnDate);

    bool checkIsBorrowed();

    // // set the game to be borrowed
    // void markAvailable(string borrowDate);
    //
    // // set the game to be returned
    // void markBorrowed(string returnDate);

    void printInfo() const;
    void printBorrowHistory();
    void checkIfBorrowedAndPrintLatest() const;
};

#endif
