#pragma once

#include "GameDictionary.h"
#include "Member.h"
#include "BorrowList.h"

bool memberDashboard(GameDictionary& games, Member& member, BorrowList& loans);
void memberBorrowMenu(GameDictionary& games, Member& borrower, BorrowList& loans);
void memberReturnMenu(GameDictionary& games, Member& returner, BorrowList& loans);