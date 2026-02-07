#include "MasterHistoryLog.h"


#include<string>
#include<iostream>
#include <iomanip> // Required for setw()
using std::left;
using std::setw;
using namespace std;


MasterHistoryLog::MasterHistoryLog() = default;


bool MasterHistoryLog::add(BoardGame& game,Member& member, const string& borrowDate) {

    BorrowRecordType item = {member.getID(),
        game.getID(),
        member.getName(),
        game.getName(),
        borrowDate,
        "",
        false};

    Node* newNode = new Node;
    newNode->item = item;
    newNode->next = nullptr;

    newNode->next = firstNode;
    firstNode = newNode;

    borrowedCount++;
    size++;
    return true;
}



bool MasterHistoryLog::markReturned(const string& returnDate,const string& gameID) {
    // Traverse the list to find the game with the given ID
    Node* current = firstNode;
    while (current != nullptr) {
        if (current->item.gameId == gameID) {
            current->item.returnDate = returnDate;
            current->item.isReturned = true;
            borrowedCount--;
            return true;
        }
        current = current->next;
    }
    return false;
}


// BorrowRecordType MasterHistoryLog::get(int index) {
//     Node* temp = firstNode;
//     for (int i = 0; i < index; i++) {
//         temp = temp->next;
//     }
//     return temp->item;
// }

bool MasterHistoryLog::isEmpty() {

    return size == 0;
}

int MasterHistoryLog::getLength() {

    return size;
}



void MasterHistoryLog::printAll() {
    if (firstNode == nullptr) {
        cout << "\n[!] The history log is empty.\n" << endl;
        return;
    }

    const int W = 120; // table width (adjust if you want)

    cout << "\n" << string(W, '=') << endl;
    cout << "MASTER HISTORY LOG (ALL RECORDS)\n";
    cout << string(W, '=') << endl;

    cout << left
         << setw(12) << "MEMBER ID"
         << setw(20) << "MEMBER NAME"
         << setw(10) << "GAME ID"
         << setw(25) << "GAME NAME"
         << setw(18) << "BORROW DATE"
         << setw(18) << "RETURN DATE"
         << "STATUS" << endl;

    cout << string(W, '-') << endl;

    Node* temp = firstNode;
    while (temp != nullptr) {
        BorrowRecordType& record = temp->item;

        cout << left
             << setw(12) << record.memberId
             << setw(20) << record.memberName
             << setw(10) << record.gameId
             << setw(25) << record.gameName
             << setw(18) << record.borrowDate
             << setw(18) << (record.isReturned ? record.returnDate : "---")
             << (record.isReturned ? "[RETURNED]" : "[ON LOAN]")
             << endl;

        temp = temp->next;
    }

    cout << string(W, '=') << "\n" << endl;
}


void MasterHistoryLog::printUnreturned() {
    const int W = 120;

    cout << "\n" << string(W, '=') << endl;
    cout << "UNRETURNED BORROW RECORDS (ON LOAN)\n";
    cout << string(W, '=') << endl;

    cout << left
         << setw(12) << "MEMBER ID"
         << setw(20) << "MEMBER NAME"
         << setw(10) << "GAME ID"
         << setw(25) << "GAME NAME"
         << setw(18) << "BORROW DATE"
         << setw(18) << "RETURN DATE"
         << "STATUS" << endl;

    cout << string(W, '-') << endl;

    Node* current = firstNode;
    int printed = 0;

    // ✅ Stop once all unreturned records are printed
    while (current != nullptr && printed < borrowedCount) {
        BorrowRecordType& record = current->item;

        if (!record.isReturned) {
            cout << left
                 << setw(12) << record.memberId
                 << setw(20) << record.memberName
                 << setw(10) << record.gameId
                 << setw(25) << record.gameName
                 << setw(18) << record.borrowDate
                 << setw(18) << "---"
                 << "[ON LOAN]" << endl;

            printed++;
        }

        current = current->next;
    }

    if (printed == 0) {
        cout << "(No unreturned records found.)" << endl;
    }

    cout << string(W, '=') << "\n" << endl;
}


int MasterHistoryLog::checkBorrowedCount() {
    return borrowedCount;
}



// Destructor

MasterHistoryLog::~MasterHistoryLog() {

    Node* current = firstNode;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}


