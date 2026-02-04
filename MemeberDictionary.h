#include<string>
#include<iostream>
#include "Member.h"
using namespace std;



typedef string KeyType;    // dictionary key (e.g., string ID)
typedef Member MemberItemType; // stored item (game info)

struct MemberNode
{
    KeyType  key;   // search key
    MemberItemType item;	// data item
    MemberNode     *next;	// pointer pointing to next item
};

class MemberDictionary
{
private:
    static constexpr int MAX_SIZE = 101;
    MemberNode *items[MAX_SIZE];
    int  size;			// number of items in the Dictionary

public:
    // constructor
    MemberDictionary();

    // destructor
    ~MemberDictionary();

    int hash(KeyType key);

    // add a new item with the specified key to the Dictionary
    bool addMember(KeyType newKey, MemberItemType newItem);

    // remove an item with the specified key in the Dictionary
    void removeMember(KeyType key);

    // get an item with the specified key in the Dictionary (retrieve)
    MemberItemType* getMember(KeyType key);

    // check if a specified key is in the Dictionary
    bool containsMember(KeyType key);

    // check if the Dictionary is empty
    bool isEmpty();

    // check the size of the Dictionary
    int getLength();

    //------------------- Other useful functions -----------------

    // display the items in the Dictionary
    void print();

    //void print(KeyType key);
};
