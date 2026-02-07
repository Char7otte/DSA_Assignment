

#include "Member.h"
#include <utility>
using namespace std;

Member::Member(string id, string name)
    : id(std::move(id)), name(std::move(name)), borrowRecords(10) {}

string Member::getID() const { return id; }
string Member::getName() const { return name; }

bool Member::borrowGame(BoardGame& game, string borrowDate) {
    // ✅ must check board game availability
    if (game.checkIsBorrowed()) {
        // cout << "Game is already borrowed!\n";
        return false;
    }

    // ✅ call game.borrowGame so game state + history updates
    if (!game.borrowGame(id, name, borrowDate)) {
        return false;
    }

    GameRental record{
        game.getID(),
        game.getName(),
        borrowDate,
        "",
        false
    };
    borrowRecords.add(record);

    // ✅ list handles capacity (if you use the resizing version),
    // or returns false if you kept fixed-size version
    // if (!borrowRecords.add(record)) {
    //     // Rollback game borrow if your List is fixed-size (optional)
    //     // game.returnGame(borrowDate); // not correct date though; you'd pass a return date
    //     return false;
    // }

    return true;
}

bool Member::returnGame(BoardGame& game, string returnDate) {
    // Find latest matching unreturned rental (newest first)
    for (int i = borrowRecords.getLength() - 1; i >= 0; i--) {
        GameRental& r = borrowRecords.getRef(i);

        if (r.gameId == game.getID() && !r.isReturned) {
            // ✅ update member record
            r.returnDate = returnDate;
            r.isReturned = true;

            // ✅ update game status + game borrow history return date
            return game.returnGame(returnDate);
        }
    }

    return false;
}

void Member::printUnreturnedGames() {
    cout << "\n" << string(70, '=') << "\n";
    cout << "UNRETURNED GAMES FOR MEMBER: " << name << " (" << id << ")\n";
    cout << string(70, '=') << "\n";

    cout << left
         << setw(15) << "GAME ID"
         << setw(30) << "GAME NAME"
         << setw(20) << "BORROW DATE"
         << "STATUS" << "\n";

    cout << string(70, '-') << "\n";

    int printed = 0;

    for (int i = 0; i < borrowRecords.getLength(); i++) {
        const GameRental& r = borrowRecords.getRef(i);
        if (!r.isReturned) {
            cout << left
                 << setw(15) << r.gameId
                 << setw(30) << r.gameName
                 << setw(20) << r.borrowDate
                 << "[ON LOAN]\n";
            printed++;
        }
    }

    if (printed == 0) {
        cout << "(No unreturned games.)\n";
    }

    cout << string(70, '=') << "\n";
}

void Member::printBorrowHistory() {
    cout << "\n" << string(90, '=') << "\n";
    cout << "BORROW HISTORY FOR MEMBER: " << name << " (" << id << ")\n";
    cout << string(90, '=') << "\n";

    cout << left
         << setw(15) << "GAME ID"
         << setw(30) << "GAME NAME"
         << setw(18) << "BORROW DATE"
         << setw(18) << "RETURN DATE"
         << "STATUS" << "\n";

    cout << string(90, '-') << "\n";

    if (borrowRecords.getLength() == 0) {
        cout << "(No borrow history.)\n";
        cout << string(90, '=') << "\n";
        return;
    }

    // newest first
    for (int i = borrowRecords.getLength() - 1; i >= 0; i--) {
        const GameRental& r = borrowRecords.getRef(i);

        cout << left
             << setw(15) << r.gameId
             << setw(30) << r.gameName
             << setw(18) << r.borrowDate;

        if (r.isReturned) {
            cout << setw(18) << r.returnDate
                 << "[RETURNED]";
        } else {
            cout << setw(18) << "---"
                 << "[ON LOAN]";
        }
        cout << "\n";
    }

    cout << string(90, '=') << "\n";
}

