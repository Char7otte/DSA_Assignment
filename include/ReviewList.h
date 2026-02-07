#pragma once

#include "List.h"

#include<string>

struct ReviewLog {
    std::string reviewerID;
    std::string reviewDate;
    std::string reviewBody;
    int rating;
};

class ReviewList: public List<ReviewLog>
{
public:
    ReviewList();

    bool add(std::string reviewerID, std::string reviewerBody, int rating);
    void print();
};

