#include "BoardGameList.h"
#include "BoardGame.h"

BoardGameList::BoardGameList() {}

void BoardGameList::remove() {}

Item* BoardGameList::get() {
	return nullptr;
}

void BoardGameList::printAll() {
	if (isEmpty()) return;
	Node* temp = firstNode;
	while (temp != nullptr) {
		temp->item->print();
		temp = temp->next;
	}
}
