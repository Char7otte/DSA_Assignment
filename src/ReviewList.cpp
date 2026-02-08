#include "ReviewList.h"
#include "List.h"
#include "Member.h"
#include "MemberDictionary.h"

#include<iomanip>
#include <ios>
#include <iostream>
#include <string>

ReviewList::ReviewList() {};

bool ReviewList::add(std::string reviewerID, std::string reviewerBody, int rating) {
    ReviewLog log;

    log.reviewerID = reviewerID;
    log.reviewBody = reviewerBody;
    log.rating = rating;

    return List<ReviewLog>::add(log);
}

void ReviewList::print(MemberDictionary& members) {
    if (isEmpty()) {
        std::cout << "No reviews found." << "\n";
        return;
    }

    Node* temp = firstNode;
    while (temp != nullptr) {
        ReviewLog* review = &temp->item;
        Member* reviewer = nullptr;
        members.get(review->reviewerID, reviewer);
        std::string reviewerName = reviewer->getName();

        std::cout << std::left << std::setw(11) << review->reviewerID
            << " | " << std::setw(30) << reviewerName
            << " | " << std::setw(15) << review->reviewDate
            << " | " << std::setw(7) << review->rating
            << " | " << review->reviewBody
            << "\n";

        temp = temp->next;
    }
}