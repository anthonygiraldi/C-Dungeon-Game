#ifndef MY_Party
#define MY_Party

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Party
{
private:
    static const int PARTY_SIZE = 50;       // total party size
    int fullness[PARTY_SIZE];               // fullness array
    string partyNames[PARTY_SIZE];          // party names array
    static const int startingFullness = 50; // starting fullness
    int membersDead;

public:
    Party(); // default constructor

    int getMembersDead(); // gets dead members

    bool setPartyNames(); // sets the party names

    bool setMemberTrapped(int partyNum); // sets members as trapped

    void displayParty(); // displays the party

    int getFullness(int partyNumber); // gets the fullness of a member

    string getPartyName(int partyNumber); // gets the name of a member

    bool setPartyName(int partyNumber, string name); // sets the name of one member

    bool setFullness(int partyNumber, int fullness); // sets the fullness of one member

    bool setMemberDead(int partyNumber); // sets a member to dead

    bool isDead(int partyNumber); // sets a member to dead if fullness if 0 or less
};

#endif
