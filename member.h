#pragma once

#include<string>
#include "List.h";
#include "BoardGame.h"

class Member
{
	std::string username;
	std::string password;
	std::string name;
	List borrowedGames;

public:
	Member(const std::string username, const std::string password, const std::string name);
	Member(const std::string username, const std::string password, const std::string name, const List borrowedGames);
//	bool borrow(BoardGame boardGameToBorrow);
//	void getBorrowedSummary();
};

