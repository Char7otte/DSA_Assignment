#ifndef DSA_ASSIGNMENT_MEMBER_H
#define DSA_ASSIGNMENT_MEMBER_H

#include <string>
#include <iostream>
#include <iomanip>

#include "BoardGame.h"
#include "List.h"

using namespace std;

struct GameRental {
    string gameId;
    string gameName;
    string borrowDate;
    string returnDate;
    bool isReturned;
};


class Member {
private:
    string id;
    string name;

    List<GameRental> borrowRecords; // ✅ replace array
    // no need borrowCount anymore

public:
    Member() : id(""), name(""), borrowRecords(10) {} // initial capacity 10
    Member(string id, string name);

    string getID() const;
    string getName() const;

    bool borrowGame(BoardGame& game, string borrowDate);
    bool returnGame(BoardGame& game, string returnDate);

    void printUnreturnedGames() ;
    void printBorrowHistory();
};

#endif // DSA_ASSIGNMENT_MEMBER_H
