#pragma once

template<typename T>
class List
{
protected:
	struct Node {
		T item{};
		Node* next = nullptr;
	};

	Node* firstNode = nullptr;

public:
	List() {}
	virtual ~List() { //Needs to be virtual because if a generic base class object is created, this won't be called
		Node* current = firstNode;
		while (current != nullptr) {
			Node* nextNode = current->next; 
			delete current;                
			current = nextNode;            
		}
		firstNode = nullptr;
	}

	// Add to head an already created struct
	bool add(T& item) {
		Node* newNode = new Node;
		newNode->item = item;

		newNode->next = firstNode;
		firstNode = newNode;
		return true;
	}

	// Remove head
	bool remove() {
		if (isEmpty()) return false;

		Node* temp = firstNode;
		firstNode = firstNode->next;
		delete temp;
		return true;
	}

	bool isEmpty() {
		return firstNode == nullptr;
	}

	// Get head
	Node* get() {
		return firstNode;
	}
};

