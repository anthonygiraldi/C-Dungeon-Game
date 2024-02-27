#include "inventory.h"
#include <string>
#include <iostream>

using namespace std;

Inventory::Inventory() // default constructor
{
    gold = 100;      // sets the starting gold to 100
    ingredients = 0; // sets the starting ingredients to 0

    int i = 0;
    while (i < 3) // fills the cookware vector with 0's
    {
        cookware.push_back(0);
        i++;
    }

    int j = 0;
    while (j < 5) // fills the weapons vector with 0's
    {
        weapons.push_back(0);
        j++;
    }

    int k = 0;
    while (k < 5) // fills the treasure vector with 0's
    {
        treasures.push_back(0);
        k++;
    }

    int l = 0;
    while (l < 5) // fills the armor vector with 0's
    {
        armor.push_back(0);
        l++;
    }
}

/*
Function to print out a riddle to the user
    - If(riddleNum == 1)
        - display riddle 1
        (repeats for all 5 riddles)
*/

void Inventory::getRiddle(int riddleNum)
{
    if (riddleNum == 1)
    {
        cout << "You measure my life in hours and I serve you by expiring. I'm quick when I'm thin and slow when I'm fat. The wind is my enemy. (single word, lowercase)" << endl;
    }
    if (riddleNum == 2)
    {
        cout << "I have cities, but no houses. I have mountains, but no trees. I have water, but no fish. What am I? (single word, lowercase)" << endl;
    }
    if (riddleNum == 3)
    {
        cout << "What is seen in the middle of March and April that can't be seen at the beginning or end of either month? (single word, lowercase)" << endl;
    }
    if (riddleNum == 4)
    {
        cout << "What English word has three consecutive double letters? (single word, lowercase)" << endl;
    }
    if (riddleNum == 5)
    {
        cout << "What disappears as soon as you say its name? (single word, lowercase)" << endl;
    }
}

/*
    Function to get the corresponding riddle answer
        - If riddle number is 1
            - Return riddle answer
            (repeats for all 5 riddles)
*/

string Inventory::getRiddleAnswer(int riddleNum)
{
    if (riddleNum == 1)
    {
        return "candle";
    }
    if (riddleNum == 2)
    {
        return "map";
    }
    if (riddleNum == 3)
    {
        return "r";
    }
    if (riddleNum == 4)
    {
        return "bookkeeper";
    }
    if (riddleNum == 5)
    {
        return "silence";
    }
    else
    {
        return "";
    }
}

/*
    Function to return the total ammount of armor in the armor vector
    For int i, when i < than the armor vector size
        - add that element to result
        - Return result
*/

int Inventory::getArmor()
{
    int result = 0;
    for (int i = 0; i < armor.size(); i++)
    {
        result += armor.at(i);
    }
    return result;
}

/*
    Function to get armor at a particular place in the armor vector
        - Return armor at the designated number
*/

int Inventory::getArmorAt(int partyNum)
{
    return armor.at(partyNum);
}

/*
Function to check if there is a weapon for every party member
    - Loop through the weapons vector
        - If a place in the weapons vector is 0, return false
    - If not, return true
*/

bool Inventory::differentWeapons()
{
    for (int i = 0; i < weapons.size(); i++)
    {
        if (weapons.at(i) == 0)
        {
            return false;
        }
    }
    return true;
}

string Inventory::getWeaponAt(int num)
{
    if (num == 0)
    {
        return "Stone Club";
    }
    if (num == 1)
    {
        return "Iron Spear";
    }
    if (num == 2)
    {
        return "(+1) Mythril Rapier";
    }
    if (num == 3)
    {
        return "(+2) Flaming Battle-Axe";
    }
    if (num == 4)
    {
        return " (+3) Vorpal Longsword";
    }
    else
    {
        return "";
    }
}

/*
Function that returns the rapier ammount
    - Return position 2 of the weapons vector
*/

int Inventory::getRapier()
{
    return weapons.at(2);
}

/*
Function that returns the axe ammount
    - Return position 3 of the weapons vector
*/

int Inventory::getAxe()
{
    return weapons.at(3);
}

/*
Function that returns the sword ammount
    - Return position 4 of the weapons vector
*/

int Inventory::getSword()
{
    return weapons.at(4);
}

/*
Function that returns the total ammount of weapons held by the party
    - Loop through the weapons vector
        - Anytime the vector element is greater than 0 increase the counter by 1
    - Return the counter
*/

