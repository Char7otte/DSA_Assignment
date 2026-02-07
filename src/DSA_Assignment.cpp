// Classes
#include "GameDictionary.h"
#include "MemberDictionary.h"
#include "BoardGame.h"
#include "Member.h"
#include "BorrowList.h"

// General Functions
#include "FileUtilities.h"
#include "InputValidation.h"

#include<string>
#include<iostream>

//Account functions
Member* login(MemberDictionary& members);
#include "AdminSystem.h"
#include "MemberSystem.h"

int main() {
    GameDictionary gameDict;
    readGameFile("./data/games.csv", gameDict);
    MemberDictionary memberDict;
    readMemberFile("./data/members.csv", memberDict);
    Member* loggedInAccount;
    BorrowList* loanList = new BorrowList();

    while (true) {
        std::cout << "Welcome to the BGC Portal!" << "\n";
        std::cout << "1. Login" << "\n";
        std::cout << "0. Quit" << "\n";

        std::string input;
        std::getline(std::cin, input);
        if (input == "1") {
            while (true) {
                loggedInAccount = login(memberDict);
                if (loggedInAccount == nullptr) {
                    std::cout << "Invalid credentials. Please try again." << "\n";
                    continue;
                }
                break;
            }
            bool logout = false;
            while (!logout) {
                std::cout << "\n";
                std::cout << "Welcome, " << loggedInAccount->getName() << "!" << "\n";
                if (loggedInAccount->getIsAdmin()) {
                    logout = adminDashboard(gameDict, memberDict, *loanList);
                }
                else {
                    logout = memberDashboard(gameDict, *loggedInAccount, *loanList);
                }
            }
        }
        else if (input == "0") {
            std::cout << "Goodbye!";
            break;
        }
        else {
            std::cout << "Invalid input. Please try again." << "\n";
            continue;
        }
        continue;
    }

    return 0;
};

Member* login(MemberDictionary& members) {
    std::string id;
    std::cout << "Enter your ID: ";
    std::getline(std::cin, id);

    Member* foundAccount = nullptr;
    members.get(id, foundAccount);
    return foundAccount;
}