#pragma once

#include "GameDictionary.h"
#include "MemberDictionary.h"
#include "BorrowList.h"

bool adminDashboard(GameDictionary& games, MemberDictionary& members, BorrowList& loans);
void createAndAddGameMenu(GameDictionary& gameDict);
void deleteGameMenu(GameDictionary& games);
void createMemberMenu(MemberDictionary& members);
void displayHistory(BorrowList& loans);