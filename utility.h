//
// Created by gongy on 7/2/2026.
//
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
std::string getCurrentDate() {
    // 1. Get the current system time
    auto now = std::chrono::system_clock::now();

    // 2. Convert to a time_t object (standard C time)
    std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

    // 3. Convert to local time structure
    std::tm* localTime = std::localtime(&currentTime);

    // 4. Use stringstream to format it (YYYY-MM-DD)
    std::stringstream ss;
    ss << std::put_time(localTime, "%Y-%m-%d");

    return ss.str();
}