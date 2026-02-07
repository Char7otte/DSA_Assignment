#pragma once

#include "GameDictionary.h"
#include "MemberDictionary.h"

#include<string>

void readGameFile(const std::string& fileName, GameDictionary& gameDict);

void readMemberFile(const std::string& fileName, MemberDictionary& memberDict);
