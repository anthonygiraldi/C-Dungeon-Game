#include "inventory.h"
#include "map.h"
#include "monster.h"
#include "party.h"
#include "status.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>

/*
mainMenu function:
    - Displays every aspect that needs to be shown for a status update
*/

void mainMenu(Inventory inventory, Map map, Monsters monsters, Party party, Status status)
{
    status.getStatus();
    inventory.showInventory();
    party.displayParty();
    map.displayMap();
}

int main()
{
    // declaring all of my objects from my different classes
    Inventory inventory = Inventory();
    Map map = Map();
    Monsters monsters = Monsters();
    Party party = Party();
    Status status = Status();

    ofstream myfile; // creating an ofstream object so that I can write final game stats to a file

    // initializing my overall variables that change throughout the entire game
    int riddleNum = 1;
    int spacesExplored = 0;
    int numMonstersKilled = 0;
    int numTurns = 0;

    party.setPartyNames(); // sets the party names using the setPartyNames function
    cout << endl;

    srand(time(0)); // getting a seed for random number generation

    for (int i = 0; i < 5; i++) // for loop that adds in NPC's onto the map at random positions
    {
        int randomRow = ((rand() % (10 - 1 + 1)) + 1);
        int randomCol = ((rand() % (11 - 1 + 1)) + 0);
        bool result = map.addNPC(randomRow, randomCol);
        if (result == false)
        {
            i = i - 1;
        }
    }
    for (int i = 0; i < 5; i++) // for loop that adds rooms onto the map at random positions
    {
        int randomRow = ((rand() % (10 - 1 + 1)) + 1);
        int randomCol = ((rand() % (11 - 1 + 1)) + 0);
        bool result = map.addRoom(randomRow, randomCol);
        if (result == false)
        {
            i = i - 1;
        }
    }

    // starting screen dialogue
    cout << "Between the 5 of you, you have 100 gold pieces." << endl;
    cout << "You will need to spend the some of your money on the following items:" << endl;
    cout << endl;
    cout << "- INGREDIENTS. To make food, you have to cook raw ingredients." << endl;
    cout << "- COOKWARE. If you want to cook, you have to have cookware first." << endl;
    cout << "- WEAPONS. You'll want at least one weapon per party member to fend off monsters." << endl;
    cout << "- ARMOR. Armor increases the chances of surviving a monster attack." << endl;
    cout << endl;
    cout << "You can spend all of your money here before you start your journey, or you can save some to spend on merchants along the way. " << endl;
    cout << "But beware, some of the merchants in this dungeon are shady characters, and they won't always give you a fair price..." << endl;
    cout << endl;

    // opens up the merchant menu for the user to purchase goods
    inventory.merchantMainMenu();
    cout << endl;

    int menuSelect = -1; // sets menu to the default menu

    while (menuSelect == -1) // default blank space menu
    {
        mainMenu(inventory, map, monsters, party, status);              // opens the main menu for the player
        while (map.isFreeSpace(map.getPlayerRow(), map.getPlayerCol())) // when on a free space
        {
            int userInput;

            // gives the user options
            cout << "Select one: " << endl;
            cout << "1. Move" << endl;
            cout << "2. Investigate" << endl;
            cout << "3. Pick a fight" << endl;
            cout << "4. Cook and Eat" << endl;
            cout << "5. Give up" << endl;
            cin >> userInput;

            // input validation
            if (userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4 && userInput != 5)
            {
                cout << "Please enter an integer 1-5" << endl;
                cin >> userInput;
            }

            if (userInput == 1) // if statement for moving around the map
            {
                char userDirection;
                cout << "Which direction would you like to move? (w,a,s,d)" << endl;
                cin >> userDirection;

                while (userDirection != 'a' && userDirection != 's' && userDirection != 'w' && userDirection != 'd') // input validation
                {
                    cout << "Please enter a valid input" << endl;
                    cin >> userDirection;
                }

                map.move(userDirection); // moves the user in the specified direction

                for (int i = 0; i < 5; i++) // for loop that random changes the hunger level of some members of the party
                {
                    int hungerDecrease = (rand() % (5 - 1 + 1) + 1);

                    if (hungerDecrease == 2) // 1/5 chance (20%)
                    {
                        party.setFullness(i, party.getFullness(i) - 1);
                        party.isDead(i);
                    }
                }

                if (!map.isExplored(map.getPlayerRow(), map.getPlayerCol())) // increases the anger level is the map is not explored
                {
                    status.setAngerLevel(status.getAngerLevel() + 1);
                }
                if (party.getMembersDead() == 4) // checks to make sure that all players are alive and if not, displays the ending screen
                {
                    // using myFile to write to a file the final stats of the game
                    myfile.open("finalStats.txt");
                    myfile << status.getRoomsCleared() << endl;
                    myfile << inventory.getGold() << endl;
                    myfile << spacesExplored << endl;
                    myfile << numMonstersKilled << endl;
                    myfile << numTurns << endl;
                    myfile << endl;
                    myfile.close();
                    cout << "All the members of your party have died. You lose" << endl;
                    mainMenu(inventory, map, monsters, party, status);
                    cout << "You had " << spacesExplored << " spaces explored" << endl;
                    cout << "You killed " << numMonstersKilled << " monsters" << endl;
                    cout << "You used " << numTurns << " turns!" << endl;
                    numTurns++;
                    return 0;
                }
                if (map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) && status.getRoomsCleared() == 5) // checks for the winning condition when the player goes onto the dungeon exit
                {
                    myfile.open("finalStats.txt");
                    myfile << status.getRoomsCleared() << endl;
                    myfile << inventory.getGold() << endl;
                    myfile << spacesExplored << endl;
                    myfile << numMonstersKilled << endl;
                    myfile << numTurns << endl;
                    myfile << endl;
                    myfile.close();
                    cout << "You win!!" << endl;
                    mainMenu(inventory, map, monsters, party, status);
                    cout << "You had " << spacesExplored << " spaces explored" << endl;
                    cout << "You killed " << numMonstersKilled << " monsters" << endl;
                    cout << "You used " << numTurns << " turns!" << endl;
                    return 0;
                }
                if (status.getAngerLevel() >= 100) // checks to make sure the anger level isn't 100
                {
                    cout << "The sorceror has become too angry! He destroys the dungeon and everything inside! YOU LOSE" << endl;
                    myfile.open("finalStats.txt");
                    myfile << status.getRoomsCleared() << endl;
                    myfile << inventory.getGold() << endl;
                    myfile << spacesExplored << endl;
                    myfile << numMonstersKilled << endl;
                    myfile << numTurns << endl;
                    myfile << endl;
                    myfile.close();
                    cout << "You win!!" << endl;
                    mainMenu(inventory, map, monsters, party, status);
                    cout << "You had " << spacesExplored << " spaces explored" << endl;
                    cout << "You killed " << numMonstersKilled << " monsters" << endl;
                    cout << "You used " << numTurns << " turns!" << endl;
                    return 0;
                }
                if (map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol())) // checks if an NPC and directs to NPC menu
                {
                    cout << "You have found an NPC!" << endl;
                    numTurns++;
                    menuSelect = 1;
                    break;
                }
                numTurns++;
                menuSelect = -1;
                break;
            }
            if (userInput == 2) // explores the space
            {
                if (map.isExplored(map.getPlayerRow(), map.getPlayerCol())) // checks if the space is already explored
                {
                    cout << "You cannot investigate this space as it is already explored" << endl;
                    menuSelect = -1;
                    break;
                }
                else if (!map.isExplored(map.getPlayerRow(), map.getPlayerCol())) // if the map isn't explored...
                {
                    int keyChance = (rand() % (10 - 1 + 1) + 1); // chance of finding a key (1/10)

                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol()); // sets space to explored
                    spacesExplored++;

                    if (keyChance == 2) // when a key is found, increases the number of keys
                    {
                        cout << "You found a key!" << endl;
                        status.setNumKeys(status.getNumKeys() + 1);
                    }

                    int treasureChance = (rand() % (5 - 1 + 1) + 1); // 1 in 5 chance of finding treasure

                    if (treasureChance == 3 && status.getRoomsCleared() > 0) // changes the type of treasure based on the number of rooms cleared
                    {
                        cout << "You found some treasure!" << endl;
                        if (status.getRoomsCleared() == 1)
                        {
                            inventory.addRing(1);
                        }
                        if (status.getRoomsCleared() == 2)
                        {
                            inventory.addNecklace(1);
                        }
                        if (status.getRoomsCleared() == 3)
                        {
                            inventory.addBracelet(1);
                        }
                        if (status.getRoomsCleared() == 4)
                        {
                            inventory.addCirclet(1);
                        }
                        if (status.getRoomsCleared() == 5)
                        {
                            inventory.addGoblet(1);
                        }
                    }

                    int monsterChance = (rand() % (5 - 1 + 1) + 1); // chance of finding a monster (1/5)

                    if (monsterChance == 2)
                    {
                        string monsterLevel = to_string(status.getRoomsCleared() + 1); // gets a monster of a certain level based on rooms cleared
                        monsters.getMonsterOfLevel(monsterLevel);

                        if (inventory.getWeaponCount() > 0) // makes sure that the user has a weapon
                        {
                            for (int i = 0; i < 5; i++) // random chance of losing hunger again
                            {
                                int hungerChance = (rand() % (5 - 1 + 1) + 1);

                                if (hungerChance == 2)
                                {
                                    party.setFullness(i, party.getFullness(i) - 1);
                                    party.isDead(i);
                                }
                            }
                            // gives the user the options for fighting the monster
                            int userInput;
                            cout << "Would you like to fight or surrender?" << endl;
                            cout << "1. Fight" << endl;
                            cout << "2. Surrender" << endl;
                            cin >> userInput;
                            while (userInput != 1 && userInput != 2) // input validation
                            {
                                cout << "Please choose between the given options" << endl;
                                cin >> userInput;
                            }
                            if (userInput == 1) // if the user fights the monster...
                            {
                                // finds variables and uses calculations to see if the player defeats the monster
                                int w = inventory.getWeaponCount() + (1 * inventory.getRapier()) + (2 * inventory.getAxe()) + (3 * inventory.getSword());
                                int d;
                                if (inventory.differentWeapons() == true)
                                {
                                    d = 4;
                                }
                                else
                                {
                                    d = 0;
                                }
                                int a = inventory.getArmor() + 1;
                                int c = status.getRoomsCleared() + 1;

                                int r1 = (rand() % (6 - 1 + 1) + 1);
                                int r2 = (rand() % (6 - 1 + 1) + 1);

                                int result = ((r1 * w) + d) - ((r2 * c) / a);

                                cout << result << endl;

                                if (result > 0) // if the result is over 0 that means the player has won
                                {
                                    numMonstersKilled++;
                                    inventory.setGold(10 * c);                                      // gifts gold to the player
                                    inventory.setIngredients(inventory.getIngredients() + (5 * c)); // gifts ingredients to the player
                                    int keyChance = (rand() % (10 - 1 + 1) + 1);                    // random chance of finding a key
                                    if (keyChance == 4)
                                    {
                                        status.setNumKeys(status.getNumKeys() + 1);
                                        cout << "The monster dropped a key!" << endl;
                                    }
                                    cout << "You have slain the monster!" << endl;
                                }
                                else if (result <= 0) // if it is 0 or under, they have lost the fight
                                {
                                    cout << "You have lost the fight" << endl;

                                    int goldLoss = inventory.getGold() / 4; // lplayer uses 1/4 of their gold
                                    inventory.setGold(inventory.getGold() - goldLoss);
                                    inventory.setIngredients(inventory.getIngredients() - 30); // player loses 30 ingredients
                                    for (int i = 1; i < 5; i++)                                // for loop that loops through each party member to see if they have randomly died
                                    {
                                        int deathChanceNoArmor = (rand() % (10 - 1 + 1) + 1);
                                        int deathChanceArmor = (rand() % (20 - 1 + 1) + 1);

                                        if (inventory.getArmorAt(i) > 0)
                                        {
                                            if (deathChanceArmor == 17) // chances of dying change based on having armor...
                                            {
                                                cout << party.getPartyName(i) << " HAS BEEN SLAIN!" << endl;
                                                party.setMemberDead(i);
                                                party.setFullness(i, 0);
                                                party.isDead(i);
                                            }
                                        }
                                        else
                                        {
                                            if (deathChanceNoArmor == 5) // and having no armor
                                            {
                                                cout << party.getPartyName(i) << " HAS BEEN SLAIN!" << endl;
                                                party.setMemberDead(i);
                                                party.setFullness(i, 0);
                                                party.isDead(i);
                                            }
                                        }
                                    }
                                }
                            }
                            if (userInput == 2) // if the user chooses to surrender, one member of the party is captured
                            {
                                cout << "You surrender, but a member of your party gets caught and is now held captive by the monster!" << endl;
                                int captureChance = (rand() % (4 - 1 + 1) + 1);
                                party.setMemberDead(captureChance);
                            }
                        }
                        else // if the user does not have any weapons they automatically surrender
                        {
                            cout << "You surrender, but a member of your party gets caught and is now held captive by the monster!" << endl;
                            int captureChance = (rand() % (4 - 1 + 1) + 1);
                            party.setMemberDead(captureChance);
                        }
                    }
                    numTurns++;
                    menuSelect = -1;
                    break;
                }

                // misfortune chances:

                int robbChance = (rand() % (3 - 1 + 1) + 1);

                if (robbChance == 1) // being robbed by bandits...
                {
                    cout << "Oh no, your team was robbed by dungeon bandits! They have stolen 10kg of ingredients!" << endl;
                    inventory.setIngredients(inventory.getIngredients() - 10);
                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                    spacesExplored++;
                    menuSelect = -1;
                    break;
                }
                if (robbChance == 2) // a random weapon breaking
                {
                    int weaponsChance = (rand() % (inventory.getWeaponCount() - 0 + 1) + 0);
                    if (weaponsChance == 0 && inventory.getClub() > 0)
                    {
                        cout << "Oh no, your club has broken!" << endl;
                        inventory.setClub(inventory.getClub() - 1);
                    }
                    else if (weaponsChance == 1 && inventory.getSpear() > 0)
                    {
                        cout << "Oh no, your spear has broken!" << endl;
                        inventory.setSpear(inventory.getSpear() - 1);
                    }
                    else if (weaponsChance == 2 && inventory.getRapier() > 0)
                    {
                        cout << "Oh no, your rapier has broken!" << endl;
                        inventory.setRapier(inventory.getRapier() - 1);
                    }
                    else if (weaponsChance == 3 && inventory.getAxe() > 0)
                    {
                        cout << "Oh no, your axe has broken!" << endl;
                        inventory.setAxe(inventory.getAxe() - 1);
                    }
                    else if (weaponsChance == 4 && inventory.getSword() > 0)
                    {
                        cout << "Oh no, your sword has broken!" << endl;
                        inventory.setSword(inventory.getSword() - 1);
                    }

                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                    spacesExplored++;
                    numTurns++;
                    menuSelect = -1;
                    break;
                }
                if (robbChance == 3) // food poisoning
                {
                    cout << "One of the members of your party got food poisoning!" << endl;
                    int partyMember = (rand() % (4 - 1 + 1) + 1);

                    party.setFullness(partyMember, party.getFullness(partyMember) - 10);
                    party.isDead(partyMember);

                    if (party.isDead(partyMember) == true) // checks if they have died from the food poisoning
                    {
                        cout << party.getPartyName(partyMember) << "has died to starvation." << endl;
                    }
                    numTurns++;
                    menuSelect = -1;
                    break;
                }

                numTurns++;
                menuSelect = -1;
                break;
            }
            if (userInput == 3) // picking a fight with the monster... same ideas as before
            {
                string monsterLevel = to_string(status.getRoomsCleared() + 1);
                monsters.getMonsterOfLevel(monsterLevel);

                if (inventory.getWeaponCount() > 0)
                {
                    for (int i = 0; i < 5; i++)
                    {
                        int hungerChance = (rand() % (5 - 1 + 1) + 1);

                        if (hungerChance == 2)
                        {
                            party.setFullness(i, party.getFullness(i) - 1);
                            party.isDead(i);
                        }
                    }

                    int userInput;
                    cout << "Would you like to fight or surrender?" << endl;
                    cout << "1. Fight" << endl;
                    cout << "2. Surrender" << endl;
                    cin >> userInput;
                    while (userInput != 1 && userInput != 2)
                    {
                        cout << "Please choose between the given options" << endl;
                        cin >> userInput;
                    }
                    if (userInput == 1)
                    {
                        int w = inventory.getWeaponCount() + (1 * inventory.getRapier()) + (2 * inventory.getAxe()) + (3 * inventory.getSword());
                        int d;
                        if (inventory.differentWeapons() == true)
                        {
                            d = 4;
                        }
                        else
                        {
                            d = 0;
                        }
                        int a = inventory.getArmor() + 1;
                        int c = status.getRoomsCleared() + 1;

                        int r1 = (rand() % (6 - 1 + 1) + 1);
                        int r2 = (rand() % (6 - 1 + 1) + 1);

                        int result = ((r1 * w) + d) - ((r2 * c) / a);

                        cout << result << endl;

                        if (result > 0)
                        {
                            numMonstersKilled++;
                            inventory.setGold(10 * c);
                            inventory.setIngredients(5 * c);
                            int keyChance = (rand() % (10 - 1 + 1) + 1);
                            if (keyChance == 4)
                            {
                                status.setNumKeys(status.getNumKeys() + 1);
                                cout << "The monster dropped a key!" << endl;
                            }
                            cout << "You have slain the monster!" << endl;
                        }
                        else if (result <= 0)
                        {
                            cout << "You have lost the fight" << endl;

                            int goldLoss = inventory.getGold() / 4;
                            inventory.setGold(inventory.getGold() - goldLoss);
                            inventory.setIngredients(inventory.getIngredients() - 30);
                            for (int i = 1; i < 5; i++)
                            {
                                int deathChanceNoArmor = (rand() % (10 - 1 + 1) + 1);
                                int deathChanceArmor = (rand() % (20 - 1 + 1) + 1);

                                if (inventory.getArmorAt(i) > 0)
                                {
                                    if (deathChanceArmor == 17)
                                    {
                                        cout << party.getPartyName(i) << " HAS BEEN SLAIN!" << endl;
                                        party.setMemberDead(i);
                                        party.setFullness(i, 0);
                                        party.isDead(i);
                                    }
                                }
                                else
                                {
                                    if (deathChanceNoArmor == 5)
                                    {
                                        cout << party.getPartyName(i) << " HAS BEEN SLAIN!" << endl;
                                        party.setMemberDead(i);
                                        party.setFullness(i, 0);
                                        party.isDead(i);
                                    }
                                }
                            }
                        }
                    }
                    if (userInput == 2)
                    {
                        cout << "You surrender, but a member of your party gets caught and is now held captive by the monster!" << endl;
                        int captureChance = (rand() % (4 - 1 + 1) + 1);
                        party.setMemberDead(captureChance);
                    }
                }
                else
                {
                    cout << "You surrender, but a member of your party gets caught and is now held captive by the monster!" << endl;
                    int captureChance = (rand() % (4 - 1 + 1) + 1);
                    party.setMemberDead(captureChance);
                }
                numTurns++;
                menuSelect = -1;
                break;
            }
            if (userInput == 4) // user selection to cook to heal fullness
            {
                if (inventory.getPot() == 0 && inventory.getPan() == 0 && inventory.getCauldron() == 0) // if there is not cookware.. tell the user they cannot cook
                {
                    cout << "You do not have any cookware to cook with, please select a different option" << endl;
                    menuSelect = -1;
                    break;
                }
                int userChoice; // display the user with what they have
                cout << "Which cookware item would you like to use?" << endl;
                cout << "You have: " << inventory.getPot() << " pot(s) " << inventory.getPan() << " pan(s) and " << inventory.getCauldron() << " cauldron(s)." << endl;
                cout << "1. Pot" << endl;
                cout << "2. Pan" << endl;
                cout << "3. Cauldron" << endl;
                cin >> userChoice;

                while (userChoice == 1 && inventory.getPot() == 0) // making sure they don't select something they dont have
                {
                    cout << "You do not have any pots. Select a different cookware" << endl;
                    cin >> userChoice;
                }
                while (userChoice == 2 && inventory.getPan() == 0) // making sure they don't select something they dont have
                {
                    cout << "You do not have any pans. Select a different cookware" << endl;
                    cin >> userChoice;
                }
                while (userChoice == 3 && inventory.getPot() == 0) // making sure they don't select something they dont have
                {
                    cout << "You do not have any cauldrons. Select a different cookware" << endl;
                    cin >> userChoice;
                }

                int ingredientNumber; // taking the ammount of ingredients to cook
                cout << "How many kg of ingredients do you want to cook? There is a 5:1 ratio between cooked food and fullness points" << endl;
                cin >> ingredientNumber;

                if (userChoice == 1 && inventory.getPot() > 0)
                {
                    int breakChance = (rand() % (4 - 1 + 1) + 1); // random chance of pots breaking

                    if (breakChance == 2)
                    {
                        cout << "The cook has failed as your pot has broken" << endl;
                        inventory.setIngredients(inventory.getIngredients() - ingredientNumber);
                        inventory.setPot(inventory.getPot() - 1);
                    }
                    else // if the cook was successful, heals everyones fullness
                    {
                        cout << "The cook was successful. The party's fullness has been updated!" << endl;
                        for (int i = 0; i < 5; i++)
                        {
                            party.setFullness(i, party.getFullness(i) + (ingredientNumber / 5));
                            party.isDead(i);
                            inventory.setIngredients(inventory.getIngredients() - ingredientNumber);
                        }
                    }
                }
                if (userChoice == 2 && inventory.getPan() > 0)
                {
                    int breakChance = (rand() % (10 - 1 + 1) + 1);

                    if (breakChance == 2)
                    {
                        cout << "The cook has failed as your pan has broken" << endl;
                        inventory.setIngredients(inventory.getIngredients() - ingredientNumber);
                        inventory.setPan(inventory.getPan() - 1);
                    }
                    else
                    {
                        cout << "The cook was successful. The party's fullness has been updated!" << endl;
                        for (int i = 0; i < 5; i++)
                        {
                            party.setFullness(i, party.getFullness(i) + (ingredientNumber / 5));
                            party.isDead(i);
                            inventory.setIngredients(inventory.getIngredients() - ingredientNumber);
                        }
                    }
                }
                if (userChoice == 3 && inventory.getCauldron() > 0)
                {
                    int breakChance = (rand() % (50 - 1 + 1) + 1);

                    if (breakChance == 2)
                    {
                        cout << "The cook has failed as your cauldron has broken" << endl;
                        inventory.setIngredients(inventory.getIngredients() - ingredientNumber);
                        inventory.setCauldron(inventory.getCauldron() - 1);
                    }
                    else
                    {
                        cout << "The cook was successful. The party's fullness has been updated!" << endl;
                        for (int i = 0; i < 5; i++)
                        {
                            party.setFullness(i, party.getFullness(i) + (ingredientNumber / 5));
                            party.isDead(i);
                            inventory.setIngredients(inventory.getIngredients() - ingredientNumber);
                        }
                    }
                }
                // misfortunes...
                int robbChance = (rand() % (3 - 1 + 1) + 1);

                if (robbChance == 1)
                {
                    cout << "Oh no, your team was robbed by dungeon bandits! They have stolen 10kg of ingredients!" << endl;
                    inventory.setIngredients(inventory.getIngredients() - 10);
                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                    spacesExplored++;
                    menuSelect = -1;
                    break;
                }
                if (robbChance == 2)
                {
                    int weaponsChance = (rand() % (inventory.getWeaponCount() - 0 + 1) + 0);
                    if (weaponsChance == 0)
                    {
                        cout << "Oh no, your club has broken!" << endl;
                        inventory.setClub(inventory.getClub() - 1);
                    }
                    else if (weaponsChance == 1)
                    {
                        cout << "Oh no, your spear has broken!" << endl;
                        inventory.setSpear(inventory.getSpear() - 1);
                    }
                    else if (weaponsChance == 2)
                    {
                        cout << "Oh no, your rapier has broken!" << endl;
                        inventory.setRapier(inventory.getRapier() - 1);
                    }
                    else if (weaponsChance == 3)
                    {
                        cout << "Oh no, your axe has broken!" << endl;
                        inventory.setAxe(inventory.getAxe() - 1);
                    }
                    else if (weaponsChance == 4)
                    {
                        cout << "Oh no, your sword has broken!" << endl;
                        inventory.setSword(inventory.getSword() - 1);
                    }

                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                    spacesExplored++;
                    menuSelect = -1;
                    break;
                }
                if (robbChance == 3)
                {
                    cout << "One of the members of your party got food poisoning!" << endl;
                    int partyMember = (rand() % (4 - 1 + 1) + 1);

                    party.setFullness(partyMember, party.getFullness(partyMember) - 10);
                    party.isDead(partyMember);

                    if (party.isDead(partyMember) == true)
                    {
                        cout << party.getPartyName(partyMember) << "has died to starvation." << endl;
                    }
                    numTurns++;
                    menuSelect = -1;
                    break;
                }
                numTurns++;
                menuSelect = -1;
                break;
            }

            if (userInput == 5) // give up menu
            {
                cout << "You have given up. It is too bad that could not make it out of the dungeon." << endl; // tells the user they have given up
                mainMenu(inventory, map, monsters, party, status);
                cout << "You had " << spacesExplored << " spaces explored" << endl;
                cout << "You killed " << numMonstersKilled << " monsters" << endl;
                cout << "You used " << numTurns << " turns!" << endl;
                numTurns++;
                return 0;
            }
        }

        while (menuSelect == 1) // NPC menu
        {
            int userInput; // gives the options for the NPC

            cout << "Select one: " << endl;
            cout << "1. Move" << endl;
            cout << "2. Speak to NPC" << endl;
            cout << "3. Give Up" << endl;
            cin >> userInput;

            while (userInput != 1 && userInput != 2 && userInput != 3) // input validation
            {
                cout << "Please enter an integer 1-3" << endl;
                cin >> userInput;
            }

            if (party.getMembersDead() == 4) // checks if some of the party is still alive
            {
                cout << "All the members of your party have died. You lose" << endl;
                mainMenu(inventory, map, monsters, party, status);
                cout << "You had " << spacesExplored << " spaces explored" << endl;
                cout << "You killed " << numMonstersKilled << " monsters" << endl;
                cout << "You used " << numTurns << " turns!" << endl;
                numTurns++;
                return 0;
            }

            if (userInput == 1) // direction menu...
            {
                char userDirection;
                cout << "Which direction would you like to move? (w,a,s,d)" << endl;
                cin >> userDirection;

                while (userDirection != 'a' && userDirection != 's' && userDirection != 'w' && userDirection != 'd')
                {
                    cout << "Please enter a valid input" << endl;
                    cin >> userDirection;
                }

                map.move(userDirection);

                for (int i = 0; i < 5; i++)
                {
                    int hungerDecrease = (rand() % (5 - 1 + 1) + 1);

                    if (hungerDecrease == 2)
                    {
                        party.setFullness(i, party.getFullness(i) - 1);
                        party.isDead(i);
                    }
                }

                if (!map.isExplored(map.getPlayerRow(), map.getPlayerCol()))
                {
                    status.setAngerLevel(status.getAngerLevel() + 1);
                }
                if (status.getAngerLevel() >= 100)
                {
                    cout << "The sorceror has become too angry! He destroys the dungeon and everything inside! YOU LOSE" << endl;
                    return 0;
                }
                if (map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol())) // checks for NPC
                {
                    cout << "You have found an NPC!" << endl;
                    numTurns++;
                    menuSelect = 1;
                    break;
                }

                if (map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) && status.getRoomsCleared() == 5) // checking win condition
                {
                    myfile.open("finalStats.txt");
                    myfile << status.getRoomsCleared() << endl;
                    myfile << inventory.getGold() << endl;
                    myfile << spacesExplored << endl;
                    myfile << numMonstersKilled << endl;
                    myfile << numTurns << endl;
                    myfile << endl;
                    myfile.close();
                    cout << "You win!!" << endl;
                    mainMenu(inventory, map, monsters, party, status);
                    cout << "You had " << spacesExplored << " spaces explored" << endl;
                    cout << "You killed " << numMonstersKilled << " monsters" << endl;
                    cout << "You used " << numTurns << " turns!" << endl;
                    return 0;
                }

                if (map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol())) // checking for rooms
                {
                    cout << "You have found a room!" << endl;
                    numTurns++;
                    menuSelect = 2;
                    break;
                }
                numTurns++;
                menuSelect = -1;
                break;
            }
            if (userInput == 2) // option to speak with the NPC
            {
                string riddleAnswer;
                inventory.getRiddle(riddleNum);
                cin >> riddleAnswer;

                if (riddleAnswer == inventory.getRiddleAnswer(riddleNum)) // gets a riddle based on how many NPC's have been spoken to
                {
                    // if the correct answer is given...
                    map.removeNPC(map.getPlayerRow(), map.getPlayerCol());
                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                    spacesExplored++;

                    string yesOrNo;
                    riddleNum++;
                    cout << "Correct! Since you are so smart, I am willing to sell you some goods. Would you like to purchase anything? (y/n)?" << endl;
                    cin >> yesOrNo;

                    while (yesOrNo != "y" && yesOrNo != "n") // asks the user if they would like to open the merchant menu
                    {
                        cout << "Please choose yes or no (y/n)" << endl;
                        cin >> yesOrNo;
                    }

                    if (yesOrNo == "y")
                    {
                        numTurns++;
                        inventory.merchantMainMenu();
                        menuSelect = 1;
                    }
                    if (yesOrNo == "n")
                    {
                        cout << "No problem, have a good rest of your journey!" << endl;
                        menuSelect = 1;
                        numTurns++;
                    }
                }
                else // if they guess the riddle wrong...
                {
                    map.removeNPC(map.getPlayerRow(), map.getPlayerCol());
                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                    spacesExplored++;

                    cout << "You have made me angry! Fight this beast instead" << endl; // summons a monster instead...
                    string monsterLevel = to_string(status.getRoomsCleared() + 1);
                    monsters.getMonsterOfLevel(monsterLevel);

                    // monster menu...

                    if (inventory.getWeaponCount() > 0)
                    {
                        for (int i = 0; i < 5; i++)
                        {
                            int hungerChance = (rand() % (5 - 1 + 1) + 1);

                            if (hungerChance == 2)
                            {
                                party.setFullness(i, party.getFullness(i) - 1);
                                party.isDead(i);
                            }
                        }

                        int userInput;
                        cout << "Would you like to fight or surrender?" << endl;
                        cout << "1. Fight" << endl;
                        cout << "2. Surrender" << endl;
                        cin >> userInput;
                        while (userInput != 1 && userInput != 2)
                        {
                            cout << "Please choose between the given options" << endl;
                            cin >> userInput;
                        }
                        if (userInput == 1)
                        {
                            int w = inventory.getWeaponCount() + (1 * inventory.getRapier()) + (2 * inventory.getAxe()) + (3 * inventory.getSword());
                            int d;
                            if (inventory.differentWeapons() == true)
                            {
                                d = 4;
                            }
                            else
                            {
                                d = 0;
                            }
                            int a = inventory.getArmor() + 1;
                            int c = status.getRoomsCleared() + 1;

                            int r1 = (rand() % (6 - 1 + 1) + 1);
                            int r2 = (rand() % (6 - 1 + 1) + 1);

                            int result = ((r1 * w) + d) - ((r2 * c) / a);

                            cout << result << endl;

                            if (result > 0)
                            {
                                numMonstersKilled++;
                                inventory.setGold(10 * c);
                                inventory.setIngredients(5 * c);
                                int keyChance = (rand() % (10 - 1 + 1) + 1);
                                if (keyChance == 4)
                                {
                                    status.setNumKeys(status.getNumKeys() + 1);
                                    cout << "The monster dropped a key!" << endl;
                                }
                                cout << "You have slain the monster!" << endl;
                            }
                            else if (result <= 0)
                            {
                                cout << "You have lost the fight" << endl;

                                int goldLoss = inventory.getGold() / 4;
                                inventory.setGold(inventory.getGold() - goldLoss);
                                inventory.setIngredients(inventory.getIngredients() - 30);
                                for (int i = 1; i < 5; i++)
                                {
                                    int deathChanceNoArmor = (rand() % (10 - 1 + 1) + 1);
                                    int deathChanceArmor = (rand() % (20 - 1 + 1) + 1);

                                    if (inventory.getArmorAt(i) > 0)
                                    {
                                        if (deathChanceArmor == 17)
                                        {
                                            cout << party.getPartyName(i) << " HAS BEEN SLAIN!" << endl;
                                            party.setMemberDead(i);
                                            party.setFullness(i, 0);
                                            party.isDead(i);
                                        }
                                    }
                                    else
                                    {
                                        if (deathChanceNoArmor == 5)
                                        {
                                            cout << party.getPartyName(i) << " HAS BEEN SLAIN!" << endl;
                                            party.setMemberDead(i);
                                            party.setFullness(i, 0);
                                            party.isDead(i);
                                        }
                                    }
                                }
                            }
                        }
                        numTurns++;
                        menuSelect = -1;
                        break;
                    }
                    numTurns++;
                    menuSelect = -1;
                    break;
                }
            }
            if (userInput == 3) // give up menu...
            {
                cout << "You have given up. It is too bad that could not make it out of the dungeon." << endl;
                mainMenu(inventory, map, monsters, party, status);
                cout << "You had " << spacesExplored << " spaces explored" << endl;
                cout << "You killed " << numMonstersKilled << " monsters" << endl;
                cout << "You used " << numTurns << " turns!" << endl;
                numTurns++;
                return 0;
            }
        }
        while (menuSelect == 2) // Room action menu
        {
            int userInput;
            // gives player options
            cout << "Select one: " << endl;
            cout << "1. Move" << endl;
            cout << "2. Open the Door" << endl;
            cout << "3. Give Up" << endl;
            cin >> userInput;

            while (userInput != 1 && userInput != 2 && userInput != 3) // input validation
            {
                cout << "Please enter an integer 1-3" << endl;
                cin >> userInput;
            }

            while (userInput == 1) // move menu...
            {
                char userDirection;
                cout << "Which direction would you like to move? (w,a,s,d)" << endl;
                cin >> userDirection;

                while (userDirection != 'a' && userDirection != 's' && userDirection != 'w' && userDirection != 'd')
                {
                    cout << "Please enter a valid input" << endl;
                    cin >> userDirection;
                }

                map.move(userDirection);

                for (int i = 0; i < 5; i++)
                {
                    int hungerDecrease = (rand() % (5 - 1 + 1) + 1);

                    if (hungerDecrease == 2)
                    {
                        party.setFullness(i, party.getFullness(i) - 1);
                        party.isDead(i);
                    }
                }

                if (!map.isExplored(map.getPlayerRow(), map.getPlayerCol()))
                {
                    status.setAngerLevel(status.getAngerLevel() + 1);
                }
                if (status.getAngerLevel() >= 100)
                {
                    cout << "The sorceror has become too angry! He destroys the dungeon and everything inside! YOU LOSE" << endl;
                    return 0;
                }

                if (map.isDungeonExit(map.getPlayerRow(), map.getPlayerCol()) && status.getRoomsCleared() == 5)
                {
                    myfile.open("finalStats.txt");
                    myfile << status.getRoomsCleared() << endl;
                    myfile << inventory.getGold() << endl;
                    myfile << spacesExplored << endl;
                    myfile << numMonstersKilled << endl;
                    myfile << numTurns << endl;
                    myfile << endl;
                    myfile.close();
                    cout << "You win!!" << endl;
                    mainMenu(inventory, map, monsters, party, status);
                    cout << "You had " << spacesExplored << " spaces explored" << endl;
                    cout << "You killed " << numMonstersKilled << " monsters" << endl;
                    cout << "You used " << numTurns << " turns!" << endl;
                    return 0;
                }

                if (map.isNPCLocation(map.getPlayerRow(), map.getPlayerCol()))
                {
                    cout << "You have found an NPC!" << endl;
                    numTurns++;
                    menuSelect = 1;
                    break;
                }
                if (map.isRoomLocation(map.getPlayerRow(), map.getPlayerCol()))
                {
                    cout << "You have found a room!" << endl;
                    numTurns++;
                    menuSelect = 2;
                    break;
                }
                menuSelect = -1;
                numTurns++;
                break;

                if (party.getMembersDead() == 4)
                {
                    cout << "All the members of your party have died. You lose" << endl;
                    mainMenu(inventory, map, monsters, party, status);
                    cout << "You had " << spacesExplored << " spaces explored" << endl;
                    cout << "You killed " << numMonstersKilled << " monsters" << endl;
                    cout << "You used " << numTurns << " turns!" << endl;
                    numTurns++;
                    return 0;
                }
            }
            while (userInput == 2) // opening the door menu...
            {
                if (status.getNumKeys() > 0) // if the user has a key, ask if they want to use the key
                {
                    string yesOrNo;
                    cout << "You have a key, do you want to use it on this door (y/n)?" << endl;
                    cin >> yesOrNo;

                    while (yesOrNo != "y" && yesOrNo != "n") // input validation
                    {
                        cout << "Please select yes or no" << endl;
                        cin >> yesOrNo;
                    }
                    if (yesOrNo == "y") // let them in the room and have them fight a monster
                    {
                        string monsterLevel = to_string(status.getRoomsCleared() + 2);
                        monsters.getMonsterOfLevel(monsterLevel);

                        if (inventory.getWeaponCount() > 0)
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                int hungerChance = (rand() % (5 - 1 + 1) + 1);

                                if (hungerChance == 2)
                                {
                                    party.setFullness(i, party.getFullness(i) - 1);
                                    party.isDead(i);
                                }
                            }

                            int userInput;
                            cout << "Would you like to fight or surrender?" << endl;
                            cout << "1. Fight" << endl;
                            cout << "2. Surrender" << endl;
                            cin >> userInput;
                            while (userInput != 1 && userInput != 2)
                            {
                                cout << "Please choose between the given options" << endl;
                                cin >> userInput;
                            }
                            if (userInput == 1)
                            {
                                int w = inventory.getWeaponCount() + (1 * inventory.getRapier()) + (2 * inventory.getAxe()) + (3 * inventory.getSword());
                                int d;
                                if (inventory.differentWeapons() == true)
                                {
                                    d = 4;
                                }
                                else
                                {
                                    d = 0;
                                }
                                int a = inventory.getArmor() + 1;
                                int c = status.getRoomsCleared() + 1;

                                int r1 = (rand() % (6 - 1 + 1) + 1);
                                int r2 = (rand() % (6 - 1 + 1) + 1);

                                int result = ((r1 * w) + d) - ((r2 * c) / a);

                                if (result > 0)
                                {
                                    numMonstersKilled++;
                                    inventory.setGold(10 * c);
                                    inventory.setIngredients(inventory.getIngredients() + (5 * c));
                                    int keyChance = (rand() % (10 - 1 + 1) + 1);
                                    if (keyChance == 4)
                                    {
                                        status.setNumKeys(status.getNumKeys() + 1);
                                        cout << "The monster dropped a key!" << endl;
                                    }
                                    cout << "You have slain the monster!" << endl;
                                    status.setRoomsCleared(status.getRoomsCleared() + 1);
                                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                                    spacesExplored++;

                                    int misChance = (rand() % (2 - 1 + 1) + 1);
                                    if (misChance == 1)
                                    {
                                        int robbChance = (rand() % (4 - 1 + 1) + 1);

                                        if (robbChance == 1)
                                        {
                                            cout << "Oh no, your team was robbed by dungeon bandits! They have stolen 10kg of ingredients!" << endl;
                                            inventory.setIngredients(inventory.getIngredients() - 10);
                                            map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                                            spacesExplored++;
                                            menuSelect = -1;
                                            break;
                                        }
                                        if (robbChance == 2)
                                        {
                                            int weaponsChance = (rand() % (inventory.getWeaponCount() - 0 + 1) + 0);
                                            if (weaponsChance == 0 && inventory.getClub() > 0)
                                            {
                                                cout << "Oh no, your club has broken!" << endl;
                                                inventory.setClub(inventory.getClub() - 1);
                                            }
                                            else if (weaponsChance == 1 && inventory.getSpear() > 0)
                                            {
                                                cout << "Oh no, your spear has broken!" << endl;
                                                inventory.setSpear(inventory.getSpear() - 1);
                                            }
                                            else if (weaponsChance == 2 && inventory.getRapier() > 0)
                                            {
                                                cout << "Oh no, your rapier has broken!" << endl;
                                                inventory.setRapier(inventory.getRapier() - 1);
                                            }
                                            else if (weaponsChance == 3 && inventory.getAxe() > 0)
                                            {
                                                cout << "Oh no, your axe has broken!" << endl;
                                                inventory.setAxe(inventory.getAxe() - 1);
                                            }
                                            else if (weaponsChance == 4 && inventory.getSword() > 0)
                                            {
                                                cout << "Oh no, your sword has broken!" << endl;
                                                inventory.setSword(inventory.getSword() - 1);
                                            }

                                            map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                                            spacesExplored++;
                                            menuSelect = -1;
                                            break;
                                        }
                                        if (robbChance == 3)
                                        {
                                            cout << "One of the members of your party got food poisoning!" << endl;
                                            int partyMember = (rand() % (4 - 1 + 1) + 1);

                                            party.setFullness(partyMember, party.getFullness(partyMember) - 10);
                                            party.isDead(partyMember);

                                            if (party.isDead(partyMember) == true)
                                            {
                                                cout << party.getPartyName(partyMember) << "has died to starvation." << endl;
                                            }
                                            numTurns++;
                                            menuSelect = -1;
                                            break;
                                        }
                                        if (robbChance == 4)
                                        {
                                            int partyMember = (rand() % (4 - 1 + 1) + 1);
                                            party.setMemberTrapped(partyMember);
                                            cout << "OH NO! Your teammate " << party.getPartyName(partyMember) << "  is trapped in the previous room and is unable to get through. You must continue without them. Your party size has reduced" << endl;
                                            numTurns++;
                                            menuSelect = -1;
                                            break;
                                        }
                                    }
                                }
                                else if (result <= 0)
                                {
                                    cout << "You have lost the fight" << endl;

                                    int goldLoss = inventory.getGold() / 4;
                                    inventory.setGold(inventory.getGold() - goldLoss);
                                    inventory.setIngredients(inventory.getIngredients() - 30);
                                    for (int i = 1; i < 5; i++)
                                    {
                                        int deathChanceNoArmor = (rand() % (10 - 1 + 1) + 1);
                                        int deathChanceArmor = (rand() % (20 - 1 + 1) + 1);

                                        if (inventory.getArmorAt(i) > 0)
                                        {
                                            if (deathChanceArmor == 17)
                                            {
                                                cout << party.getPartyName(i) << " HAS BEEN SLAIN!" << endl;
                                                party.setMemberDead(i);
                                                party.setFullness(i, 0);
                                                party.isDead(i);
                                            }
                                        }
                                        else
                                        {
                                            if (deathChanceNoArmor == 5)
                                            {
                                                cout << party.getPartyName(i) << " HAS BEEN SLAIN!" << endl;
                                                party.setMemberDead(i);
                                                party.setFullness(i, 0);
                                                party.isDead(i);
                                            }
                                        }
                                    }
                                }
                            }
                            if (userInput == 2)
                            {
                                cout << "You surrender, but a member of your party gets caught and is now held captive by the monster!" << endl;
                                int captureChance = (rand() % (4 - 1 + 1) + 1);
                                party.setMemberDead(captureChance);
                            }
                        }
                        else
                        {
                            cout << "You surrender, but a member of your party gets caught and is now held captive by the monster!" << endl;
                            int captureChance = (rand() % (4 - 1 + 1) + 1);
                            map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                            spacesExplored++;
                            party.setMemberDead(captureChance);
                            numTurns++;
                            menuSelect = -1;
                            break;
                        }
                    }
                    if (yesOrNo == "n") // if the user doesn't use the key sends them back to room menu
                    {
                        cout << "Okay (you walk away from the door)" << endl;
                        menuSelect = 2;
                        break;
                    }
                }
                if (status.getNumKeys() == 0) // if the user does not have any keys, have them solve a riddle
                {
                    int incorrectCount = 0;
                    string userAnswer;
                    cout << "You must solve this puzzle to unlock the door: " << endl;

                    status.getPuzzle(status.getRoomsCleared());
                    cin >> userAnswer;

                    while (userAnswer != status.getPuzzleAnswer(status.getRoomsCleared())) // if the wrong answer is provided
                    {
                        incorrectCount++;

                        if (incorrectCount == 3) // incorrectCount counts to three before too many incorrect attempts are entered
                        {
                            // kills a random party member
                            int partyNum = (rand() % (4 - 1 + 1) + 1);
                            party.setMemberDead(partyNum);
                            cout << "You have failed three times. One of your party members is now dead" << endl;
                            numTurns++;
                            menuSelect = 2;
                            break;
                        }

                        cout << "Incorrect. Try again" << endl; // asks for the user to try again
                        cin >> userAnswer;
                    }
                    if (userAnswer == status.getPuzzleAnswer(status.getRoomsCleared())) // if the user gives the correct answer, let them in the room to fight the monster
                    {
                        cout << "Correct! You may now enter the room!" << endl;
                        status.setRoomsCleared(status.getRoomsCleared() + 1);
                        map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                        spacesExplored++;
                        numTurns++;
                        string monsterLevel = to_string(status.getRoomsCleared() + 2);
                        monsters.getMonsterOfLevel(monsterLevel);

                        if (inventory.getWeaponCount() > 0)
                        {
                            for (int i = 0; i < 5; i++)
                            {
                                int hungerChance = (rand() % (5 - 1 + 1) + 1);

                                if (hungerChance == 2)
                                {
                                    party.setFullness(i, party.getFullness(i) - 1);
                                    party.isDead(i);
                                }
                            }

                            int userInput;
                            cout << "Would you like to fight or surrender?" << endl;
                            cout << "1. Fight" << endl;
                            cout << "2. Surrender" << endl;
                            cin >> userInput;
                            while (userInput != 1 && userInput != 2)
                            {
                                cout << "Please choose between the given options" << endl;
                                cin >> userInput;
                            }
                            if (userInput == 1)
                            {
                                int w = inventory.getWeaponCount() + (1 * inventory.getRapier()) + (2 * inventory.getAxe()) + (3 * inventory.getSword());
                                int d;
                                if (inventory.differentWeapons() == true)
                                {
                                    d = 4;
                                }
                                else
                                {
                                    d = 0;
                                }
                                int a = inventory.getArmor() + 1;
                                int c = status.getRoomsCleared() + 1;

                                int r1 = (rand() % (6 - 1 + 1) + 1);
                                int r2 = (rand() % (6 - 1 + 1) + 1);

                                int result = ((r1 * w) + d) - ((r2 * c) / a);

                                if (result > 0)
                                {
                                    numMonstersKilled++;
                                    inventory.setGold(10 * c);
                                    inventory.setIngredients(inventory.getIngredients() + (5 * c));
                                    int keyChance = (rand() % (10 - 1 + 1) + 1);
                                    if (keyChance == 4)
                                    {
                                        status.setNumKeys(status.getNumKeys() + 1);
                                        cout << "The monster dropped a key!" << endl;
                                    }
                                    cout << "You have slain the monster!" << endl;
                                    status.setRoomsCleared(status.getRoomsCleared() + 1);
                                    map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                                    spacesExplored++;

                                    int misChance = (rand() % (2 - 1 + 1) + 1);
                                    if (misChance == 1)
                                    {
                                        int robbChance = (rand() % (4 - 1 + 1) + 1);

                                        if (robbChance == 1)
                                        {
                                            cout << "Oh no, your team was robbed by dungeon bandits! They have stolen 10kg of ingredients!" << endl;
                                            inventory.setIngredients(inventory.getIngredients() - 10);
                                            map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                                            spacesExplored++;
                                            menuSelect = -1;
                                            break;
                                        }
                                        if (robbChance == 2)
                                        {
                                            int weaponsChance = (rand() % (inventory.getWeaponCount() - 0 + 1) + 0);
                                            if (weaponsChance == 0)
                                            {
                                                cout << "Oh no, your club has broken!" << endl;
                                                inventory.setClub(inventory.getClub() - 1);
                                            }
                                            else if (weaponsChance == 1)
                                            {
                                                cout << "Oh no, your spear has broken!" << endl;
                                                inventory.setSpear(inventory.getSpear() - 1);
                                            }
                                            else if (weaponsChance == 2)
                                            {
                                                cout << "Oh no, your rapier has broken!" << endl;
                                                inventory.setRapier(inventory.getRapier() - 1);
                                            }
                                            else if (weaponsChance == 3)
                                            {
                                                cout << "Oh no, your axe has broken!" << endl;
                                                inventory.setAxe(inventory.getAxe() - 1);
                                            }
                                            else if (weaponsChance == 4)
                                            {
                                                cout << "Oh no, your sword has broken!" << endl;
                                                inventory.setSword(inventory.getSword() - 1);
                                            }

                                            map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                                            spacesExplored++;
                                            menuSelect = -1;
                                            break;
                                        }
                                        if (robbChance == 3)
                                        {
                                            cout << "One of the members of your party got food poisoning!" << endl;
                                            int partyMember = (rand() % (4 - 1 + 1) + 1);

                                            party.setFullness(partyMember, party.getFullness(partyMember) - 10);
                                            party.isDead(partyMember);

                                            if (party.isDead(partyMember) == true)
                                            {
                                                cout << party.getPartyName(partyMember) << " has died to starvation." << endl;
                                            }
                                            numTurns++;
                                            menuSelect = -1;
                                            break;
                                        }
                                        if (robbChance == 4)
                                        {
                                            int partyMember = (rand() % (4 - 1 + 1) + 1);
                                            party.setMemberTrapped(partyMember);
                                            cout << "OH NO! Your teammate " << party.getPartyName(partyMember) << "  is trapped in the previous room and is unable to get through. You must continue without them. Your party size has reduced" << endl;
                                            numTurns++;
                                            menuSelect = -1;
                                            break;
                                        }
                                    }
                                }
                                else if (result <= 0)
                                {
                                    cout << "You have lost the fight" << endl;

                                    int goldLoss = inventory.getGold() / 4;
                                    inventory.setGold(inventory.getGold() - goldLoss);
                                    inventory.setIngredients(inventory.getIngredients() - 30);
                                    for (int i = 1; i < 5; i++)
                                    {
                                        int deathChanceNoArmor = (rand() % (10 - 1 + 1) + 1);
                                        int deathChanceArmor = (rand() % (20 - 1 + 1) + 1);

                                        if (inventory.getArmorAt(i) > 0)
                                        {
                                            if (deathChanceArmor == 17)
                                            {
                                                cout << party.getPartyName(i) << " HAS BEEN SLAIN!" << endl;
                                                party.setMemberDead(i);
                                                party.setFullness(i, 0);
                                                party.isDead(i);
                                            }
                                        }
                                        else
                                        {
                                            if (deathChanceNoArmor == 5)
                                            {
                                                cout << party.getPartyName(i) << " HAS BEEN SLAIN!" << endl;
                                                party.setMemberDead(i);
                                                party.setFullness(i, 0);
                                                party.isDead(i);
                                            }
                                        }
                                    }
                                }
                            }
                            if (userInput == 2)
                            {
                                cout << "You surrender, but a member of your party gets caught and is now held captive by the monster!" << endl;
                                int captureChance = (rand() % (4 - 1 + 1) + 1);
                                party.setMemberDead(captureChance);
                            }
                        }
                        else
                        {
                            cout << "You surrender, but a member of your party gets caught and is now held captive by the monster!" << endl;
                            int captureChance = (rand() % (4 - 1 + 1) + 1);
                            map.exploreSpace(map.getPlayerRow(), map.getPlayerCol());
                            spacesExplored++;
                            party.setMemberDead(captureChance);
                            numTurns++;
                            menuSelect = -1;
                            break;
                        }
                        menuSelect = -1;
                        break;
                    }
                    numTurns++;
                    menuSelect = -1;
                    break;
                }
            }
            if (userInput == 3) // give up menu...
            {
                cout << "You have given up. It is too bad that could not make it out of the dungeon." << endl;
                mainMenu(inventory, map, monsters, party, status);
                cout << "You had " << spacesExplored << " spaces explored" << endl;
                cout << "You killed " << numMonstersKilled << " monsters" << endl;
                cout << "You used " << numTurns << " turns!" << endl;
                numTurns++;
                return 0;
            }
        }
    }
}
