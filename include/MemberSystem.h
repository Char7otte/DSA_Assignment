#pragma once

#include "BorrowList.h"
#include "GameDictionary.h"
#include "Member.h"
#include "MemberDictionary.h"

#include <string>

bool memberDashboard(GameDictionary& games, MemberDictionary& members, BorrowList& loans, Member& member);
void memberBorrowMenu(GameDictionary& games, Member& borrower, BorrowList& loans);
void memberReturnMenu(GameDictionary& games, Member& returner, BorrowList& loans);
void getBorrowHistory(GameDictionary& games, MemberDictionary& members, BorrowList& loans, std::string borrowerID);
void leaveReview(GameDictionary& games, Member& member);
void viewReviews(GameDictionary& games, MemberDictionary& members);
void logMatch(GameDictionary& games, std::string memberID);
void printMatches(GameDictionary& games);