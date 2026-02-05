#pragma once

#include "Dictionary.h"

class GameDictionary: public Dictionary
{
public:
    GameDictionary();

    void print() override;
};
