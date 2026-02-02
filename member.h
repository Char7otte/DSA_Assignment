#pragma once

#include<string>
#include<list> //TEMPORARY



class member
{
	std::string name;
	std::list<std::string> borrowedGames; //TEMPORARY

public:
	bool borrow(std::string borrowedBoardGame); //TEMPORARY
	void getBorrowedSummary();
};

