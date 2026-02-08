#pragma once

#include "MemberDictionary.h"
#include "GameDictionary.h"
#include "List.h"

#include "InputValidation.h"

#include<string>

struct BorrowLog {
	std::string borrowerID = "N/A";
	std::string gameID = "N/A";
	std::string loanDate = getTodayDate();
	std::string returnDate = "N/A";
};

class BorrowList: public List<BorrowLog>
{
public:
	using List<BorrowLog>::add; //Because BorrowList has its own add, it will ignore add() in base class by default
	BorrowList();
	~BorrowList();

	// Add to head
	bool add(std::string memberID, std::string gameID);

	// Get head and return via params
	bool get(std::string& memberID, std::string& gameID);

	BorrowLog* find(const std::string& borrowerID, std::string& gameID);

	void print(GameDictionary& games, MemberDictionary& members);

	bool returnGame(const std::string& borrowerID, std::string& gameID);

	BorrowList findAll(const std::string& borrowerID);
};

