#define _CRT_SECURE_NO_WARNINGS

#include "InputValidation.h"

#include <corecrt.h>
#include <ctime>
#include <iostream>
#include <stdexcept>
#include <string>

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
        std::cout << "Input cannot be empty.\n";
    }
}

std::string getTodayDate() {
    time_t now = time(nullptr);
    struct tm* localTime = localtime(&now);
    std::string year = std::to_string(localTime->tm_year + 1900);
    std::string month = std::to_string(localTime->tm_mon + 1);
    std::string monthDay = std::to_string(localTime->tm_mday);
    std::string date = year + "-" + month + "-" + monthDay;
    return date;
}