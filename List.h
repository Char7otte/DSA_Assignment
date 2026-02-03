#pragma once

#include "BoardGame.h"
#include "Item.h"

struct Node {
	Item* item;
	Node* next = nullptr;
};

class List
{
protected:
	Node* firstNode = nullptr;

public:
	List();

	virtual void remove() = 0;
	virtual Item* get() = 0;
	virtual void printAll() = 0;

	bool add(Item& newItem);
	int getLength();
	bool isEmpty();
};

