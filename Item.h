#pragma once

#include<string>

struct DateLog {
	std::string loanDate = "0000-00-00"; //Year/Month/Day
	std::string returnDate = "0000-00-00"; //Year/Month/Day
};

class Item {
protected:
	std::string id = "N/A";
	std::string name = "N/A";

public:
	Item(const std::string id, const std::string name);

	std::string getID() {}
	std::string getName() {}
};

