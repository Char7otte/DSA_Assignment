#pragma once

#include "BoardGame.h"

struct Node {
	BoardGame item;
	Node* next = nullptr;
};

class List
{
	Node* firstNode;

public:
	List();
	bool add(BoardGame newBoardGame);
	void remove(int index);
	BoardGame get(int index);
	int getLength();
	bool isEmpty();
	void printAll();
};

