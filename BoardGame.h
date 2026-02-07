#pragma once

#include<string>
#include"Item.h"


class BoardGame : public Item
{
	std::string name;
	int minPlayers;
	int maxPlayers;
	int minPlaytime;
	int maxPlaytime;
	int yearPublished;

public:
	BoardGame();
	BoardGame(const std::string name, const int minPlayers, const int maxPlayers, const int minPlaytime, const int maxPlaytime, const int yearPublished);
	void print() override;
};

