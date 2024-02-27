#ifndef MY_Inventory
#define MY_Inventory

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Inventory
{
private:
    int gold;
    int ingredients;
    vector<int> cookware;
    vector<int> weapons;
    vector<int> treasures;
    vector<int> armor;

public:
    Inventory(); // default constructor

    bool differentWeapons(); // finds the ammount of different weapons possessed by the party

    void getRiddle(int riddleNum); // gets a riddle based on the number given

    string getRiddleAnswer(int riddleNum); // gets the answer to the corresponding riddle number

    int getArmor(); // gets total armor

    void setPot(int pots_); // sets pots to desired ammount

    void setPan(int pans_); // sets pans to desired ammount

    void setCauldron(int cauldrons_); // sets cauldrons to desired ammount

    int getArmorAt(int partyNumber); // sets armor to desired ammount

    int getIngredients(); // gets total ingredients

    void showInventory(); // shows the current inventory

    int getPan(); // gets number of pans

    int getPot(); // gets number of pots

    int getCauldron(); // gets number of cauldrons

    void setGold(int gold_); // sets gold

    int getGold(); // gets gold

    int setIngredients(int ingredients_); // sets ingredients

    int setArmor(int armor); // sets armor

    int buyPan(int numPans); // adds pans and changes gold

    int buyPot(int numPots); // adds pots and changes gold

    int buyCauldron(int numCauldrons); // adds cauldrons and changes gold

    int buyClub(int numClubs); // adds clubs and changes gold

    int buySpear(int numSpears); // adds spears and changes gold

    int buyRapier(int numRapiers); // adds rapiers and changes gold

    int getClub(); // gets clubs

    int getSpear(); // gets spears

    int getRapier(); // gets rapiers

    int getAxe(); // gets axes

    int getSword(); // gets swords

    string getWeaponAt(int num); // retrieves the weapon name from the weapons vector

    int buyAxe(int numAxes); // adds axes and changes gold

    void setClub(int clubs); // sets clubs

    void setAxe(int axes); // sets axes

    void setSpear(int spears); // sets spears

    void setRapier(int rapiers); // sets rapiers

    void setSword(int swords); // sets swords

    int buyLongsword(int numLongswords); // adds swords and changes gold

    void startingMerchant(); // displays starting merchant menu

    int sellRings(int numRings); // sells rings for gold

    int sellNecklace(int numNecklaces); // sells necklaces for gold

    int sellBracelet(int numBracelets); // sells bracelets for gold

    int sellCirclet(int numCirclets); // sells circlets for gold

    int sellGoblet(int numGoblets); // sells goblets for gold

    void addRing(int numRings); // adds rings

    void addNecklace(int numNecklaces); // adds necklaces

    void addBracelet(int numBracelets); // adds bracelets

    void addCirclet(int numCirclets); // adds circlets

    void addGoblet(int numGoblets); // adds goblets

    void merchantMainMenu(); // displays the main merchant menu

    int getWeaponCount(); // gets total weapons
};

#endif
