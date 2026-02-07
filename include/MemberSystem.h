#pragma once

#include "GameDictionary.h"
#include "Member.h"
#include "MasterHistoryLog.h"

bool memberDashboard(GameDictionary& games, Member& member, MasterHistoryLog& masterLog);
void memberBorrowMenu(GameDictionary& games, Member& borrower, MasterHistoryLog& masterLog);
