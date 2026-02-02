#include "Member.h"

Member::Member(const std::string username, const std::string password, const std::string name) {
	this->username = username;
	this->password = password;
	this->name = name;
}

Member::Member(const std::string username, const std::string password, const std::string name, const List borrowedGames) {
	this->username = username;
	this->password = password;
	this->name = name;
	this->borrowedGames = borrowedGames;
}