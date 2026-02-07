#include "ReviewList.h"

#include "InputValidation.h"
#include<iomanip>

ReviewList::ReviewList() {};

bool ReviewList::add(std::string reviewerID, std::string reviewerBody, int rating) {
    ReviewLog log;

    log.reviewerID = reviewerID;
    log.reviewBody = reviewerBody;
    log.reviewDate = getTodayDate();
    log.rating = rating;

    return List<ReviewLog>::add(log);
}

void ReviewList::print() {
    if (isEmpty()) {
        std::cout << "No reviews found." << "\n";
        return;
    }

    Node* temp = firstNode;
    while (temp != nullptr) {
        ReviewLog* review = &temp->item;
        std::cout << std::left << std::setw(11) << review->reviewerID
            << " | " << std::setw(15) << review->reviewDate
            << " | " << std::setw(7) << review->rating
            << " | " << review->reviewBody
            << "\n";

        temp = temp->next;
    }
}