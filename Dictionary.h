#pragma once

#include "Item.h"

#include<string>

using KeyType = std::string;    //Dict key
using ItemType = Item*;  //Dict value.

struct Node {
	KeyType key = "N/A";
	ItemType item = nullptr;
	Node* next = nullptr;
};

class Dictionary
{
protected:
	static constexpr int MAX_SIZE = 101;
	Node* items[MAX_SIZE] = {};
	int size = 0;

public:
	Dictionary();
	~Dictionary();

	int hash(const KeyType keyToHash);

	// Add a new item with the specified key
	bool add(const KeyType newKey, const ItemType newItem);

	// Remove an item with the specified key
	bool remove(const KeyType keyOfItemToRemove);

	// Use a key to find its value
	ItemType* get(const KeyType keyToFind);

	// Check if the dictionary contains a key
	bool contains(const KeyType keyToContain);

	bool isEmpty();

	int getLength();

	virtual void print() = 0;
};

