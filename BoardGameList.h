#pragma once

#include "List.h"
#include "BoardGame.h"

class BoardGameList: public List
{
public:
	BoardGameList();
	void remove() override;
	Item* get() override;
	void printAll() override;
};

