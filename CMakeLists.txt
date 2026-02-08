cmake_minimum_required(VERSION 4.0)
project(DSA_Assigment_testing CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# Source and header files
set(SOURCES
        src/DSA_Assignment.cpp
        src/AdminSystem.cpp
        src/BoardGame.cpp
        src/FileUtilities.cpp
        src/GameDictionary.cpp
        src/InputValidation.cpp
        src/Item.cpp
        src/MasterHistoryLog.cpp
        src/Member.cpp
        src/MemberDictionary.cpp
        src/MemberSystem.cpp)

set(HEADERS
        include/AdminSystem.h
        include/BoardGame.h
        include/Dictionary.h
        include/FileUtilities.h
        include/GameDictionary.h
        include/InputValidation.h
        include/Item.h
        include/MasterHistoryLog.h
        include/Member.h
        include/MemberDictionary.h
        include/MemberSystem.h)

add_executable(DSA_Assigment_testing ${SOURCES} ${HEADERS})
