// #ifndef BOARDGAME_H
// #define BOARDGAME_H
//
// #include <array>
// #include <string>
// #include <iostream>
//
// #include "List.h"
//
// using namespace std;
//
// struct UsageRecord {
//     string borrowerId;
//     string borrowerName;
//     string borrowDate;
//     string returnDate;
// };
//
// struct Review {
//     string reviewerId;
//     string reviewerName;
//     string reviewDate;
//     string reviewText;
//     int rating;
// };
//
// class BoardGame {
// public:
//
//     BoardGame()
//         : id("0"), name(""), minPlayers(0), maxPlayers(0),
//           minPlayTime(0), maxPlayTime(0), yearPublished(0),
//           isBorrowed(false), borrowHistory(10),reviewHistory(10), historyCount(0) {}
//
//
//     string id;
//     string name;
//     int minPlayers;
//     int maxPlayers;
//     int minPlayTime;
//     int maxPlayTime;
//     int yearPublished;
//     bool isBorrowed;
//
//     // UsageRecord borrowHistory[10];
//     List<UsageRecord>borrowHistory;
//     List<Review> reviewHistory;
//     int historyCount;
//
// public:
//     BoardGame(string id, string name, int minP, int maxP,
//               int minTime, int maxTime, int year);
//
//     string getID() const;
//     string getName() const;
//
//     bool borrowGame(string borrowerId, string borrowerName, string date);
//     bool returnGame(string returnDate);
//
//     bool checkIsBorrowed();
//
//     //UsageRecord getLastestBorrowRecord();
//
//
//     void printInfo() const;
//     // void printBorrowHistory();
//     // void checkIfBorrowedAndPrintLatest() const;
// };
//
// #endif
#ifndef BOARDGAME_H
#define BOARDGAME_H

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
    string reviewDate;
    string reviewText;
    int rating;
};

class BoardGame {
public:
    BoardGame()
        : id("0"), name(""), minPlayers(0), maxPlayers(0),
          minPlayTime(0), maxPlayTime(0), yearPublished(0),
          isBorrowed(false), borrowHistory(10), reviewHistory(10) {}

    BoardGame(string id, string name, int minP, int maxP,
              int minTime, int maxTime, int year);

    string getID() const;
    string getName() const;

    bool borrowGame(string borrowerId, string borrowerName, string date);
    bool returnGame(string returnDate);

    bool checkIsBorrowed() const;

    void printInfo() const;

// private:
    string id;
    string name;
    int minPlayers;
    int maxPlayers;
    int minPlayTime;
    int maxPlayTime;
    int yearPublished;
    bool isBorrowed;

    List<UsageRecord> borrowHistory;
    List<Review> reviewHistory;
};

#endif
