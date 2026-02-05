#include "Member.h"
#include<iomanip>

Member::Member(const std::string id, const std::string username, const std::string password, const std::string name) : Item(id, name) {
    this->username = username;
    this->password = password;
}

Member::Member(const std::string id, const std::string username, const std::string password, const bool isAdmin, const std::string name) : Item(id, name) {
    this->username = username;
    this->password = password;
    this->isAdmin = isAdmin;
}

void Member::print() {
    std::cout << id << " " << username << " " << password << " " << isAdmin << " " << name << "\n";
}

//bool Member::borrowGame(BoardGame& game, std::string borrowDate) {
//    bool borrowed = game.checkIsBorrowed();
//    if (!borrowed) {
//
//        borrowRecords[borrowCount] = {
//            game.getID(), game.getName(), borrowDate, "", false
//        };
//        borrowCount++;
//        // cout << "Game borrowed successfully!" << endl;
//        return true;
//
//    }
//    // cout << "Game is already borrowed!" << endl;
//    return false;
//}
//
//bool Member::returnGame(BoardGame& game, string returnDate) {
//    //game.returnGame(returnDate);
//
//    for (int i = borrowCount - 1; i >= 0; i--) {
//        if (borrowRecords[i].gameId == game.getID()) {
//            borrowRecords[i].returnDate = returnDate;
//            borrowRecords[i].isReturned = true;
//            return true;
//            //game.returnGame(returnDate);
//        }
//    }
//    return false;
//    //cout << "Game was not borrow by this member!" << endl;
//
//}
//
//
//void Member::printUnreturnedGames() const {
//    cout << "\n" << string(70, '=') << "\n";
//    cout << "UNRETURNED GAMES FOR MEMBER: " << name << " (" << id << ")\n";
//    cout << string(70, '=') << "\n";
//
//    cout << left
//         << setw(15) << "GAME ID"
//         << setw(30) << "GAME NAME"
//         << setw(20) << "BORROW DATE"
//         << "STATUS" << "\n";
//
//    cout << string(70, '-') << "\n";
//
//    int printed = 0;
//
//    for (int i = 0; i < borrowCount; i++) {
//        if (!borrowRecords[i].isReturned) {
//            cout << left
//                 << setw(15) << borrowRecords[i].gameId
//                 << setw(30) << borrowRecords[i].gameName
//                 << setw(20) << borrowRecords[i].loanDate
//                 << "[ON LOAN]" << "\n";
//            printed++;
//        }
//    }
//
//    if (printed == 0) {
//        cout << "(No unreturned games.)\n";
//    }
//
//    cout << string(70, '=') << "\n";
//}
//
//void Member::printBorrowHistory() const {
//    cout << "\n" << string(90, '=') << "\n";
//    cout << "BORROW HISTORY FOR MEMBER: " << name << " (" << id << ")\n";
//    cout << string(90, '=') << "\n";
//
//    cout << left
//         << setw(15) << "GAME ID"
//         << setw(30) << "GAME NAME"
//         << setw(18) << "BORROW DATE"
//         << setw(18) << "RETURN DATE"
//         << "STATUS" << "\n";
//
//    cout << string(90, '-') << "\n";
//
//    if (borrowCount == 0) {
//        cout << "(No borrow history.)\n";
//        cout << string(90, '=') << "\n";
//        return;
//    }
//
//    // Print newest first (your original idea)
//    for (int i = borrowCount - 1; i >= 0; i--) {
//        const auto& r = borrowRecords[i];
//
//        cout << left
//             << setw(15) << r.gameId
//             << setw(30) << r.gameName
//             << setw(18) << r.loanDate;
//
//        if (r.isReturned) {
//            cout << setw(16) << r.returnDate
//                 << "[RETURNED]";
//        } else {
//            cout << setw(16) << "---"
//                 << "[ON LOAN]";
//        }
//
//        cout << "\n";
//    }
//
//    cout << string(90, '=') << "\n";
//}


