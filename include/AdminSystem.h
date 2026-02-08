#pragma once

#include "BorrowList.h"
#include "GameDictionary.h"
#include "MemberDictionary.h"

bool adminDashboard(GameDictionary& games, MemberDictionary& members, BorrowList& loans);
void createAndAddGameMenu(GameDictionary& gameDict);
void deleteGameMenu(GameDictionary& games);
void createMemberMenu(MemberDictionary& members);
void displayHistory(GameDictionary& games, MemberDictionary& members, BorrowList& loans);
void displayHistoryUnreturned(GameDictionary& games, MemberDictionary& members, BorrowList& loans);