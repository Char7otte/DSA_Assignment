#include<string>
#include<iostream>
using namespace std;

struct Member {
    string id;
    string name;

};

typedef string KeyType;    // dictionary key (e.g., string ID)
typedef Member ItemType; // stored item (game info)

struct Node
{
    KeyType  key;   // search key
    ItemType item;	// data item
    Node     *next;	// pointer pointing to next item
};

class MemberDictionary
{
private:
    static constexpr int MAX_SIZE = 101;
    Node *items[MAX_SIZE];
    int  size;			// number of items in the Dictionary

public:
    // constructor
    MemberDictionary();

    // destructor
    ~MemberDictionary();

    int hash(KeyType key);

    // add a new item with the specified key to the Dictionary
    bool addMember(KeyType newKey, ItemType newItem);

    // remove an item with the specified key in the Dictionary
    void removeMember(KeyType key);

    // get an item with the specified key in the Dictionary (retrieve)
    ItemType* getMember(KeyType key);

    // check if a specified key is in the Dictionary
    bool contains(KeyType key);

    // check if the Dictionary is empty
    bool isEmpty();

    // check the size of the Dictionary
    int getLength();

    //------------------- Other useful functions -----------------

    // display the items in the Dictionary
    void print();

    //void print(KeyType key);
};
