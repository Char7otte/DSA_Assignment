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

    // if (firstNode == nullptr) {
    //     //
    //      //GameBorrowRecordList is empty, make new node the first node
    //     firstNode = newNode;
    // } else {
    //     // Traverse to the end of the GameBorrowRecordList
    //
    //     Node* current = firstNode;
    //     while (current->next != nullptr) {
    //         current = current->next;
    //     }
    //     current->next = newNode;
    // }

    borrowedCount++;
    size++;
    return true;
}

bool MasterHistoryLog::add(int index,const BorrowRecordType &item) {

    if (index < 0 || index > size) {
        return false;
    }

    Node* newNode = new Node;
    newNode->item = item;

    newNode->next = firstNode;
    firstNode = newNode;

    // if (index == 0) {
    //     // Insert at the beginning
    //     newNode->next = firstNode;
    //     firstNode = newNode;
    // }
    // else {
    //     // Traverse to the position before index
    //     Node* current = firstNode;
    //     for (int i = 0; i < index - 1; i++) {
    //         current = current->next;
    //     }
    //     newNode->next = current->next;
    //     current->next = newNode;
    // }

    size++;
    return true;
}

void MasterHistoryLog::remove(int index) {


    if (index < 0 || index >= size) {
        return;
    }

    Node* nodeToDelete;

    if (index == 0) {
        // Remove the first node
        nodeToDelete = firstNode;
        firstNode = firstNode->next;
    } else {
        // Traverse to the node before the one to remove
        Node* current = firstNode;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }
        nodeToDelete = current->next;
        current->next = nodeToDelete->next;
    }

    delete nodeToDelete;
    borrowedCount--;
    size--;

}

BorrowRecordType MasterHistoryLog::get(int index) {

    Node* temp = firstNode;
    for (int i = 0; i < index; i++) {
        temp = temp->next;
    }
    return temp->item;


}

bool MasterHistoryLog::isEmpty() {

    return size == 0;
}

int MasterHistoryLog::getLength() {

    return size;
}

void MasterHistoryLog::print() {
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

// Destructor

MasterHistoryLog::~MasterHistoryLog() {

    Node* current = firstNode;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}


