#pragma once

#include "InputValidation.h"

#include<string>

class BorrowList
{
	struct BorrowLog {
		std::string borrowerID = "N/A";
		std::string gameID = "N/A";
		std::string loanDate = getTodayDate();
		std::string returnDate = "N/A";
	};

	struct Node {
		BorrowLog item{};
		Node* next = nullptr;
	};

	Node* firstNode = nullptr;

	BorrowList();
	~BorrowList();

	// Add to head
	bool add(std::string memberID, std::string gameID);

	// Remove head
	bool remove();

	// Get head and return via params
	bool get(std::string& memberID, std::string& gameID);

	bool isEmpty();
};

