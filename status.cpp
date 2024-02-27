#include "status.h"

Status::Status() // default constructor sets everything to 0
{
    roomsCleared = 0;
    keys = 0;
    angerLevel = 0;
}

Status::Status(int roomsCleared_, int keys_, int angerLevel_) // param. constructor
{
    roomsCleared = roomsCleared_;
    keys = keys_;
    angerLevel = angerLevel_;
}

void Status::getStatus() // displays the status of the party
{
    cout << "+-------------+" << endl;
    cout << "| STATUS      |" << endl;
    cout << "+-------------+" << endl;
    cout << "| Rooms Cleared: " << roomsCleared << " | Keys: " << keys << " | Anger Level: " << angerLevel << endl;
}

void Status::setRoomsCleared(int rooms) // sets the number of rooms cleared
{
    roomsCleared = rooms;
}

void Status::getPuzzle(int roomNum) // gets a puzzle based on an inputed number
{
    if (roomNum == 0)
    {
        cout << "Solve: 2x + 10 = 20" << endl;
    }
    if (roomNum == 1)
    {
        cout << "Solve: 5x + 10x = 30" << endl;
    }
    if (roomNum == 2)
    {
        cout << "Solve: 120x + 10 = 130" << endl;
    }
    if (roomNum == 3)
    {
        cout << "Solve: 9x + 4 = 31" << endl;
    }
    if (roomNum == 4)
    {
        cout << "Solve: 14x + 20 = 48" << endl;
    }
}

string Status::getPuzzleAnswer(int roomNum) // gets an answer to a corresponding puzzle based on a number
{
    if (roomNum == 0)
    {
        return "5";
    }
    if (roomNum == 1)
    {
        return "2";
    }
    if (roomNum == 2)
    {
        return "1";
    }
    if (roomNum == 3)
    {
        return "3";
    }
    if (roomNum == 4)
    {
        return "2";
    }
    else
    {
        return "";
    }
}

void Status::increaseRoomsCleared() // increases rooms cleared by 1
{
    roomsCleared++;
}

int Status::getRoomsCleared() // returns to ammount of rooms cleared
{
    return roomsCleared;
}

void Status::setNumKeys(int keys_) // sets the number of keys
{
    keys = keys_;
}

int Status::getNumKeys() // returns the current number of keys
{
    return keys;
}

void Status::setAngerLevel(int angerLevel_) // sets the anger level
{
    angerLevel = angerLevel_;
}

int Status::getAngerLevel() // return the current anger level
{
    return angerLevel;
}
