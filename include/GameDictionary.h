#pragma once

#include "Dictionary.h"
#include "BoardGame.h"

class GameDictionary: public Dictionary<BoardGame*>
{
public:
    GameDictionary();

    void print() override;
    void printAvailable();
};
