#pragma once

#include "GameDictionary.h"
#include "Member.h"
#include "BorrowList.h"

bool memberDashboard(GameDictionary& games, MemberDictionary& members, BorrowList& loans, Member& member);
void memberBorrowMenu(GameDictionary& games, Member& borrower, BorrowList& loans);
void memberReturnMenu(GameDictionary& games, Member& returner, BorrowList& loans);
void getBorrowHistory(GameDictionary& games, MemberDictionary& members, BorrowList& loans, std::string borrowerID);