#include "MemberDictionary.h"

#include<iostream>

MemberDictionary::MemberDictionary() {}

void MemberDictionary::print() {
    for (int i = 0; i < MAX_SIZE; i++) {
        Node* temp = items[i];

        while (temp != nullptr) {
            Item* member = temp->item;
            member->print();
            temp = temp->next;
        }
    }
}

