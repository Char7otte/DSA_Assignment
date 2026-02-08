#include "Member.h"

#include "InputValidation.h"
#include "BoardGame.h"

#include<iomanip>

Member::Member() {}

Member::Member(const std::string id, const std::string name) : Item(id, name) {
}

Member::Member(const std::string id, const std::string name, const bool isAdmin) : Item(id, name) {
    this->isAdmin = isAdmin;
}

void Member::print() {
    std::cout << std::left << std::setw(8) << id
        << " | " << std::setw(30) << name
        << " | " << std::setw(10) << (isAdmin ? "Yes" : "")
        << "\n";
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
            borrowCount--;
            return true;
        }
    }
    return false;
}

void Member::printLoans() {
    const int TOTAL_WIDTH = 74;

    std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ') << "BORROWED GAMES\n";
    std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

    std::cout << std::left << std::setw(8) << "ID"
        << " | " << std::setw(50) << "NAME"
        << " | " << std::setw(15) << "LOAN DATE"
        << "\n";

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    for (int i = 0; i < MAX_SIZE; i++) {
        BorrowLogMember borrowLog = borrowHistory[i];
        if (borrowLog.gameID == "N/A") continue;
        std::cout << std::left << std::setw(8) << borrowLog.gameID
            << " | " << std::setw(50) << (borrowLog.gameName.length() > 47 ? borrowLog.gameName.substr(0, 47) + "..." : borrowLog.gameName)
            << " | " << std::setw(15) << borrowLog.loanDate
            << "\n";
    }

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
}

bool Member::hasLoans() {
    return borrowCount > 0;
}