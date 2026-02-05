#include "MasterHistoryLog.h"

#include<string>
#include<iostream>
#include <iomanip> // Required for setw()
using namespace std;


MasterHistoryLog::MasterHistoryLog() = default;


bool MasterHistoryLog::add(const BorrowRecordType &item) {



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

    // Print Header
    cout << "\n" << string(80, '=') << endl;
    cout << left << setw(15) << "MEMBER ID"
         << setw(15) << "GAME ID"
         << setw(20) << "BORROW DATE"
         << setw(20) << "RETURN DATE"
         << "STATUS" << endl;
    cout << string(80, '-') << endl;

    Node* temp = firstNode;
    while (temp != nullptr) {
        BorrowRecordType &record = temp->item;

        // Print Row
        cout << left << setw(15) << record.memberId
             << setw(15) << record.gameId
             << setw(20) << record.borrowDate;

        if (record.isReturned) {
            cout << setw(20) << record.returnDate
                 << "[RETURNED]";
        } else {
            cout << setw(20) << "---"
                 << "[ON LOAN]";
        }

        cout << endl;
        temp = temp->next;
    }

    cout << string(80, '=') << "\n" << endl;
}

void MasterHistoryLog::printUnreturned() {
    cout << "\n" << string(80, '=') << endl;
    cout << "UNRETURNED BORROW RECORDS (ON LOAN)" << endl;
    cout << string(80, '=') << endl;

    cout << left << setw(15) << "MEMBER ID"
         << setw(15) << "GAME ID"
         << setw(20) << "BORROW DATE"
         << setw(20) << "RETURN DATE"
         << "STATUS" << endl;

    cout << string(80, '-') << endl;

    Node* current = firstNode;
    int printed = 0;

    while (current != nullptr && printed < borrowedCount) {
        BorrowTransaction& record = current->item;

        if (!record.isReturned) {
            cout << left << setw(15) << record.memberId
                 << setw(15) << record.gameId
                 << setw(20) << record.borrowDate
                 << setw(20) << "---"
                 << "[ON LOAN]" << endl;

            printed++;
        }
        current = current->next;
    }

    if (printed == 0) {
        cout << "(No unreturned records found.)" << endl;
    }

    cout << string(80, '=') << "\n" << endl;
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


