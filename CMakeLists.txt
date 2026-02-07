cmake_minimum_required(VERSION 4.0)
project(DSA_Assignment)

set(CMAKE_CXX_STANDARD 14)

add_executable(DSA_Assignment
        DSA_Assignment.cpp
        GameDictionary.cpp
        GameDictionary.h
        BoardGame.cpp
        BoardGame.h
        MemeberDictionary.cpp
        MemeberDictionary.h
        Member.cpp
        Member.h
        MasterHistoryLog.cpp
        MasterHistoryLog.h
        List.h
        MasterHistoryLog.cpp
        MasterHistoryLog.cpp
        List.h)

# Provide source and binary directories to the code for robust resource lookup
add_definitions(-DSOURCE_DIR="${CMAKE_CURRENT_SOURCE_DIR}")
add_definitions(-DBINARY_DIR="${CMAKE_CURRENT_BINARY_DIR}")

# Ensure games.csv is available next to the built executable
add_custom_command(TARGET DSA_Assignment POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/games.csv"
        "$<TARGET_FILE_DIR:DSA_Assignment>/games.csv")
