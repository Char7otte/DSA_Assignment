#include <string>
#include<array>

#include "Item.h"

struct UsageLog: public DateLog {
    std::string borrowerId = "N/A";
    std::string borrowerName = "N/A";
};

class BoardGame: public Item {
private:
    int minPlayers;
    int maxPlayers;
    int minPlaytime;
    int maxPlaytime;
    int yearPublished;
    bool isBorrowed;
    UsageLog borrowHistory[10] = {};
    int historyCount = 0;

public:
    BoardGame(const std::string id,
        const std::string name,
        const int minPlayers,
        const int maxPlayers,
        const int minPlaytime,
        const int maxPlaytime,
        const int yearPublished,
        const bool isBorrowed);

    //bool borrowGame(std::string borrowerId, std::string borrowerName, std::string date);
    //bool returnGame(std::string returnDate);

    //bool checkIsBorrowed();

    //UsageRecord getLastestBorrowRecord();

    //// // set the game to be borrowed
    //// void markAvailable(string borrowDate);
    ////
    //// // set the game to be returned
    //// void markBorrowed(string returnDate);

    //void printInfo() const;
    //void printBorrowHistory();
    //void checkIfBorrowedAndPrintLatest() const;
};
