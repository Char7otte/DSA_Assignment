#include "BoardGame.h"

// Constructor
BoardGame::BoardGame(string id, string name, int minP, int maxP,
                     int minTime, int maxTime, int year)
    : id(id), name(name), minPlayers(minP), maxPlayers(maxP),
      minPlayTime(minTime), maxPlayTime(maxTime),
      yearPublished(year), isBorrowed(false),
      borrowHistory(10), reviewHistory(10) {}

string BoardGame::getID() const { return id; }
string BoardGame::getName() const { return name; }

bool BoardGame::borrowGame(string borrowerId, string borrowerName, string date) {
    if (isBorrowed) {
        cout << "Game is already borrowed." << endl;
        return false;
    }

    UsageRecord newRecord{ borrowerId, borrowerName, date, "" };

    borrowHistory.add(newRecord); // always true now (auto-resize)
    isBorrowed = true;
    return true;
}

bool BoardGame::returnGame(string returnDate) {
    if (!isBorrowed) {
        cout << "Game is not currently borrowed." << endl;
        return false;
    }

    if (borrowHistory.getLength() == 0) {
        cout << "Error: no borrow history found." << endl;
        return false;
    }

    int lastIndex = borrowHistory.getLength() - 1;
    borrowHistory.getRef(lastIndex).returnDate = returnDate;

    isBorrowed = false;
    cout << "Game returned successfully!" << endl;
    return true;
}

bool BoardGame::addReview(string reviewerId,
                          string reviewerName,
                          string reviewDate,
                          string reviewText,
                          int rating) {
    // Optional validation
    if (rating < 1 || rating > 10) {
        cout << "Rating must be between 1 and 10.\n";
        return false;
    }

    Review newReview{
        reviewerId,
        reviewerName,
        reviewDate,
        reviewText,
        rating
    };

    // Use List.add()
    if (!reviewHistory.add(newReview)) {
        cout << "Failed to add review.\n";
        return false;
    }

    // cout << "Review added successfully.\n";
    return true;
}

void BoardGame::displayReviews() {
    cout << "\n" << string(90, '=') << "\n";
    cout << "REVIEWS FOR GAME: " << name << " (" << id << ")\n";
    cout << string(90, '=') << "\n";

    if (reviewHistory.getLength() == 0) {
        cout << "(No reviews yet.)\n";
        cout << string(90, '=') << "\n";
        return;
    }

    // Header
    cout << left
         << setw(30) << "REVIEWER NAME"
         << setw(20) << "REVIEW DATE"
         << setw(10) << "RATING"
         << "\n";

    cout << string(90, '-') << "\n";

    // Each review
    for (int i = 0; i < reviewHistory.getLength(); i++) {
        const Review& r = reviewHistory.getRef(i);

        // First line (meta info)
        cout << left
             << setw(30) << r.reviewerName
             << setw(20) << r.reviewDate
             << setw(10) << (to_string(r.rating) + "/5")
             << "\n";

        // Second line (review text)
        cout << setw(30) << " "
             << r.reviewText << "\n";

        cout << string(90, '-') << "\n";
    }

    cout << string(90, '=') << "\n";
}



bool BoardGame::checkIsBorrowed() const {
    return isBorrowed;
}

void BoardGame::printInfo() const {
    cout << "[ id= " << id
         << ", name= \"" << name << "\""
         << ", players= " << minPlayers << "-" << maxPlayers
         << ", playtime= " << minPlayTime << "-" << maxPlayTime
         << ", year= " << yearPublished
         << ", borrowed= " << (isBorrowed ? "true" : "false")
         << " ]" << endl;
}
