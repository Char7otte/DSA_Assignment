#include "BoardGame.h"

// Constructor
BoardGame::BoardGame(const std::string id,
    const std::string name,
    const int minPlayers,
    const int maxPlayers,
    const int minPlaytime,
    const int maxPlaytime,
    const int yearPublished) : Item(id, name) {
    this->minPlayers = minPlayers;
    this->maxPlayers = maxPlayers;
    this->minPlaytime = minPlaytime;
    this->maxPlaytime = maxPlaytime;
    this->yearPublished = yearPublished;
}

BoardGame::BoardGame(const std::string id,
    const std::string name,
    const int minPlayers,
    const int maxPlayers,
    const int minPlaytime,
    const int maxPlaytime,
    const int yearPublished,
    const bool isBorrowed) : Item(id, name) {
    this->minPlayers = minPlayers;
    this->maxPlayers = maxPlayers;
    this->minPlaytime = minPlaytime;
    this->maxPlaytime = maxPlaytime;
    this->yearPublished = yearPublished;
}

bool BoardGame::getIsBorrowed() {
    return loanInfo.borrowerID != "N/A";
}

bool BoardGame::borrowGame(std::string borrowerID, std::string borrowerName) {
    if (getIsBorrowed())
        return false;

    loanInfo.borrowerID = borrowerID;
    loanInfo.borrowerName = borrowerName;
    loanInfo.loanDate = borrowerName;

    return true;
}

// Return
bool BoardGame::returnGame() {
    if (!isBorrowed)
        return false;

    loanInfo = {};
    return true;
}

void BoardGame::print() {
    std::cout << "Game ID: " << id
        << " | Name: " << name
        << " | Players: " << minPlayers << "-" << maxPlayers
        << " | Playtime: " << minPlaytime << "-" << maxPlaytime << " mins"
        << " | Year: " << yearPublished
        << " | Status: " << (getIsBorrowed() ? "Loaned" : "Available")
        << "\n";
}

void BoardGame::printAvailable() {
    if (getIsBorrowed()) return;
    else print();
}

//UsageRecord BoardGame::getLastestBorrowRecord() {
//    return borrowHistory[historyCount - 1];
//}
//
//
//void BoardGame::printInfo() const {
//        cout << "[ id= " << id
//        << ", name= \"" << name << "\""
//        << ", players= " << minPlayers << "-" << maxPlayers
//        << ", playtime= " << minPlayTime << "-" << maxPlayTime
//        << ", year= " << yearPublished
//        << ", borrowed= " << (isBorrowed ? "Yes" : "No")
//        << "]" << endl;
//}
//
//
//// Print full history
//void BoardGame::printBorrowHistory(){
//    cout << "Borrowing history of " << name << ":" << endl;
//    for (int i = historyCount-1; i >= 0; i--) {
//        cout<< "BorrowerId: " << borrowHistory[i].borrowerId
//            << ", Borrower: " << borrowHistory[i].borrowerName
//             << ", Borrowed: " << borrowHistory[i].borrowDate
//             << ", Returned: " << borrowHistory[i].returnDate << endl;
//    }
//}
//
//// Check + print latest
//void BoardGame::checkIfBorrowedAndPrintLatest() const {
//    if (isBorrowed) {
//        const UsageRecord& latest = borrowHistory[historyCount - 1];
//        cout << name << " is currently borrowed by: "<< latest.borrowerName << endl;
//
//        cout << "Borrower ID: " << latest.borrowerId << endl;
//        cout << "Borrower Name: " << latest.borrowerName << endl;
//        cout << "Borrow Date: " << latest.borrowDate << endl;
//        cout << "Return Date: "
//             << (latest.returnDate.empty() ? "Not returned yet" : latest.returnDate)
//             << endl;
//    }else {
//        cout << name << " is currently available!" << endl;
//    }
//}
