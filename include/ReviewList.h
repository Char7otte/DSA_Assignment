#pragma once

#include "List.h"
#include "MemberDictionary.h"
#include "InputValidation.h"

#include <string>

struct ReviewLog {
    std::string reviewerID = "N/A";
    std::string reviewDate = getTodayDate();
    std::string reviewBody = "N/A";
    int rating = -1;
};

class ReviewList: public List<ReviewLog>
{
public:
    ReviewList();

    bool add(std::string reviewerID, std::string reviewerBody, int rating);
    void print(MemberDictionary& members);
};

