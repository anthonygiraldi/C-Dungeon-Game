#include <iostream>
#include <string>

using namespace std;

class Status
{
private:
    int roomsCleared;
    int keys;
    int angerLevel;

public:
    Status(); // default const.

    Status(int roomsCleared_, int keys_, int angerLevel_); // param. const.

    void getStatus(); // gets the status

    void getPuzzle(int roomNum); // gets a puzzle

    string getPuzzleAnswer(int roomNum); // gets a puzzle answer

    void setRoomsCleared(int num_rooms_); // sets the number of rooms cleared

    void increaseRoomsCleared(); // increases rooms cleared by 1

    int getRoomsCleared(); // gets the number of rooms cleared

    void setNumKeys(int keys); // sets the number of keys

    int getNumKeys(); // gets the current number of keys

    void setAngerLevel(int angerLevel); // sets the anger level

    int getAngerLevel(); // return the current anger level
};
