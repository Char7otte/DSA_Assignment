#include "BorrowList.h"
#include "BoardGame.h"
#include "GameDictionary.h"
#include "InputValidation.h"
#include "List.h"
#include "Member.h"
#include "MemberDictionary.h"

#include<iomanip>
#include <ios>
#include <iostream>
#include <string>

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

// Get head and return via params
bool BorrowList::get(std::string& memberID, std::string& gameID) {
	if (isEmpty()) return false;
	memberID = firstNode->item.borrowerID;
	gameID = firstNode->item.gameID;
	return true;
}

void BorrowList::print(GameDictionary& games, MemberDictionary& members) {
	const int TOTAL_WIDTH = 100;

	std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ') << "BORROW HISTORY\n";
	std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

	std::cout << std::left << std::setw(10) << "MEMBER ID"
		<< " | " << std::setw(20) << "MEMBER NAME"
		<< " | " << std::setw(8) << "GAME ID"
		<< " | " << std::setw(20) << "GAME NAME"
		<< " | " << std::setw(15) << "LOAN DATE"
		<< " | " << std::setw(15) << "RETURN DATE"
		<< "\n";

	std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
	Node* temp = firstNode;
	while (temp != nullptr) {
		BorrowLog borrowLog = temp->item;

		BoardGame* logGame = {};
		games.get(borrowLog.gameID, logGame);
		std::string gameName = logGame->getName();

		Member* logMember = {};
		members.get(borrowLog.borrowerID, logMember);
		std::string memberName = logMember->getName();

		std::cout << std::left << std::setw(10) << borrowLog.borrowerID
			<< " | " << std::setw(20) << (memberName.length() > 17 ? memberName.substr(0, 17) + "..." : memberName)
			<< " | " << std::setw(8) << borrowLog.gameID
			<< " | " << std::setw(20) << (gameName.length() > 17 ? gameName.substr(0, 17) + "..." : gameName)
			<< " | " << std::setw(15) << borrowLog.loanDate
			<< " | " << std::setw(15) << borrowLog.returnDate
			<< "\n";

		temp = temp->next;
	}
	std::cout << std::string(TOTAL_WIDTH, '-') << "\n" << "\n";
}

void BorrowList::printNotReturned(GameDictionary& games, MemberDictionary& members) {
	const int TOTAL_WIDTH = 100;

	std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ') << "BORROW HISTORY\n";
	std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

	std::cout << std::left << std::setw(10) << "MEMBER ID"
		<< " | " << std::setw(20) << "MEMBER NAME"
		<< " | " << std::setw(8) << "GAME ID"
		<< " | " << std::setw(20) << "GAME NAME"
		<< " | " << std::setw(15) << "LOAN DATE"
		<< " | " << std::setw(15) << "RETURN DATE"
		<< "\n";

	std::cout << std::string(TOTAL_WIDTH, '-') << "\n";
	Node* temp = firstNode;
	while (temp != nullptr) {
		BorrowLog borrowLog = temp->item;
		if (borrowLog.returnDate != "") {
			temp = temp->next;
			continue;
		}

		BoardGame* logGame = {};
		games.get(borrowLog.gameID, logGame);
		std::string gameName = logGame->getName();

		Member* logMember = {};
		members.get(borrowLog.borrowerID, logMember);
		std::string memberName = logMember->getName();

		std::cout << std::left << std::setw(10) << borrowLog.borrowerID
			<< " | " << std::setw(20) << (memberName.length() > 17 ? memberName.substr(0, 17) + "..." : memberName)
			<< " | " << std::setw(8) << borrowLog.gameID
			<< " | " << std::setw(20) << (gameName.length() > 17 ? gameName.substr(0, 17) + "..." : gameName)
			<< " | " << std::setw(15) << borrowLog.loanDate
			<< " | " << std::setw(15) << borrowLog.returnDate
			<< "\n";

		temp = temp->next;
	}
	std::cout << std::string(TOTAL_WIDTH, '-') << "\n" << "\n";
}

BorrowLog* BorrowList::find(const std::string& borrowerID, std::string& gameID) { //genuinely do not understand why const needs to be here but that's just C++ being C++
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
