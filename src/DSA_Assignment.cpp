// Classes
#include "GameDictionary.h"
#include "MemberDictionary.h"
#include "BoardGame.h"
#include "Member.h"
#include "MasterHistoryLog.h"

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
    MasterHistoryLog masterLog;

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
                    logout = adminDashboard(gameDict, memberDict, masterLog);
                }
                else {
                    logout = memberDashboard(gameDict, *loggedInAccount, masterLog);
                }
            }
        }
        else if (input == "0") {
            std::cout << "Goodbye!";
            break;
        }
        else {
            std::cout << "Invalid input. Please try again.";
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

//}
//void DisplayBorrowedGames(Member& selectedMember) {}
//void adminMenu(GameDictionary& gameDict, MemberDictionary& memberDict, MasterHistoryLog& historyList) {
//    int choice;
//
//    while (true) {
//        std::cout << "\n========= Admin Menu =========\n";
//        std::cout << "1) Add Game\n";
//        std::cout << "2) Delete Game\n";
//        std::cout << "3) View All Games\n";
//        std::cout << "4) Create Member\n";
//        std::cout << "5) Summary of All Borrowing Records\n";
//        std::cout << "6) Summary of Unreturned Games\n";
//        std::cout << "0) Logout\n";
//        std::cout << "Choose: ";
//
//        if (!(std::cin >> choice)) {
//            std::cin.clear();
//            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//            std::cout << "Invalid input.\n";
//            continue;
//        }
//
//        if (choice == 1) {
//            createAndAddGameMenu(gameDict);
//        } else if (choice == 2) {
//            deleteGameMenu(gameDict);
//        } else if (choice == 3) {
//            gameDict.print();
//        } else if (choice == 4) {
//            createMemberMenu(memberDict);
//        } else if (choice == 5) {
//            historyList.printAll();
//        } else if (choice == 6) {
//            historyList.printUnreturned();
//        } else if (choice == 0) {
//            std::cout << "Logging out...\n";
//            break;
//        } else {
//            std::cout << "Invalid option.\n";
//        }
//    }
//}
//
//void memberMenu(GameDictionary& gameDict,
//                MemberDictionary& memberDict,
//                MasterHistoryLog& historyList) {
//    cout << "\n======= Member Login =======\n";
//    cout << "Enter your Member ID (e.g., M001) (or 0 to cancel): ";
//
//    string memberId;
//    cin >> memberId;
//
//    if (memberId == "0") {
//        cout << "Cancelled.\n";
//        return;
//    }
//
//    Member* selectedMemberPtr = memberDict.getMember(memberId);
//    if (selectedMemberPtr == nullptr) {
//        cout << "Member ID not found.\n";
//        return;
//    }
//
//    Member& selectedMember = *selectedMemberPtr;
//
//    cout << "Welcome, " << selectedMember.getName()
//         << " (" << selectedMember.getID() << ")\n";
//
//    int choice;
//
//    while (true) {
//        cout << "\n========= Member Menu =========\n";
//        cout << "1) Borrow Game\n";
//        cout << "2) Return Game\n";
//        cout << "3) Summary of Games Borrowed\n";
//        cout << "0) Logout\n";
//        cout << "Choose: ";
//
//        if (!(cin >> choice)) {
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cout << "Invalid input.\n";
//            continue;
//        }
//
//        if (choice == 1) {
//            memberBorrowMenu(gameDict, selectedMember, historyList);
//        } else if (choice == 2) {
//            memberReturnMenu(gameDict, selectedMember, historyList);
//        }else if (choice == 3){
//            selectedMember.printBorrowHistory();
//        } else if (choice == 0) {
//            cout << "Logging out...\n";
//            return;
//        } else {
//            cout << "Invalid option.\n";
//        }
//    }
//}
//
//void mainMenu(GameDictionary& gameDict, MemberDictionary& memberDict, MasterHistoryLog& historyList) {
//    int role;
//
//    while (true) {
//        cout << "\n======= Login =======\n";
//        cout << "1) Admin\n";
//        cout << "2) Member\n";
//        cout << "0) Exit\n";
//        cout << "Choose: ";
//
//        if (!(cin >> role)) {
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            cout << "Invalid input.\n";
//            continue;
//        }
//
//        if (role == 1) {
//            adminMenu(gameDict, memberDict,historyList);
//        } else if (role == 2) {
//            memberMenu(gameDict, memberDict, historyList);
//        } else if (role == 0) {
//            cout << "Bye!\n";
//            break;
//        } else {
//            cout << "Invalid option.\n";
//        }
//    }
//}