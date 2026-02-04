#ifndef BOARDGAME_H
#define BOARDGAME_H

#include <array>
#include <string>
#include <iostream>

using namespace std;

struct BurrowRecord {
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
    array<BurrowRecord, MAX_HISTORY> burrowHistory;
    int historyCount;

public:
    BoardGame(string id, string name, int minP, int maxP,
              int minTime, int maxTime, int year);

    bool borrowGame(string borrowerId, string borrowerName, string date);
    bool returnGame(string returnDate);

    void printInfo() const;
    void printBurrowHistory() const;
    void checkIfBorrowedAndPrintLatest() const;
};

#endif
