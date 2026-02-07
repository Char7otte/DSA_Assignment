// #include "BoardGame.h"
//
// // Constructor
// BoardGame::BoardGame(string id, string name, int minP, int maxP,
//                      int minTime, int maxTime, int year)
//     : id(id), name(name), minPlayers(minP), maxPlayers(maxP),
//       minPlayTime(minTime), maxPlayTime(maxTime),
//       yearPublished(year), borrowHistory(10),reviewHistory(10), isBorrowed(false), historyCount(0) {}
//
//
//
// string BoardGame::getID() const {
//     return id;
// }
// string BoardGame::getName() const {
//     return name;
// }
//
//
// // Borrow
// bool BoardGame::borrowGame(string borrowerId, string borrowerName, string date) {
//     if (isBorrowed)
//         cout << "Game is already borrow" << endl;
//         return false;
//
//     // Create the record struct
//     UsageRecord newRecord = {
//         borrowerId,
//         borrowerName,
//         date,
//         "" // Use "N/A" or empty string for return date
//     };
//
//     // Use the .add() method from your custom List class
//     if (borrowHistory.add(newRecord)) {
//         isBorrowed = true;
//         historyCount++;
//         // Note: size is handled inside borrowHistory.add()
//         cout << "Game borrowed successfully << " << endl;
//         return true;
//     }
//
//     // If .add() returns false, it means the list is full (capacity 10)
//     cout << "failed" << endl;
//     return false;
// }
//
// // Return
// bool BoardGame::returnGame(string returnDate) {
//     if (!isBorrowed)
//         return false;
//
//     isBorrowed = false;
//     borrowHistory.getRef(historyCount-1).returnDate = returnDate;
//     //cout << "Game returned successfully!" << endl;
//     return true;
// }
//
// bool BoardGame::checkIsBorrowed() {
//     return isBorrowed;
// }
//
// // UsageRecord BoardGame::getLastestBorrowRecord() {
// //     return borrowHistory[historyCount - 1];
// // }
//
//
// void BoardGame::printInfo() const {
//         cout << "[ id= " << id
//         << ", name= \"" << name << "\""
//         << ", players= " << minPlayers << "-" << maxPlayers
//         << ", playtime= " << minPlayTime << "-" << maxPlayTime
//         << ", year= " << yearPublished
//         << ", borrowed= " << isBorrowed
//         << "]" << endl;
// }
// //
// //
// // // Print full history
// // void BoardGame::printBorrowHistory(){
// //     cout << "Borrowing history of " << name << ":" << endl;
// //     for (int i = historyCount-1; i >= 0; i--) {
// //         cout<< "BorrowerId: " << borrowHistory[i].borrowerId
// //             << ", Borrower: " << borrowHistory[i].borrowerName
// //              << ", Borrowed: " << borrowHistory[i].borrowDate
// //              << ", Returned: " << borrowHistory[i].returnDate << endl;
// //     }
// // }
// //
// // // Check + print latest
// // void BoardGame::checkIfBorrowedAndPrintLatest() const {
// //     if (isBorrowed) {
// //         const UsageRecord& latest = borrowHistory[historyCount - 1];
// //         cout << name << " is currently borrowed by: "<< latest.borrowerName << endl;
// //
// //         cout << "Borrower ID: " << latest.borrowerId << endl;
// //         cout << "Borrower Name: " << latest.borrowerName << endl;
// //         cout << "Borrow Date: " << latest.borrowDate << endl;
// //         cout << "Return Date: "
// //              << (latest.returnDate.empty() ? "Not returned yet" : latest.returnDate)
// //              << endl;
// //     }else {
// //         cout << name << " is currently available!" << endl;
// //     }
// // }
#include "BoardGame.h"

// Constructor
BoardGame::BoardGame(string id, string name, int minP, int maxP,
                     int minTime, int maxTime, int year)
    : id(id), name(name), minPlayers(minP), maxPlayers(maxP),
      minPlayTime(minTime), maxPlayTime(maxTime),
      yearPublished(year), isBorrowed(false),
      borrowHistory(10), reviewHistory(10) {}

string BoardGame::getID() const { return id; }
string BoardGame::getName() const { return name; }

bool BoardGame::borrowGame(string borrowerId, string borrowerName, string date) {
    if (isBorrowed) {
        cout << "Game is already borrowed." << endl;
        return false;
    }

    UsageRecord newRecord{ borrowerId, borrowerName, date, "" };

    borrowHistory.add(newRecord); // always true now (auto-resize)
    isBorrowed = true;
    return true;
}

bool BoardGame::returnGame(string returnDate) {
    if (!isBorrowed) {
        cout << "Game is not currently borrowed." << endl;
        return false;
    }

    if (borrowHistory.getLength() == 0) {
        cout << "Error: no borrow history found." << endl;
        return false;
    }

    int lastIndex = borrowHistory.getLength() - 1;
    borrowHistory.getRef(lastIndex).returnDate = returnDate;

    isBorrowed = false;
    cout << "Game returned successfully!" << endl;
    return true;
}

bool BoardGame::checkIsBorrowed() const {
    return isBorrowed;
}

void BoardGame::printInfo() const {
    cout << "[ id= " << id
         << ", name= \"" << name << "\""
         << ", players= " << minPlayers << "-" << maxPlayers
         << ", playtime= " << minPlayTime << "-" << maxPlayTime
         << ", year= " << yearPublished
         << ", borrowed= " << (isBorrowed ? "true" : "false")
         << " ]" << endl;
}
