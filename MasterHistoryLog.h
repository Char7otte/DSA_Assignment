// List.h - - Specification of List ADT (implemented using Pointers)
#pragma once
#include<string>
#include<iostream>
using namespace std;

struct BorrowTransaction {
    string memberId;
    string gameId;
    string borrowDate;
    string returnDate;     // Initially "N/A" or empty
    bool isReturned;
};

typedef BorrowTransaction BorrowRecordType;

class MasterHistoryLog
{
private:
    struct Node
    {
        BorrowRecordType item;	// item
        Node     *next;	// pointer pointing to next item
    };
    Node *firstNode = nullptr; // point to the first item
    int  borrowedCount = 0;
    int  size = 0;		// number of items in the list

public:
    // constructor
    MasterHistoryLog();

    // destructor
    ~MasterHistoryLog();

    // add an item to the back of the list (append)
    bool add(const BorrowRecordType &item);

    // add an item at a specified position in the list (insert)
    bool add(int index, const BorrowRecordType &item);

    // remove an item at a specified position in the list
    void remove(int index);

    // get an item at a specified position of the list (retrieve)
    BorrowRecordType get(int index);

    // check if the list is empty
    bool isEmpty();

    // check the size of the list
    int getLength();

    // display all the items in the list
    void print();
};
