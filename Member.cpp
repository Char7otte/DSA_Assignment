#include "Member.h"
#include <utility>

Member::Member(string id, string name) {
    this->id = std::move(id);
    this->name = std::move(name);
}
string Member::getID() const {
    return id;
}
string Member::getName() const {
    return name;
}

bool Member::borrowGame(BoardGame& game, string borrowDate) {
    bool borrowed = game.checkIsBorrowed();
    if (!borrowed) {

        borrowRecords[borrowCount] = {
            game.getID(), game.getName(), borrowDate, ""
        };
        borrowCount++;
        // cout << "Game borrowed successfully!" << endl;
        return true;

    }
    // cout << "Game is already borrowed!" << endl;
    return false;
}

bool Member::returnGame(BoardGame& game, string returnDate) {
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

