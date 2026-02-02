#include "List.h"
#include<iostream>

List::List() {
	firstNode = nullptr;
}

bool List::add(BoardGame newBoardGame) {
	Node* newNode = new Node;
	newNode->item = newBoardGame;

	if (isEmpty()) {
		firstNode = newNode;
		return true;
	}

	Node* temp = firstNode;
	while (temp->next != nullptr) {
		temp = temp->next;
	}
	temp->next = newNode;
}

void  List::remove(int index) {}
BoardGame List::get(int index) {
	BoardGame foundBoardGame;
	return foundBoardGame;
}
int List::getLength() {
	return 0;
}
bool List::isEmpty() {
	return firstNode == nullptr;
}
void List::printAll() {

	std::cout << "name" << " | ";
	std::cout << "minPlayers" << " | ";
	std::cout << "maxPlayers" << " | ";
	std::cout << "minPlaytime" << " | ";
	std::cout << "maxPlaytime" << " | ";
	std::cout << "\n";

	Node* temp = firstNode;
	while (temp != nullptr) {
		temp->item.print();
		temp = temp->next;
	}
}