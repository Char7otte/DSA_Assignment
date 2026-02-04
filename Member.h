//
// Created by gongy on 4/2/2026.
//

#ifndef DSA_ASSIGNMENT_MEMBER_H
#define DSA_ASSIGNMENT_MEMBER_H
#include <string>
#include <iostream>
#include <array>
#include "BoardGame.h"
using namespace std;

struct GameRental {
    string gameId;
    string gameName;
    string borrowDate;
    string returnDate;
};

class Member {

private:

    string id;
    string name;
    GameRental borrowRecords[10];
    int borrowCount = 0;

public:
    Member() : id(""), name("") {}
    Member(string id, string name);
    string getID() const;
    string getName() const;

    bool borrowGame(BoardGame& game, string borrowDate);
    bool returnGame(BoardGame& game, string returnDate);
    void printBorrowHistory() const;
};


#endif //DSA_ASSIGNMENT_MEMBER_H