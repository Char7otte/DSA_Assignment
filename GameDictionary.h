#include<string>
#include<iostream>
using namespace std;


const int MAX_SIZE = 101;
typedef string ItemType;

struct GameInfo {
    int id;                 // auto-generated unique key

    string name;
    int minPlayers;
    int maxPlayers;
    int minPlayTime;
    int maxPlayTime;
    int yearPublished;

    bool isBorrowed = false;
    string borrowedBy = "";
    string borrowDate = "";
};

typedef GameInfo KeyType;
struct Node
{
    KeyType  key;   // search key
    ItemType item;	// data item
    Node     *next;	// pointer pointing to next item
};

class GameDictionary
{
private:
    Node *items[MAX_SIZE];
    int  size;			// number of items in the Dictionary

public:
    // constructor
    GameDictionary();

    // destructor
    ~GameDictionary();

    int hash(KeyType key);

    // add a new item with the specified key to the Dictionary
    bool add(KeyType newKey, ItemType newItem);

    // remove an item with the specified key in the Dictionary
    void remove(KeyType key);

    // get an item with the specified key in the Dictionary (retrieve)
    ItemType get(KeyType key);

    // check if a specified key is in the Dictionary
    bool contains(KeyType key);

    // check if the Dictionary is empty
    bool isEmpty();

    // check the size of the Dictionary
    int getLength();

    //------------------- Other useful functions -----------------

    // display the items in the Dictionary
    void print();
};
