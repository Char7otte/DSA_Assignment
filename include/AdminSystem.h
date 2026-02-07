#pragma once

#include "GameDictionary.h"
#include "MemberDictionary.h"
#include "MasterHistoryLog.h"

bool adminDashboard(GameDictionary& games, MemberDictionary& members, MasterHistoryLog& masterLog);
void createAndAddGameMenu(GameDictionary& gameDict);
void deleteGameMenu(GameDictionary& games);
void createMemberMenu(MemberDictionary& members);