int Inventory::getWeaponCount()
{
    int count = 0;
    for (int i = 0; i < 5; i++)
    {
        if (weapons.at(i) > 0)
        {
            count++;
        }
    }
    return count;
}

/*
Function to set the number of pots
    - Change cookware vector at position 0 to specified number of pots
*/

void Inventory::setPot(int pots_)
{
    cookware.at(0) = pots_;
}

/*
Function to set the number of pans
    - Change cookware vector at position 1 to specified number of pans
*/

void Inventory::setPan(int pans_)
{
    cookware.at(1) = pans_;
}

/*
Function to set the number of cauldrons
    - Change cookware vector at position 2 to specified number of cauldrons
*/

void Inventory::setCauldron(int cauldrons_)
{
    cookware.at(2) = cauldrons_;
}

/*
Function to get the number of pots
    - Return the value of cookware position 0
*/

int Inventory::getPot()
{
    return cookware.at(0);
}

/*
Function to get the number of pans
    - Return the value of cookware position 1
*/

int Inventory::getPan()
{
    return cookware.at(1);
}

/*
Function to get the number of cauldrons
    - Return the value of cookware position 2
*/

int Inventory::getCauldron()
{
    return cookware.at(2);
}

/*
Function to show the current inventory of the player
    - Print the inventory using the values from all the vectors
*/

void Inventory::showInventory()
{
    cout << "+-------------+" << endl;
    cout << "| INVENTORY   |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Gold        | " << gold << endl;
    cout << "| Ingredients | " << ingredients << " kg" << endl;
    cout << "| Cookware    | P: " << cookware.at(0) << " | F: " << cookware.at(1) << " | C: " << cookware.at(2) << endl;
    cout << "| Weapons     | C: " << weapons.at(0) << " | S: " << weapons.at(1) << " | R: " << weapons.at(2) << " | B: " << weapons.at(3) << " | L: " << weapons.at(4) << endl;
    cout << "| Armor       | " << getArmor() << endl;
    cout << "| Treasures   | R: " << treasures.at(0) << " | N: " << treasures.at(1) << " | B: " << treasures.at(2) << " | C: " << treasures.at(3) << " | G: " << treasures.at(4) << endl;
    cout << "+-------------+" << endl;
}

/*
Function to set the number of ingredients and change the gold
    - If the gold is less than the ammount of ingredients return -1 (the ingredients couldn't be purchased)
    - If the ingredients are less than 0, set ingredients to 0
    - Set gold to the new gold after ingredients are purchased
    - Set ingredients to new ingredients
    - Return 1
*/

int Inventory::setIngredients(int ingredients_)
{
    if (gold < ingredients_)
    {
        return -1;
    }

    ingredients = ingredients_;

    if (ingredients_ <= 0)
    {
        ingredients = 0;
    }

    gold = gold - ingredients_;

    return 1;
}

/*
Function to set the armor
    - If the armor times 5 is greater than the current gold return -1
    - Otherwise, gold equals the gold - the armor purchased times 5
    - Fill the array with 1's
    - Return 1
*/

int Inventory::setArmor(int armor_)
{
    if ((armor_ * 5) > gold)
    {
        return -1;
    }
    else
    {
        gold = gold - (5 * armor_);
        for (int i = 0; i < armor_; i++)
        {
            armor.push_back(1);
        }
        return 1;
    }
}

/*
Function to return ingredients
    - Returns the ingredients variable
*/

int Inventory::getIngredients()
{
    return ingredients;
}

/*
Function to buy pans based on number of pans
    - If the number of pans times ten is greater than the user's gold, return -1
    - Otherwise, gold = gold - number of pans times 10
    - Return 1
*/

int Inventory::buyPan(int numPans)
{
    if ((numPans * 10) > gold) // if the price of the items that are wished to be purchased are greater than the gold in the players inventory return -1
    {
        return -1;
    }
    else
    {
        gold = gold - (numPans * 10);
        cookware.at(1) = numPans;
        return 1;
    }
}

/*
Function to return gold
    - Return gold variable
*/

int Inventory::getGold()
{
    return gold;
}

/*
Function to set gold to specified ammount
    - Gold equals specified gold
*/

void Inventory::setGold(int gold_)
{
    gold = gold_;
}

/*
Function to buy pots based on specified number of pots
    - If number of pots times 2 is greater than gold return -1
    - Otherwise gold = gold - number of pots times 2
    - Return 1
*/

int Inventory::buyPot(int numPots)
{
    if ((numPots * 2) > gold)
    {
        return -1;
    }
    else
    {
        gold = gold - (numPots * 2);
        cookware.at(0) = numPots;
        return 1;
    }
}

