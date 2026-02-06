#pragma once

#include "GameDictionary.h"
#include "MemberDictionary.h"

bool adminDashboard(GameDictionary& games, MemberDictionary& members);
void createAndAddGameMenu(GameDictionary& gameDict);
void deleteGameMenu(GameDictionary& games);
void createMemberMenu(MemberDictionary& members);