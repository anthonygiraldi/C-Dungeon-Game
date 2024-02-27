#ifndef MY_Monster
#define MY_Monster

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Monsters
{
private:
    static const int maxMonsters = 27; // max monsters of 27
    string monsters[maxMonsters][2];   // 2D array that holds monsters and monster level
    int num_monsters;                  // total number of monsters

public:
    Monsters(); // default constructor

    int splitMonsters(string input_string, char seperator, string tempArray[], int tempArraySize); // splits monsters into the 2D array using split function

    void deleteMonster(int monsterNumber); // removes monster from array

    int readMonsters(string file_name); // reads monsters into the array

    string getMonsterLevel(int monsterNumber); // gets a monster of a certain level

    string getMonsterOfLevel(string level); // displays a monster of a certain level
};

#endif
