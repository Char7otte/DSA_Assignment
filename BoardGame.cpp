#include "BoardGame.h"

// Constructor
BoardGame::BoardGame(string id, string name, int minP, int maxP,
                     int minTime, int maxTime, int year)
    : id(id), name(name), minPlayers(minP), maxPlayers(maxP),
      minPlayTime(minTime), maxPlayTime(maxTime),
      yearPublished(year), isBorrowed(false), historyCount(0) {}



string BoardGame::getID() const {
    return id;
}
string BoardGame::getName() const {
    return name;
}


// Borrow
bool BoardGame::borrowGame(string borrowerId, string borrowerName, string date) {
    if (isBorrowed || historyCount >= MAX_HISTORY)
        return false;

    isBorrowed = true;

    borrowHistory[historyCount] = {
        borrowerId,
        borrowerName,
        date,
        ""
    };

    historyCount++;
    return true;
}

// Return
bool BoardGame::returnGame(string returnDate) {
    if (!isBorrowed)
        return false;

    isBorrowed = false;
    borrowHistory[historyCount - 1].returnDate = returnDate;
    cout << "Game returned successfully!" << endl;
    return true;
}

bool BoardGame::checkIsBorrowed() {
    return isBorrowed;
}



void BoardGame::printInfo() const {
        cout << "[ id= " << id
        << ", name= \"" << name << "\""
        << ", players= " << minPlayers << "-" << maxPlayers
        << ", playtime= " << minPlayTime << "-" << maxPlayTime
        << ", year= " << yearPublished
        << ", borrowed= " << (isBorrowed ? "Yes" : "No")
        << "]" << endl;
}


// Print full history
void BoardGame::printBorrowHistory(){
    cout << "Borrowing history of " << name << ":" << endl;
    for (int i = historyCount-1; i >= 0; i--) {
        cout<< "BorrowerId: " << borrowHistory[i].borrowerId
            << ", Borrower: " << borrowHistory[i].borrowerName
             << ", Borrowed: " << borrowHistory[i].borrowDate
             << ", Returned: " << borrowHistory[i].returnDate << endl;
    }
}

// Check + print latest
void BoardGame::checkIfBorrowedAndPrintLatest() const {
    if (isBorrowed) {
        const UsageRecord& latest = borrowHistory[historyCount - 1];
        cout << name << " is currently borrowed by: "<< latest.borrowerName << endl;

        cout << "Borrower ID: " << latest.borrowerId << endl;
        cout << "Borrower Name: " << latest.borrowerName << endl;
        cout << "Borrow Date: " << latest.borrowDate << endl;
        cout << "Return Date: "
             << (latest.returnDate.empty() ? "Not returned yet" : latest.returnDate)
             << endl;
    }else {
        cout << name << " is currently available!" << endl;
    }
}
