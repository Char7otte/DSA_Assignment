#include "List.h"
#include<iostream>

List::List() {
	firstNode = nullptr;
}

bool List::add(Item& newItem) {
	Node* newNode = new Node;
	newNode->item = &newItem;

	if (firstNode == nullptr) {
		firstNode = newNode;
		return true;
	}

	Node* temp = firstNode;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = newNode;
	return true;
}

int List::getLength() {
	std::cout << "GET LENGTH NOT SUPPORTED";
	return 0;
}

bool List::isEmpty() {
	return firstNode == nullptr;
}
