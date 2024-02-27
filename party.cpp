#include "party.h"

using namespace std;

Party::Party()
{
    for (int i = 0; i < PARTY_SIZE; i++) // sets the party names to empty strings
    {
        partyNames[i] = "";
    }

    for (int i = 0; i < PARTY_SIZE; i++) // sets the starting fullness to 50
    {
        fullness[i] = startingFullness;
    }
}

bool Party::setPartyNames() // function to set the names of each party member using user input
{
    string partyMember1;
    string partyMember2;
    string partyMember3;
    string partyMember4;
    string partyMember5;
    cout << "Please enter your name, followed by the names of your other 4 party members" << endl;
    cin >> partyMember1;
    setPartyName(0, partyMember1);
    cin >> partyMember2;
    setPartyName(1, partyMember2);
    cin >> partyMember3;
    setPartyName(2, partyMember3);
    cin >> partyMember4;
    setPartyName(3, partyMember4);
    cin >> partyMember5;
    setPartyName(4, partyMember5);
    return true;
}

void Party::displayParty() // displays the party names and their fullness
{
    cout << "| PARTY       |" << endl;
    cout << "+-------------+" << endl;
    cout << "| " << getPartyName(0) << " | Fullness: " << getFullness(0) << endl;
    cout << "| " << getPartyName(1) << " | Fullness: " << getFullness(1) << endl;
    cout << "| " << getPartyName(2) << " | Fullness: " << getFullness(2) << endl;
    cout << "| " << getPartyName(3) << " | Fullness: " << getFullness(3) << endl;
    cout << "| " << getPartyName(4) << " | Fullness: " << getFullness(4) << endl;
    cout << "+-------------+" << endl;
}

int Party::getFullness(int partyNumber) // returns to fullness of one party member
{
    return fullness[partyNumber];
}

bool Party::setFullness(int partyNumber, int newFullness) // sets the fullness of a party member
{
    if (getFullness(partyNumber) > 50 || getFullness(partyNumber) <= 0) // checks the the member isn't dead
    {
        return false;
    }
    else
    {
        fullness[partyNumber] = newFullness;
        return true;
    }
}

string Party::getPartyName(int partyNum) // returns the name of a party member
{
    return partyNames[partyNum];
}

bool Party::setPartyName(int partyNumber, string name) // sets the name of a party member
{
    partyNames[partyNumber] = name;
    return true;
}

bool Party::setMemberTrapped(int partyNumber) // sets a party member to trapped
{
    if (partyNames[partyNumber] == "Dead") // if they are already dead, return false
    {
        return false;
    }
    else
    {
        setPartyName(partyNumber, "Trapped");
        setFullness(partyNumber, 0);
        return true;
    }
}

int Party::getMembersDead() // return the total number of dead members
{
    return membersDead;
}

bool Party::isDead(int partyNumber) // sets a party member to dead if the fullness if at or below 0
{
    if (getFullness(partyNumber) <= 0)
    {
        setPartyName(partyNumber, "Dead");
        membersDead++;
        return true;
    }
    else
    {
        return false;
    }
}

bool Party::setMemberDead(int partyNumber) // sets the party member as dead
{
    if (partyNames[partyNumber] == "Dead")
    {
        return false;
    }
    else
    {
        setPartyName(partyNumber, "Dead");
        membersDead++;
        setFullness(partyNumber, 0);
        return true;
    }
}