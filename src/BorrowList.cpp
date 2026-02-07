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

//Add to head a struct
bool BorrowList::add(BorrowLog& log) {
	Node* newNode = new Node;
	newNode->item = log;

	newNode->next = firstNode;
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

void BorrowList::print() {
	Node* temp = firstNode;
	while (temp != nullptr) {
		BorrowLog borrowLog = temp->item;
		std::cout << borrowLog.borrowerID << " " << borrowLog.gameID << " " << borrowLog.loanDate << " " << borrowLog.returnDate << "\n";
		temp = temp->next;
	}
}

BorrowList::BorrowLog* BorrowList::find(const std::string& borrowerID, std::string& gameID) { //genuinely do not understand why const needs to be here but that's just C++ being C++
	if (isEmpty()) return nullptr;

	Node* temp = firstNode;
	while (temp != nullptr) {
		if (temp->item.borrowerID == borrowerID && temp->item.gameID == gameID) {
			return &temp->item;
		}
		temp = temp->next;
	}
	return nullptr;
}

bool BorrowList::returnGame(const std::string& borrowerID, std::string& gameID) { //genuinely do not understand why const needs to be here but that's just C++ being C++
	BorrowLog* returningLog = find(borrowerID, gameID);
	returningLog->returnDate = getTodayDate();
	return true;
}

BorrowList BorrowList::findAll(const std::string& borrowerID) {
	BorrowList foundItems{};
	Node* temp = firstNode;
	while (temp != nullptr) {
		if (temp->item.borrowerID == borrowerID) {
			foundItems.add(temp->item);
		}
		temp = temp->next;
	}
	return foundItems;
}
