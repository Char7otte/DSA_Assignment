#include "Member.h"

#include "InputValidation.h"

#include<iomanip>

Member::Member() {}

Member::Member(const std::string id, const std::string name) : Item(id, name) {
}

Member::Member(const std::string id, const std::string name, const bool isAdmin) : Item(id, name) {
    this->isAdmin = isAdmin;
}

void Member::print() {
    std::cout << id << " " << name << " " << (isAdmin ? "Admin" : "Member") << "\n";
}

std::string Member::getName() {
    return name;
}

bool Member::getIsAdmin() {
    return isAdmin;
}

bool Member::borrowGame(BoardGame& gameToBorrow) {
    if (borrowCount >= MAX_SIZE) {
        return false;
    }

    if (!gameToBorrow.getIsBorrowed()) {

        borrowHistory[borrowCount].gameID = gameToBorrow.getID();
        borrowHistory[borrowCount].gameName = gameToBorrow.getName();
        borrowHistory[borrowCount].loanDate = getTodayDate();

        borrowCount++;
        return true;

    }
    return false;
}

bool Member::returnGame(BoardGame& game) {
    for (int i = borrowCount - 1; i >= 0; i--) {
        if (borrowHistory[i].gameID == game.getID()) {
            borrowHistory[i] = {};
            return true;
        }
    }
    return false;
}

void Member::printLoans() {
    for (int i = 0; i < MAX_SIZE; i++) {
        BorrowLog borrowLog = borrowHistory[i];
        if (borrowLog.gameID == "N/A") continue;
        std::cout << borrowLog.gameID << " " << borrowLog.gameName << " " << borrowLog.loanDate << " " << borrowLog.returnDate << "\n";
    }
}

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


