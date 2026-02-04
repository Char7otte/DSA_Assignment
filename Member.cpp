//
// Created by gongy on 4/2/2026.
//

#include "Member.h"

#include <utility>

Member::Member(string id, string name) {
    this->id = std::move(id);
    this->name = std::move(name);
}

void Member::burrowGame(BoardGame& game, string borrowDate) {
    bool borrowed = game.checkIsBorrowed();
    if (!borrowed) {
        game.borrowGame(id, name, borrowDate);
        borrowRecords[borrowCount] = {
            game.getID(), game.getName(), borrowDate, ""
        };
        borrowCount++;
        cout << "Game borrowed successfully!" << endl;
    }
    else cout << "Game is already borrowed!" << endl;
}

void Member::returnGame(BoardGame& game, string returnDate) {
    game.returnGame(returnDate);

    for (int i = borrowCount - 1; i >= 0; i--) {
        if (borrowRecords[i].gameId == game.getID()) {
            borrowRecords[i].returnDate = returnDate;
            game.returnGame(returnDate);
        }
    }
    cout << "Game was not borrow by this member!" << endl;

}

void Member::printBorrowHistory() const {
    cout << "Borrowing history of " << name << ":" << endl;
    for (int i = borrowCount-1; i >= 0; i--) {
        cout << "Game Id: " << borrowRecords[i].gameId
             << ",Game name: " << borrowRecords[i].gameName
             << ", Borrowed: " << borrowRecords[i].borrowDate
             << ", Returned: " << borrowRecords[i].returnDate << endl;
    }
}

