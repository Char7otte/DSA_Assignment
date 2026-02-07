#include "Member.h"
#include <utility>
#include <iomanip>
#include <iostream>
using namespace std;

// Member::Member(string id, string name) {
////     this->id = std::move(id);
////     this->name = std::move(name);
//// }

Member::Member(string id,string name)
    : id(id), name(name), borrowRecords(10) {}

string Member::getID() const {
    return id;
}

string Member::getName() const {
    return name;
}

bool Member::borrowGame(BoardGame& game, string borrowDate) {
    bool borrowed = game.checkIsBorrowed();
    if (!borrowed) {
        // Create the struct locally
        GameRental newRecord = {
            game.getID(), game.getName(), borrowDate, "", false
        };

        // Use the List's .add() method
        if (borrowRecords.add(newRecord)) {
            borrowCount++;
            return true;
        }
    }
    return false;
}

bool Member::returnGame(BoardGame& game, string returnDate) {
    // Loop through the current items in the list
    for (int i = borrowRecords.getLength() - 1; i >= 0; i--) {
        // Use getRef to get the actual object, not a copy
        GameRental& current = borrowRecords.getRef(i);

        if (current.gameId == game.getID() && !current.isReturned) {
            current.returnDate = returnDate; // Modifies the list directly!
            current.isReturned = true;
            return true;
        }
    }
    return false;
}


void Member::printUnreturnedGames() const {
    cout << "\n" << string(70, '=') << "\n";
    cout << "UNRETURNED GAMES FOR MEMBER: " << name << " (" << id << ")\n";
    cout << string(70, '=') << "\n";

    cout << left
         << setw(15) << "GAME ID"
         << setw(30) << "GAME NAME"
         << setw(20) << "BORROW DATE"
         << "STATUS" << "\n";

    cout << string(70, '-') << "\n";



    if (borrowRecords.getLength() == 0) {
        cout << "(No unreturned games.)\n";
    }

    for (int i = borrowRecords.getLength() - 1; i >= 0; i--) {
        GameRental r = borrowRecords.get(i); // get() is fine here for reading

        cout << left << setw(15) << r.gameId
             << setw(30) << r.gameName
             << setw(18) << r.borrowDate;

        if (r.isReturned) {
            cout << setw(16) << r.returnDate << "[RETURNED]\n";
        } else {
            cout << setw(16) << "---" << "[ON LOAN]\n";
        }
    }

    cout << string(70, '=') << "\n";
}

void Member::printBorrowHistory() const {
    cout << "\n" << string(90, '=') << "\n";
    cout << "BORROW HISTORY FOR MEMBER: " << name << " (" << id << ")\n";
    cout << string(90, '=') << "\n";

    if (borrowRecords.getLength() == 0) {
        cout << "(No borrow history.)\n";
        return;
    }

    cout << left
         << setw(15) << "GAME ID"
         << setw(30) << "GAME NAME"
         << setw(18) << "BORROW DATE"
         << setw(18) << "RETURN DATE"
         << "STATUS" << "\n";
    cout << string(90, '-') << "\n";

    for (int i = borrowRecords.getLength() - 1; i >= 0; i--) {
        GameRental r = borrowRecords.get(i);
        cout << left
             << setw(15) << r.gameId
             << setw(30) << r.gameName
             << setw(18) << r.borrowDate;

        if (r.isReturned) {
            cout << setw(16) << r.returnDate << "[RETURNED]\n";
        } else {
            cout << setw(16) << "---" << "[ON LOAN]\n";
        }
    }
    cout << string(90, '=') << "\n";
}


