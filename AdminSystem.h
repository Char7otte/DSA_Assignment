#pragma once

void createAndAddGameMenu(GameDictionary& gameDict) {
    cout << "\n===== Add New Board Game =====\n";
    string id, name;
    int minPlayers, maxPlayers, minPlayTime, maxPlayTime, yearPublished;

    // --- Input: Game ID ---
    while (true) {
        cout << "Enter Game ID (e.g., G004): ";
        cin >> id;
        if (id.empty()) {
            cout << "Game ID cannot be empty.\n";
            continue;
        }
        if (gameDict.contains(id)) {
            cout << "This Game ID already exists. Please enter a different ID.\n";
            continue;
        }
        break;
    }

    // clear newline before getline
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // --- Input: Game Name ---
    while (true) {
        cout << "Enter Game Name: ";
        getline(cin, name);

        if (name.empty()) {
            cout << "Game name cannot be empty.\n";
            continue;
        }
        break;
    }

    // --- Numeric inputs with basic validation ---
    auto readInt = [](const string& prompt) {
        int x;
        while (true) {
            cout << prompt;
            if (cin >> x) return x;

            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    };

    minPlayers = readInt("Enter Min Players: ");
    maxPlayers = readInt("Enter Max Players: ");
    while (maxPlayers < minPlayers) {
        cout << "Max Players cannot be less than Min Players.\n";
        maxPlayers = readInt("Enter Max Players again: ");
    }

    minPlayTime = readInt("Enter Min Play Time (minutes): ");
    maxPlayTime = readInt("Enter Max Play Time (minutes): ");
    while (maxPlayTime < minPlayTime) {
        cout << "Max Play Time cannot be less than Min Play Time.\n";
        maxPlayTime = readInt("Enter Max Play Time again: ");
    }

    yearPublished = readInt("Enter Year Published: ");

    // --- Create and add ---
    BoardGame newGame(id, name, minPlayers, maxPlayers, minPlayTime, maxPlayTime, yearPublished);

    if (gameDict.add(id, newGame)) {
        cout << "\n Game added successfully!\n";
    } else {
        cout << "\n Failed to add game (duplicate key or other issue).\n";
    }
    cout << "==============================\n";
}

void deleteGameMenu(GameDictionary& gameDict) {
    cout << "\n===== Delete Board Game =====\n";
    gameDict.print();
    cout << "Enter Game ID to delete (e.g., G001): ";

    string id;
    cin >> id;
    BoardGame* game = gameDict.get(id);
    if (game == nullptr) {
        cout << "Game ID " << id << " not found. Nothing deleted.\n";

    }else {
        if (game->checkIsBorrowed()) {
            cout << "Game: " << game->getName() << " has been borrowed by other member.\n";
        }else {
            gameDict.remove(id);
            cout << "Game deleted successfully!\n";
        }
    }
    cout << "=============================\n";
}

void createMemberMenu(MemberDictionary& memberDict) {
    std::cout << "\n===== Create Member =====\n";

    std::string memberId;
    std::string memberName;

    // Member ID (no spaces)
    while (true) {
        std::cout << "Enter Member ID (e.g., M001): ";
        std::cin >> memberId;

        if (memberId.empty()) {
            std::cout << "Member ID cannot be empty.\n";
            continue;
        }

        // If you have containsMember(), use it:
        if (memberDict.containsMember(memberId)) {
            std::cout << "This Member ID already exists.\n";
            continue;
        }

        break;
    }

    // clear newline before getline
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Member name (can contain spaces)
    while (true) {
        std::cout << "Enter Member Name: ";
        std::getline(std::cin, memberName);

        if (memberName.empty()) {
            std::cout << "Member name cannot be empty.\n";
            continue;
        }
        break;
    }

    // Create and add
    Member member(memberId, memberName);

    // Your required call style:
    // memberDict.addMember("M001", member);
    // but since memberId is the key, use:
    bool ok = memberDict.addMember(memberId, member);

    if (ok) {
        std::cout << "Member " << memberId << " created successfully.\n";
    } else {
        std::cout << "Failed to create member (duplicate ID or other issue).\n";
    }

    std::cout << "=========================\n";
}

void adminMenu(GameDictionary& gameDict, MemberDictionary& memberDict, MasterHistoryLog& historyList) {
    int choice;

    while (true) {
        std::cout << "\n========= Admin Menu =========\n";
        std::cout << "1) Add Game\n";
        std::cout << "2) Delete Game\n";
        std::cout << "3) View All Games\n";
        std::cout << "4) Create Member\n";
        std::cout << "5) Summary of All Borrowing Records\n";
        std::cout << "6) Summary of Unreturned Games\n";
        std::cout << "0) Logout\n";
        std::cout << "Choose: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        if (choice == 1) {
            createAndAddGameMenu(gameDict);
        } else if (choice == 2) {
            deleteGameMenu(gameDict);
        } else if (choice == 3) {
            gameDict.print();
        } else if (choice == 4) {
            createMemberMenu(memberDict);
        } else if (choice == 5) {
            historyList.printAll();
        } else if (choice == 6) {
            historyList.printUnreturned();
        } else if (choice == 0) {
            std::cout << "Logging out...\n";
            break;
        } else {
            std::cout << "Invalid option.\n";
        }
    }
}
