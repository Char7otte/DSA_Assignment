#pragma once

#include "Item.h"

#include<string>
#include<iostream>

using KeyType = std::string;

template<typename T> //T is storing Item subclasses Member & BoardGame
class Dictionary
{
protected:
	struct Node {
		KeyType key = "N/A";
		T item{};
		Node* next = nullptr;
	};

	static constexpr int MAX_SIZE = 101;
	Node* items[MAX_SIZE] = {};
	int size = 0;

public:
	Dictionary() {}
	~Dictionary() {
		for (int i = 0; i < MAX_SIZE; i++) {

			Node* current = items[i];

			//Go through the current index in case there are collisions
			while (current != nullptr) {
				Node* previous = current;
				current = current->next;
				delete previous;
			}

			items[i] = nullptr;
		}
	}

	int hash(const KeyType keyToHash) {
		if (keyToHash.empty()) {
			return 0;
		}

		int hashValue = 0;

		for (char c : keyToHash) {
			hashValue = (hashValue * 31 + c) % MAX_SIZE;
		}
		return hashValue;
	}

	// Add a new item with the specified key
	bool add(const KeyType newKey, const T newItem) {
		int index = hash(newKey);
		Node* temp = items[index];

		//Check if the dictionary already has an item with newKey.
		// KeyType is the ID of the item, which means the dictionary already contains a copy of the 'new' node.
		while (temp != nullptr) {
			if (temp->key == newKey) {
				std::cout << "Error. Identical ID found in dictionary." << "\n";
				return false;
			}
			temp = temp->next;
		}

		Node* newNode = new Node;
		newNode->key = newKey;
		newNode->item = newItem;

		//Unnecessary to handle if items[index] == nullptr, since next'll remain nullptr.
		newNode->next = items[index];
		items[index] = newNode;
		size++;
		return true;
	}

	// Remove an item with the specified key
	bool remove(const KeyType keyOfItemToRemove) {
		int index = hash(keyOfItemToRemove);
		Node* temp = items[index];
		Node* previous = nullptr;

		while (temp != nullptr) {
			if (temp->key == keyOfItemToRemove) {
				if (previous == nullptr) { //If previous is nullptr, it means that the first node is being removed.
					items[index] = temp->next;  //Unnecessary to handle if there are no more items after, since it'll remain nullptr.
				}
				else {
					previous->next = temp->next;
				}
				delete temp;
				size--;
				return true;
			}
			previous = temp;
			temp = temp->next;
		}

		return false;
	}

	// Use a key to find its value
	bool get(const KeyType keyToFind) {
		int index = hash(keyToFind);
		Node* temp = items[index];

		while (temp != nullptr) {
			if (temp->key == keyToFind) {
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	// Use a key to find its value & return it
	bool get(const KeyType keyToFind, T& item) {
		int index = hash(keyToFind);
		Node* temp = items[index];

		while (temp != nullptr) {
			if (temp->key == keyToFind) {
				item = temp->item;
				return true;
			}
			temp = temp->next;
		}
		return false;
	}

	bool isEmpty() {
		return size == 0;
	}

	int getLength() {
		return size;
	}

	virtual void print() = 0;
};

