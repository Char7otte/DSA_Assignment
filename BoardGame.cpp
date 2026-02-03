#include "BoardGame.h"
#include<iostream>

BoardGame::BoardGame() {}

BoardGame::BoardGame(const std::string name, const int minPlayers, const int maxPlayers, const int minPlaytime, const int maxPlaytime, const int yearPublished) {
	this->name = name;
	this->minPlayers = minPlayers;
	this->maxPlayers = maxPlayers;
	this->minPlaytime = minPlaytime;
	this->maxPlaytime = maxPlaytime;
	this->yearPublished = yearPublished;
}

void BoardGame::print() {
	std::cout << name << " | ";
	std::cout << minPlayers << " | ";
	std::cout << maxPlayers << " | ";
	std::cout << minPlaytime << " | ";
	std::cout << maxPlaytime << " | ";
	std::cout << "\n";
}