/*
Function to buy cauldrons based on specified number of cauldrons
    - If number of cauldrons times 20 is greater than gold return -1
    - Otherwise gold = gold - number of cauldrons times 20
    - Return 1
*/

int Inventory::buyCauldron(int numCauldrons)
{
    if ((numCauldrons * 20) > gold) // if the price of the items that are wished to be purchased are greater than the gold in the players inventory return -1
    {
        return -1;
    }
    else
    {
        gold = gold - (numCauldrons * 20);
        cookware.at(2) = numCauldrons;
        return 1;
    }
}

/*
Function to buy clubs based on specified number of clubs
    - If number of clubs times 2 is greater than gold return -1
    - Otherwise gold = gold - number of clubs times 2
    - Return 1
*/

int Inventory::buyClub(int numClubs)
{
    if ((numClubs * 2) > gold)
    {
        return -1;
    }
    else
    {
        gold = gold - (numClubs * 2);
        weapons.at(0) = numClubs;
        return 1;
    }
}

/*
Function to buy spears based on specified number of spears
    - If number of spears times 2 is greater than gold return -1
    - Otherwise gold = gold - number of spears times 2
    - Return 1
*/

int Inventory::buySpear(int numSpears)
{
    if ((numSpears * 2) > gold)
    {
        return -1;
    }
    else
    {
        gold = gold - (numSpears * 2);
        weapons.at(1) = numSpears;
        return 1;
    }
}

void Inventory::setClub(int clubs)
{
    weapons.at(0) = clubs;
}

void Inventory::setSpear(int spears)
{
    weapons.at(1) = spears;
}

void Inventory::setRapier(int rapiers)
{
    weapons.at(2) = rapiers;
}

int Inventory::getClub()
{
    return weapons.at(0);
}

int Inventory::getSpear()
{
    return weapons.at(1);
}

void Inventory::setAxe(int axes)
{
    weapons.at(3) = axes;
}

void Inventory::setSword(int swords)
{
    weapons.at(4) = swords;
}

/*
Function to buy axes based on specified number of axes
    - If number of axes times 15 is greater than gold return -1
    - Otherwise gold = gold - number of axes times 15
    - Return 1
*/

int Inventory::buyAxe(int numAxes)
{
    if ((numAxes * 15) > gold)
    {
        return -1;
    }
    else
    {
        gold = gold - (numAxes * 15);
        weapons.at(3) = numAxes;
        return 1;
    }
}

/*
Function to buy rapier's based on specified number of rapier's
    - If number of rapier's times 5 is greater than gold return -1
    - Otherwise gold = gold - number of rapier's times 5
    - Return 1
*/

int Inventory::buyRapier(int numRapiers)
{
    if ((numRapiers * 5) > gold)
    {
        return -1;
    }
    else
    {
        gold = gold - (numRapiers * 5);
        weapons.at(2) = numRapiers;
        return 1;
    }
}

/*
Function to buy swords based on specified number of swords
    - If number of swords times 50 is greater than gold return -1
    - Otherwise gold = gold - number of swords times 50
    - Return 1
*/

int Inventory::buyLongsword(int numLongswords)
{
    if ((numLongswords * 50) > gold)
    {
        return -1;
    }
    else
    {
        gold = gold - (numLongswords * 50);
        weapons.at(4) = numLongswords;
        return 1;
    }
}

/*
Function to sell rings
    - If the number of rings is less than the rings possesed
        - Set number of rings to the new number of rings
        - Set gold to the new gold after rings are sold
        - Return 1
    - Otherwirse return -1
*/

int Inventory::sellRings(int numRings)
{
    if (numRings <= treasures.at(0))
    {
        treasures.at(0) = treasures.at(0) - numRings;
        gold = numRings * 10;
        return 1;
    }
    else
    {
        return -1;
    }
}

/*
Function to sell necklaces
    - If the number of necklaces is less than the necklaces possesed
        - Set number of necklaces to the new number of necklaces
        - Set gold to the new gold after necklaces are sold
        - Return 1
    - Otherwirse return -1
*/

int Inventory::sellNecklace(int numNecklaces)
{
    if (numNecklaces <= treasures.at(1))
    {
        treasures.at(1) = treasures.at(1) - numNecklaces;
        gold = numNecklaces * 20;
        return 1;
    }
    else
    {
        return -1;
    }
}

