#pragma once

#include "Member.h"
#include "Dictionary.h"

class MemberDictionary: public Dictionary<Member*>
{
public:
    MemberDictionary();

    void print() override;
 };
