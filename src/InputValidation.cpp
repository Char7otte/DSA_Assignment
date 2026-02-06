#include "InputValidation.h"

int getInt(std::string inputPrompt) {
    int x;
    std::string input;

    while (true) {
        std::cout << inputPrompt;
        std::getline(std::cin, input);
        try {
            x = std::stoi(input);
            if (x <= 0) throw std::runtime_error("");
            return x;
        }
        catch (...) {
            std::cout << "Invalid input. Please enter a positive number.\n";
        }
    }
}

std::string getString(std::string inputPrompt) {
    std::string input;

    while (true) {
        std::cout << inputPrompt;
        std::getline(std::cin, input);

        if (!input.empty()) {
            return input;
        }
        std::cout << "Game name cannot be empty.\n";
    }
}