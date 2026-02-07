#include "BorrowList.h"

BorrowList::BorrowList() {}
BorrowList::~BorrowList() {
	while (firstNode != nullptr) {
		Node* temp = firstNode;
		firstNode = firstNode->next;
		delete temp;
	}
}

// Add to head
bool BorrowList::add(std::string memberID, std::string gameID) {
	Node* newNode = new Node;
	newNode->item.borrowerID = memberID;
	newNode->item.gameID = gameID;

	newNode->next = firstNode; //Automatically handles firstNode == nullptr
	firstNode = newNode;
	return true;
}

// Remove from head
bool BorrowList::remove() {
	if (isEmpty()) return false;

	Node* temp = firstNode;
	firstNode = firstNode->next;
	delete temp;
	return true;
}

// Get head and return via params
bool BorrowList::get(std::string& memberID, std::string& gameID) {
	if (isEmpty()) return false;
	memberID = firstNode->item.borrowerID;
	gameID = firstNode->item.gameID;
	return true;
}

bool BorrowList::isEmpty() {
	return firstNode == nullptr;
}
