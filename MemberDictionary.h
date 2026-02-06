#pragma once

#include "Dictionary.h"
#include "Member.h"

class MemberDictionary: public Dictionary<Member*>
{
public:
    MemberDictionary();

    void print() override;
 };
