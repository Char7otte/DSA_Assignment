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

public:
	BorrowList();
	~BorrowList();

	// Add to head
	bool add(std::string memberID, std::string gameID);

	//Add to head a struct
	bool add(BorrowLog& log);

	// Remove head
	bool remove();

	// Get head and return via params
	bool get(std::string& memberID, std::string& gameID);

	BorrowLog* find(const std::string& borrowerID, std::string& gameID);

	bool isEmpty();

	void print();

	bool returnGame(const std::string& borrowerID, std::string& gameID);

	BorrowList findAll(const std::string& borrowerID);
};

