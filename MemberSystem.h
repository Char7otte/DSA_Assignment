//
// Created by gongy on 7/2/2026.
//
#include "utility.h""
void memberBorrowMenu(GameDictionary& gameDict, Member& selectedMember, MasterHistoryLog& historyList) {
    cout << "\n===== Borrow Game =====\n";

    // Show all games first
    gameDict.print();

    while (true) {
        cout << "\nEnter Game ID to borrow (or 0 to cancel): ";
        string gameId;
        cin >> gameId;

        if (gameId == "0") {
            cout << "Cancelled.\n";
            return;
        }

        // Retrieve game (pointer)
        BoardGame* game = gameDict.get(gameId);
        if (game == nullptr) {
            cout << "Game ID not found. Please try again.\n";
            continue;
        }

        // Check if already borrowed
        if (game->checkIsBorrowed()) {
            cout << "⚠️ This game is already borrowed. Please choose another.\n";
            continue;
        }

        string today = getCurrentDate();

        // ✅ Member borrows (Member will call game.borrowGame internally)
        bool memberOk = selectedMember.borrowGame(*game, today);

        if (!memberOk) {
            cout << "Borrow failed unexpectedly.\n";
            return;
        }

        // ✅ Log history AFTER successful borrow
        bool logOk = historyList.add(*game, selectedMember, today);
        if (!logOk) {
            cout << "Borrowed successfully, but failed to log history.\n";
        }

        cout << "Borrow successful!\n";
        cout << selectedMember.getName() << " borrowed " << gameId
             << " on " << today << "\n";
        return;
    }
}

void memberReturnMenu(GameDictionary& gameDict, Member& selectedMember, MasterHistoryLog& historyList) {
    cout << "\n===== Return Game =====\n";

    // 1) Show unreturned games from this member
    selectedMember.printUnreturnedGames();

    while (true) {
        cout << "\nEnter Game ID to return (or 0 to cancel): ";
        string gameId;
        cin >> gameId;

        if (gameId == "0") {
            cout << "Cancelled.\n";
            return;
        }

        // 2) Retrieve game from dictionary
        BoardGame* game = gameDict.get(gameId);
        if (game == nullptr) {
            cout << "Game ID not found. Please try again.\n";
            continue;
        }

        // 3) Check global game status first (fast feedback)
        if (!game->checkIsBorrowed()) {
            cout << "This game is not currently borrowed (already returned).\n";
            continue;
        }

        string today = getCurrentDate();

        // ✅ Member returns (Member will call game.returnGame internally)
        bool memberOk = selectedMember.returnGame(*game, today);

        if (!memberOk) {
            cout << "Return failed: This game is not currently borrowed by you.\n";
            continue;
        }

        // ✅ Update master history log
        bool logOk = historyList.markReturned(today, gameId);
        if (!logOk) {
            cout << "Returned, but history record not found to update.\n";
        }

        cout << "Return successful!\n";
        cout << "You returned Game " << gameId << " on " << today << "\n";
        return;
    }
}

void memberAddReviewMenu(GameDictionary& gameDict, Member& selectedMember) {
    cout << "\n===== Add Review =====\n";

    // 1) Show all games
    gameDict.print();

    while (true) {
        cout << "\nEnter Game ID to review (or 0 to cancel): ";
        string gameId;
        cin >> gameId;

        if (gameId == "0") {
            cout << "Cancelled.\n";
            return;
        }

        // 2) Retrieve game
        BoardGame* game = gameDict.get(gameId);
        if (game == nullptr) {
            cout << "Game ID not found. Please try again.\n";
            continue;
        }

        // 3) Get rating (1-10)
        int rating;
        while (true) {
            cout << "Enter rating (1-10): ";
            cin >> rating;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";
                continue;
            }

            if (rating < 1 || rating > 10) {
                cout << "Rating must be between 1 and 10.\n";
                continue;
            }

            // clear newline before getline for review text
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }

        // 4) Get review text
        string reviewText;
        while (true) {
            cout << "Enter review text: ";
            getline(cin, reviewText);

            if (reviewText.empty()) {
                cout << "Review text cannot be empty.\n";
                continue;
            }
            break;
        }

        // 5) Add review into game reviewHistory
        string today = getCurrentDate();

        bool ok = game->addReview(
            selectedMember.getID(),
            selectedMember.getName(),
            today,
            reviewText,
            rating
        );

        if (!ok) {
            cout << "Failed to add review.\n";
            return;
        }

        cout << "Review added successfully!\n";
        cout << selectedMember.getName() << " reviewed " << game->getName()
             << " (" << gameId << ") on " << today
             << " with rating " << rating << "/10.\n";

        return;
    }
}

void memberViewReviewMenu(GameDictionary& gameDict) {
    cout << "\n===== View Game Reviews =====\n";

    // 1) Show all games
    gameDict.print();

    while (true) {
        cout << "\nEnter Game ID to view reviews (or 0 to cancel): ";
        string gameId;
        cin >> gameId;

        if (gameId == "0") {
            cout << "Cancelled.\n";
            return;
        }

        // 2) Retrieve game
        BoardGame* game = gameDict.get(gameId);
        if (game == nullptr) {
            cout << "Game ID not found. Please try again.\n";
            continue;
        }

        // 3) Display reviews
        game->displayReviews();
        return;
    }
}


void memberMenu(GameDictionary& gameDict,
                MemberDictionary& memberDict,
                MasterHistoryLog& historyList) {
    cout << "\n======= Member Login =======\n";
    cout << "Enter your Member ID (e.g., M001) (or 0 to cancel): ";

    string memberId;
    cin >> memberId;

    if (memberId == "0") {
        cout << "Cancelled.\n";
        return;
    }

    Member* selectedMemberPtr = memberDict.getMember(memberId);
    if (selectedMemberPtr == nullptr) {
        cout << "Member ID not found.\n";
        return;
    }

    Member& selectedMember = *selectedMemberPtr;

    cout << "Welcome, " << selectedMember.getName()
         << " (" << selectedMember.getID() << ")\n";

    int choice;

    while (true) {
        cout << "\n========= Member Menu =========\n";
        cout << "1) Borrow Game\n";
        cout << "2) Return Game\n";
        cout << "3) Summary of Games Borrowed\n";
        cout << "4) Add Review\n";          // ✅ NEW
        cout << "5) View Game Reviews\n";   // ✅ NEW
        cout << "0) Logout\n";
        cout << "Choose: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input.\n";
            continue;
        }

        if (choice == 1) {
            memberBorrowMenu(gameDict, selectedMember, historyList);
        }
        else if (choice == 2) {
            memberReturnMenu(gameDict, selectedMember, historyList);
        }
        else if (choice == 3) {
            selectedMember.printBorrowHistory();
        }
        else if (choice == 4) {
            memberAddReviewMenu(gameDict, selectedMember);   // ✅ NEW
        }
        else if (choice == 5) {
            memberViewReviewMenu(gameDict);                  // ✅ NEW
        }
        else if (choice == 0) {
            cout << "Logging out...\n";
            return;
        }
        else {
            cout << "Invalid option.\n";
        }
    }
}
