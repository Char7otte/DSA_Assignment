#include "BoardGame.h"
#include "GameDictionary.h"

#include<iomanip>

// Constructor
BoardGame::BoardGame(const std::string id,
    const std::string name,
    const int minPlayers,
    const int maxPlayers,
    const int minPlaytime,
    const int maxPlaytime,
    const int yearPublished) : Item(id, name) {
    this->minPlayers = minPlayers;
    this->maxPlayers = maxPlayers;
    this->minPlaytime = minPlaytime;
    this->maxPlaytime = maxPlaytime;
    this->yearPublished = yearPublished;
}

BoardGame::BoardGame(const std::string id,
    const std::string name,
    const int minPlayers,
    const int maxPlayers,
    const int minPlaytime,
    const int maxPlaytime,
    const int yearPublished,
    const bool isBorrowed) : Item(id, name) {
    this->minPlayers = minPlayers;
    this->maxPlayers = maxPlayers;
    this->minPlaytime = minPlaytime;
    this->maxPlaytime = maxPlaytime;
    this->yearPublished = yearPublished;
}

bool BoardGame::getIsBorrowed() {
    return loanInfo.borrowerID != "N/A";
}

bool BoardGame::borrowGame(std::string borrowerID, std::string borrowerName) {
    if (getIsBorrowed())
        return false;

    loanInfo.borrowerID = borrowerID;
    loanInfo.borrowerName = borrowerName;
    loanInfo.loanDate = borrowerName;

    return true;
}

// Return
bool BoardGame::returnGame() {
    if (!getIsBorrowed())
        return false;

    loanInfo = {};
    return true;
}

void BoardGame::print() {
    //2-2 Players becomes 2 players
    std::string players = (minPlayers == maxPlayers ? 
        std::to_string(minPlayers) :
        std::to_string(minPlayers) + "-" + std::to_string(maxPlayers));

    //120 - 120 mins becomes 120 mins
    std::string playtime = (minPlaytime == maxPlaytime ?
        std::to_string(minPlaytime) :
        std::to_string(minPlaytime) + "-" + std::to_string(maxPlaytime));


    std::cout << std::left << std::setw(8) << id
        << " | " << std::setw(50) << (name.length() > 47 ? name.substr(0, 47) + "..." : name)
        << " | " << std::setw(15) << (players + " players")
        << " | " << std::setw(15) << (playtime + " mins")
        << " | " << std::setw(6) << yearPublished
        << " | " << (getIsBorrowed() ? "Loaned" : "Available")
        << "\n";
}

void BoardGame::printAvailable() {
    if (getIsBorrowed()) return;
    else print();
}

bool BoardGame::addReview(std::string reviewerID, std::string reviewBody, int rating) {
    return reviewList.add(reviewerID, reviewBody, rating);
}

void BoardGame::printReviews(MemberDictionary& members) {
    reviewList.print(members);
}

bool BoardGame::hasReviews() {
    return !reviewList.isEmpty();
}

bool BoardGame::printReviewed() {
    if (!hasReviews()) return false;
    print();
    return true;
}