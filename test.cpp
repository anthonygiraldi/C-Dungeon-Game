#include "status.cpp"
#include "inventory.cpp"
#include "map.cpp"
#include "party.cpp"
#include "monster.cpp"
#include <iostream>

using namespace std;

void statusUpdate(Inventory playerInventory, Status playerStatus, Map myMap, Party myParty)
{
    playerStatus.getStatus();
    playerInventory.showInventory();
    myParty.displayParty();
    cout << endl;
    myMap.displayMap();
}

int main()
{
    Inventory myInventory = Inventory();
    Status playerStatus = Status();
    Map myMap = Map();
    Party myParty = Party();
    Monsters myMonsters = Monsters();
    myMonsters.getMonsterOfLevel("1");

    myInventory.setArmor(5);

    int result = myInventory.getArmor();

    cout << result;

    myParty.setPartyNames();
    myParty.setMemberDead(0);
    statusUpdate(myInventory, playerStatus, myMap, myParty);

    myInventory.setArmor(5);
    playerStatus.setAngerLevel(10);

    statusUpdate(myInventory, playerStatus, myMap, myParty);

    myInventory.merchantMainMenu();

    return 0;
}