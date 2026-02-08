#include "MemberDictionary.h"
#include "Dictionary.h"
#include "Member.h"

#include<iostream>
#include<iomanip>
#include <ios>
#include <string>

MemberDictionary::MemberDictionary() {}

void MemberDictionary::print() {
    const int TOTAL_WIDTH = 50;

    std::cout << "\n" << std::string((TOTAL_WIDTH / 2) - 10, ' ') << "MEMBER LIST\n";
    std::cout << std::string(TOTAL_WIDTH, '=') << "\n";

    std::cout << std::left << std::setw(8) << "ID"
        << " | " << std::setw(30) << "NAME"
        << " | " << std::setw(10) << "ADMIN"
        << "\n";

    std::cout << std::string(TOTAL_WIDTH, '-') << "\n";

    for (int i = 0; i < MAX_SIZE; i++) {
        Node* temp = items[i];

        while (temp != nullptr) {
            Member* member = temp->item;
            member->print();
            temp = temp->next;
        }
    }
    std::cout << std::string(TOTAL_WIDTH, '-') << "\n" << "\n";
}

