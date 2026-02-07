#include "Item.h"

Item::Item() {}

Item::Item(const std::string id, const std::string name) {
	this->id = id;
	this->name = name;
}

std::string Item::getID() {
	return id;
}

std::string Item::getName() {
	return name;
}