/*
Function to sell bracelets
    - If the number of bracelets is less than the bracelets possesed
        - Set number of bracelets to the new number of bracelets
        - Set gold to the new gold after bracelets are sold
        - Return 1
    - Otherwirse return -1
*/

int Inventory::sellBracelet(int numBracelets)
{
    if (numBracelets <= treasures.at(2))
    {
        treasures.at(2) = treasures.at(2) - numBracelets;
        gold = numBracelets * 30;
        return 1;
    }
    else
    {
        return -1;
    }
}

/*
Function to sell circlets
    - If the number of circlets is less than the circlets possesed
        - Set number of circlets to the new number of circlets
        - Set gold to the new gold after circlets are sold
        - Return 1
    - Otherwirse return -1
*/

int Inventory::sellCirclet(int numCirclets)
{
    if (numCirclets <= treasures.at(3))
    {
        treasures.at(3) = treasures.at(3) - numCirclets;
        gold = numCirclets * 40;
        return 1;
    }
    else
    {
        return -1;
    }
}

/*
Function to sell goblets
    - If the number of goblets is less than the goblets possesed
        - Set number of goblets to the new number of goblets
        - Set gold to the new gold after goblets are sold
        - Return 1
    - Otherwirse return -1
*/

int Inventory::sellGoblet(int numGoblets)
{
    if (numGoblets <= treasures.at(4))
    {
        treasures.at(4) = treasures.at(4) - numGoblets;
        gold = numGoblets * 50;
        return 1;
    }
    else
    {
        return -1;
    }
}

/*
Funciton to add a number of rings
    - Add the number of rings to the treasures vector
*/

void Inventory::addRing(int numRings)
{
    treasures.at(0) += numRings;
}

/*
Funciton to add a number of necklaces
    - Add the number of necklaces to the treasures vector
*/

void Inventory::addNecklace(int numNecklaces)
{
    treasures.at(1) += numNecklaces;
}

/*
Funciton to add a number of bracelets
    - Add the number of bracelets to the treasures vector
*/

void Inventory::addBracelet(int numBracelets)
{
    treasures.at(2) += numBracelets;
}

/*
Funciton to add a number of circlets
    - Add the number of circlets to the treasures vector
*/

void Inventory::addCirclet(int numCirclets)
{
    treasures.at(3) += numCirclets;
}

/*
Funciton to add a number of goblets
    - Add the number of goblets to the treasures vector
*/

void Inventory::addGoblet(int numGoblets)
{
    treasures.at(4) += numGoblets;
}

/*
Void function to display and use the merchant main menu whenever it needs to be called
*/

void Inventory::merchantMainMenu()
{
    int menuSelect = -10; // sets menu select to -10 for the default menu

    // displays the initial message just once before the while loop
    cout << "If you're looking to get supplies, you've come to the right place." << endl;
    cout << "I would be happy to part with some of my wares...for the proper price!" << endl;

    while (menuSelect == -10) // takes user input for different options
    {
        showInventory(); // uses showInventory to display inventory
        cout << endl;
        cout << "Choose one of the following:" << endl;
        cout << "1. Ingredients: To make food, you have to cook raw ingredients." << endl;
        cout << "2. Cookware: You will need something to cook those ingredients." << endl;
        cout << "3. Weapons: It's dangerous to go alone, take this!" << endl;
        cout << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
        cout << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
        cout << "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
        cin >> menuSelect;
        cin.ignore(); // ignore to flush the cin buffer

        while (menuSelect != 1 && menuSelect != 2 && menuSelect != 3 && menuSelect != 4 && menuSelect != 5 && menuSelect != 6 && menuSelect != -10) // while loop to account for misinputs
        {
            cout << "Please enter an integer 1-6" << endl;
            cout << "Choose one of the following:" << endl;
            cout << "1. Ingredients: To make food, you have to cook raw ingredients." << endl;
            cout << "2. Cookware: You will need something to cook those ingredients." << endl;
            cout << "3. Weapons: It's dangerous to go alone, take this!" << endl;
            cout << "4. Armor: If you want to survive monster attacks, you will need some armor." << endl;
            cout << "5. Sell treasures: If you find anything shiny, I would be happy to take it off your hands." << endl;
            cout << "6. Leave: Make sure you get everything you need, I'm leaving after this sale!" << endl;
            cin >> menuSelect;
            cin.ignore(); // ignore to flush the cin buffer
        }

        while (menuSelect == 1) // Ingredients menu
        {
            int numIngredients;
            string yesOrNo;

            cout << "How many kg of ingredients do you need [1 Gold/kg]? (Enter a positive mulitple of 5, or 0 to cancel)" << endl;
            cin >> numIngredients;

            while (numIngredients != 5 && numIngredients != 10 && numIngredients != 15 && numIngredients != 20 && numIngredients != 25 && numIngredients != 30 && numIngredients != 35 && numIngredients != 40 && numIngredients != 45 && numIngredients != 0) // accounts for misinputs
            {
                cout << "Please enter a positive multiple of 5, or 0 to cancel" << endl;
                cin >> numIngredients;
            }

            if (numIngredients == 0) // if the user enters 0, cancel out of the menu
            {
                cout << "No problem, let me know if you still need ingredients" << endl;
                menuSelect = -10;
                break;
            }
            else
            {
                cout << "You want to buy " << numIngredients << " kg of ingredients for " << numIngredients << " Gold? (y/n)" << endl; // double checks transaction
                cin >> yesOrNo;

                while (yesOrNo != "y" && yesOrNo != "n") // takes user's validation
                {
                    cout << "Please enter a valid input" << endl;
                    cin >> yesOrNo;
                }
                if (yesOrNo == "y")
                {
                    int result = setIngredients(ingredients + numIngredients); // uses setIngredients to the number
                    if (result == -1)                                          // checks for if the player doesn't have enough gold
                    {
                        cout << "Not enough gold" << endl;
                        cout << endl;
                        menuSelect = -10;
                    }
                    else // thanks the user for their patronage
                    {
                        cout << "Thank you for your patronage! What else can I get for you?" << endl;
                        menuSelect = -10; // sends back to main menu
                    }
                }
                else if (yesOrNo == "n") // if not sends back to main menu
                {
                    cout << "No problem, anything else I can get for you?" << endl;
                    menuSelect = -10;
                    break;
                }
            }
        }
        while (menuSelect == 2) // cookware menu
        {
            int cookwareSelect = 0;

            // cookware message to be displayed once
            cout << "I have a several types of cookware, which one would you like?" << endl;
            cout << "Each type has a different probability of breaking when used, marked with (XX%)." << endl;
            cout << endl;

            while (cookwareSelect == 0) // default cookware menu
            {
                cout << "Choose one of the following:" << endl;
                cout << "1. (25%) Ceramic Pot [2 Gold]" << endl;
                cout << "2. (10%) Frying Pan [10 Gold]" << endl;
                cout << "3. (2%) Cauldron [20 Gold]" << endl;
                cout << "4. Cancel" << endl;
                cin >> cookwareSelect;

                while (cookwareSelect > 4 || cookwareSelect < 0) // input validation for menu choice
                {
                    cout << "Enter a valid choice" << endl;
                    cin >> cookwareSelect;
                }

                while (cookwareSelect == 1) // menu for buying a pot
                {
                    int potNumber;
                    string yesOrNo;
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> potNumber;

                    if (potNumber == 0) // if the user cancels, go back to main menu
                    {
                        menuSelect = -10;
                        break;
                    }

                    while (potNumber < 0) // input validation for the number of pots
                    {
                        cout << "Enter a valid number that you wish to purchase" << endl;
                        cin >> potNumber;
                    }
                    cout << "You want to buy " << potNumber << " Ceramic Pot(s) for " << 2 * potNumber << " Gold? (y/n)" << endl;
                    cin >> yesOrNo;

                    while (yesOrNo != "y" && yesOrNo != "n") // takes a yes or no from the user
                    {
                        cout << "Please enter a valid input" << endl;
                        cin >> yesOrNo;
                    }
                    if (yesOrNo == "y") // if they select yes...
                    {
                        int result = buyPot(potNumber);

                        if (result == -1) // checks for not enough gold
                        {
                            cout << "Not enough gold" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                        else // thanks user for their patronage
                        {
                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                    }
                    else if (yesOrNo == "n") // if no, sends user back to main menu
                    {
                        cout << "No problem, anything else I can get for you?" << endl;
                        menuSelect = -10;
                        break;
                    }
                }
                while (cookwareSelect == 2)
                {
                    int panNumber;
                    string yesOrNo;
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> panNumber;

                    if (panNumber == 0)
                    {
                        menuSelect = -10;
                        break;
                    }

                    while (panNumber < 0)
                    {
                        cout << "Enter a valid number that you wish to purchase" << endl;
                        cin >> panNumber;
                    }

                    cout << "You want to buy " << panNumber << " Frying Pan(s) for " << 10 * panNumber << " Gold? (y/n)" << endl;
                    cin >> yesOrNo;

                    while (yesOrNo != "y" && yesOrNo != "n")
                    {
                        cout << "Please enter a valid input" << endl;
                        cin >> yesOrNo;
                    }

                    if (yesOrNo == "y")
                    {
                        int result = buyPan(panNumber);

                        if (result == -1)
                        {
                            cout << "Not enough gold" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                        else
                        {
                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                    }
                    else if (yesOrNo == "n")
                    {
                        cout << "No problem, anything else I can get for you?" << endl;
                        menuSelect = -10;
                        break;
                    }
                }
                while (cookwareSelect == 3)
                {
                    int caulNumber;
                    string yesOrNo;
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> caulNumber;

                    if (caulNumber == 0)
                    {
                        menuSelect = -10;
                        break;
                    }

                    while (caulNumber < 0)
                    {
                        cout << "Enter a valid number that you wish to purchase" << endl;
                        cin >> caulNumber;
                    }
                    cout << "You want to buy " << caulNumber << " Cauldron(s) for " << 20 * caulNumber << " Gold? (y/n)" << endl;
                    cin >> yesOrNo;

                    while (yesOrNo != "y" && yesOrNo != "n")
                    {
                        cout << "Please enter a valid input" << endl;
                        cin >> yesOrNo;
                    }

                    if (yesOrNo == "y")
                    {
                        int result = buyCauldron(caulNumber);

                        if (result == -1)
                        {
                            cout << "Not enough gold" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                        else
                        {
                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                    }
                    else if (yesOrNo == "n")
                    {
                        cout << "No problem, anything else I can get for you?" << endl;
                        menuSelect = -10;
                        break;
                    }
                }
                while (cookwareSelect == 4)
                {
                    menuSelect = -10;
                }
            }
        }
        while (menuSelect == 3)
        {
            int weaponSelect = 0;
            cout << endl;
            cout << "I have a plentiful collection of weapons to choose from, what would you like?" << endl;
            cout << "Note that some of them provide you a special bonus in combat, marked by a (+X)." << endl;
            cout << endl;

            while (weaponSelect == 0)
            {
                cout << "Choose one of the following:" << endl;
                cout << "1. Stone Club [2 Gold]" << endl;
                cout << "2. Iron Spear [2 Gold]" << endl;
                cout << "3. (+1) Mythril Rapier [5 Gold]" << endl;
                cout << "4. (+2) Flaming Battle-Axe [15 Gold]" << endl;
                cout << "5. (+3) Vorpal Longsword [50 Gold]" << endl;
                cout << "6. Cancel" << endl;
                cout << endl;
                cin >> weaponSelect;

                while (weaponSelect > 6 || weaponSelect < 0)
                {
                    cout << "Enter a valid choice" << endl;
                    cin >> weaponSelect;
                }

                while (weaponSelect == 1)
                {
                    int clubNumber;
                    string yesOrNo;
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> clubNumber;

                    if (clubNumber == 0)
                    {
                        menuSelect = -10;
                        break;
                    }

                    while (clubNumber < 0)
                    {
                        cout << "Enter a valid number that you wish to purchase" << endl;
                        cin >> clubNumber;
                    }
                    cout << "You want to buy " << clubNumber << " Stone Club(s) for " << 2 * clubNumber << " Gold? (y/n)" << endl;
                    cin >> yesOrNo;

                    while (yesOrNo != "y" && yesOrNo != "n")
                    {
                        cout << "Please enter a valid input" << endl;
                        cin >> yesOrNo;
                    }

                    if (yesOrNo == "y")
                    {
                        int result = buyClub(clubNumber);

                        if (result == -1)
                        {
                            cout << "Not enough gold" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                        else
                        {
                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                    }
                    else if (yesOrNo == "n")
                    {
                        cout << "No problem, anything else I can get for you?" << endl;
                        menuSelect = -10;
                        break;
                    }
                }

                while (weaponSelect == 2)
                {
                    int spearNum;
                    string yesOrNo;
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> spearNum;

                    if (spearNum == 0)
                    {
                        menuSelect = -10;
                        break;
                    }

                    while (spearNum < 0)
                    {
                        cout << "Enter a valid number that you wish to purchase" << endl;
                        cin >> spearNum;
                    }
                    cout << "You want to buy " << spearNum << " Iron Spear(s) for " << 2 * spearNum << " Gold? (y/n)" << endl;
                    cin >> yesOrNo;

                    while (yesOrNo != "y" && yesOrNo != "n")
                    {
                        cout << "Please enter a valid input" << endl;
                        cin >> yesOrNo;
                    }

                    if (yesOrNo == "y")
                    {
                        int result = buySpear(spearNum);

                        if (result == -1)
                        {
                            cout << "Not enough gold" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                        else
                        {
                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                    }
                    else if (yesOrNo == "n")
                    {
                        cout << "No problem, anything else I can get for you?" << endl;
                        menuSelect = -10;
                        break;
                    }
                }

                while (weaponSelect == 3)
                {
                    int rapierNum;
                    string yesOrNo;
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> rapierNum;

                    if (rapierNum == 0)
                    {
                        menuSelect = -10;
                        break;
                    }

                    while (rapierNum < 0)
                    {
                        cout << "Enter a valid number that you wish to purchase" << endl;
                        cin >> rapierNum;
                    }
                    cout << "You want to buy " << rapierNum << " Mythril Rapier(s) for " << 5 * rapierNum << " Gold? (y/n)" << endl;
                    cin >> yesOrNo;

                    while (yesOrNo != "y" && yesOrNo != "n")
                    {
                        cout << "Please enter a valid input" << endl;
                        cin >> yesOrNo;
                    }

                    if (yesOrNo == "y")
                    {
                        int result = buyRapier(rapierNum);

                        if (result == -1)
                        {
                            cout << "Not enough gold" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                        else
                        {
                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                    }
                    else if (yesOrNo == "n")
                    {
                        cout << "No problem, anything else I can get for you?" << endl;
                        menuSelect = -10;
                        break;
                    }
                }

                while (weaponSelect == 4)
                {
                    int axeNum;
                    string yesOrNo;
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> axeNum;

                    if (axeNum == 0)
                    {
                        menuSelect = -10;
                        break;
                    }

                    while (axeNum < 0)
                    {
                        cout << "Enter a valid number that you wish to purchase" << endl;
                        cin >> axeNum;
                    }
                    cout << "You want to buy " << axeNum << " Flaming Battle-Axe(s) for " << 15 * axeNum << " Gold? (y/n)" << endl;
                    cin >> yesOrNo;

                    while (yesOrNo != "y" && yesOrNo != "n")
                    {
                        cout << "Please enter a valid input" << endl;
                        cin >> yesOrNo;
                    }

                    if (yesOrNo == "y")
                    {
                        int result = buyAxe(axeNum);

                        if (result == -1)
                        {
                            cout << "Not enough gold" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                        else
                        {
                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                    }
                    else if (yesOrNo == "n")
                    {
                        cout << "No problem, anything else I can get for you?" << endl;
                        menuSelect = -10;
                        break;
                    }
                }

                while (weaponSelect == 5)
                {
                    int swordNum;
                    string yesOrNo;
                    cout << "How many would you like? (Enter a positive integer, or 0 to cancel)" << endl;
                    cin >> swordNum;

                    if (swordNum == 0)
                    {
                        menuSelect = -10;
                        break;
                    }

                    while (swordNum < 0)
                    {
                        cout << "Enter a valid number that you wish to purchase" << endl;
                        cin >> swordNum;
                    }
                    cout << "You want to buy " << swordNum << " Vorpal Longsword(s) for " << 50 * swordNum << " Gold? (y/n)" << endl;
                    cin >> yesOrNo;

                    while (yesOrNo != "y" && yesOrNo != "n")
                    {
                        cout << "Please enter a valid input" << endl;
                        cin >> yesOrNo;
                    }

                    if (yesOrNo == "y")
                    {
                        int result = buyLongsword(swordNum);

                        if (result == -1)
                        {
                            cout << "Not enough gold" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                        else
                        {
                            cout << "Thank you for your patronage! What else can I get for you?" << endl;
                            cout << endl;
                            menuSelect = -10;
                            break;
                        }
                    }
                    else if (yesOrNo == "n")
                    {
                        cout << "No problem, anything else I can get for you?" << endl;
                        menuSelect = -10;
                        break;
                    }
                }
                while (weaponSelect == 6)
                {
                    menuSelect = -10;
                    break;
                }
            }
        }
        while (menuSelect == 4)
        {
            int armorSelect;
            cout << "How many suits of armor can I get you? (Enter a positive integer, or 0 to cancel)" << endl;
            cin >> armorSelect;

            while (armorSelect == 0)
            {
                menuSelect = -10;
                break;
            }
            while (armorSelect < 0)
            {
                cout << "Please enter a positive integer, or 0 to cancel" << endl;
                cin >> armorSelect;
            }
            while (armorSelect > 0)
            {
                string yesOrNo;
                cout << "You want to buy " << armorSelect << " suit(s) of armor for " << armorSelect * 5 << " Gold? (y/n)" << endl;
                cin >> yesOrNo;

                while (yesOrNo != "y" && yesOrNo != "n")
                {
                    cout << "Please enter y or n" << endl;
                    cin >> yesOrNo;
                }
                if (yesOrNo == "y")
                {
                    int result = setArmor(armorSelect);

                    if (result == 1)
                    {
                        cout << "------------------------------------------------------" << endl;
                        cout << "Thank you for your patronage! What else can I get for you?" << endl;
                        menuSelect = -10;
                        break;
                    }
                    else if (result == -1)
                    {
                        cout << "------------------------------------------------------" << endl;
                        cout << "Not enough gold, what else can I get for you?" << endl;
                        break;
                    }
                }
                else if (yesOrNo == "n")
                {
                    cout << "------------------------------------------------------" << endl;
                    cout << "No problem what else can I get for you?" << endl;
                    menuSelect = -10;
                    break;
                }
            }
        }
        while (menuSelect == 5)
        {
            int treasureSelect;
            cout << endl;
            cout << "You have: R: " << treasures.at(0) << " | N: " << treasures.at(1) << " | B: " << treasures.at(2) << " | C: " << treasures.at(3) << " | G: " << treasures.at(4) << endl;
            cout << "Which type of treasure would you like to sell? (1)R ,(2)N ,(3)B ,(4)C ,(5)G (or press 0 to cancel)" << endl;
            cin >> treasureSelect;

            while (treasureSelect == 0)
            {
                cout << "------------------------------------------------------" << endl;
                cout << "No problem, what else can I get for you?" << endl;
                menuSelect = -10;
                break;
            }
            while (treasureSelect == 1)
            {
                int ringNum;
                cout << "How many silver ring(s) would you like to sell?" << endl;
                cin >> ringNum;

                int result = sellRings(ringNum);

                if (result == -1)
                {
                    cout << "You do not have enough rings" << endl;
                    menuSelect = -10;
                    break;
                }
                if (result == 1)
                {
                    cout << "Your rings have been sold" << endl;
                    menuSelect = -10;
                    break;
                }
            }
            while (treasureSelect == 2)
            {
                int necklaceNum;
                cout << "How many ruby necklace(s) would you like to sell?" << endl;
                cin >> necklaceNum;

                int result = sellNecklace(necklaceNum);

                if (result == -1)
                {
                    cout << "You do not have enough necklaces" << endl;
                    menuSelect = -10;
                    break;
                }
                if (result == 1)
                {
                    cout << "Your necklaces have been sold" << endl;
                    menuSelect = -10;
                    break;
                }
            }
            while (treasureSelect == 3)
            {
                int braceletNum;
                cout << "How many emerald bracelet(s) would you like to sell?" << endl;
                cin >> braceletNum;

                int result = sellBracelet(braceletNum);

                if (result == -1)
                {
                    cout << "You do not have enough bracelets" << endl;
                    menuSelect = -10;
                    break;
                }
                if (result == 1)
                {
                    cout << "Your bracelets have been sold" << endl;
                    menuSelect = -10;
                    break;
                }
            }
            while (treasureSelect == 4)
            {
                int circletNum;
                cout << "How many diamond circlet(s) would you like to sell?" << endl;
                cin >> circletNum;

                int result = sellCirclet(circletNum);

                if (result == -1)
                {
                    cout << "You do not have enough circlets" << endl;
                    menuSelect = -10;
                    break;
                }
                if (result == 1)
                {
                    cout << "Your circlets have been sold" << endl;
                    menuSelect = -10;
                    break;
                }
            }
            while (treasureSelect == 5)
            {
                int gobNum;
                cout << "How many gem-encrusted goblet(s) would you like to sell?" << endl;
                cin >> gobNum;

                int result = sellGoblet(gobNum);

                if (result == -1)
                {
                    cout << "You do not have enough goblets" << endl;
                    menuSelect = -10;
                    break;
                }
                if (result == 1)
                {
                    cout << "Your goblets have been sold" << endl;
                    menuSelect = -10;
                    break;
                }
            }
        }
        while (menuSelect == 6)
        {
            return;
        }
    }
    while (menuSelect == 6)
    {
        return;
    }
}
