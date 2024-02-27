#include "monster.h"
#include <fstream>

using namespace std;

Monsters::Monsters()
{
    readMonsters("monsters.txt");
}

int Monsters::splitMonsters(string input_string, char seperator, string tempArray[], int tempArraySize)
{
    // creating our split function that takes in an input string
    int counter = 1;
    int arr_count = 0;
    int string_count = 0; // initialing our different "counter" variables

    for (int i = 0; i < input_string.length(); i++)
    { // for loop that loops through each character of the input_string
        if (input_string[i] != seperator)
        {                                                                 // if statement for if the character of the string does not equal the seperator character
            tempArray[arr_count] += input_string.substr(string_count, 1); // adds the character to the array
            string_count++;                                               // increases string count by one so that we are able to add the next character
        }
        else if (input_string[i] == seperator)
        {                                    // if statement for if the character of the string does equal the seperator
            counter++;                       // increases our counter indicating we have another part of the string being split
            arr_count++;                     // increases array_count so that the next time our input does not equal the seperator if will be filling a new part of the array
            string_count = string_count + 1; // increases our string_count by 1 so that we skip over the seperator since it is not included in the array
        }
    }
    if (counter > tempArraySize)
    {                 // if statement that checks if the counter is greater than our arr_size
        counter = -1; // sets the counter equal to -1;
    }
    else if (input_string.length() == 0)
    {             // if statement that makes sure that the input is not just an empty string by checking the length
        return 0; // returns 0 from our function
    }
    return counter; // returns counter to the main function
}

int Monsters::readMonsters(string file_name)
{
    ifstream textStream;        // creates ifstream object
    textStream.open(file_name); // open the file given by the user d
    string text;
    int counter = 0;

    if (textStream.is_open()) // checks if the file is open
    {
        while (getline(textStream, text))
        {
            string tempArray[2];
            if (splitMonsters(text, ',', tempArray, 2) == 2) // if the result of splitting the text equals for and the number of lines is less than the post array size
            {
                monsters[counter][0] = tempArray[0];
                monsters[counter][1] = tempArray[1];
                counter++;
            }
        }
        return true;
    }
    else
    {
        return false;
    }
}

void Monsters::deleteMonster(int monsterNumber) // removes monsters from the array by setting them to empty strings
{
    monsters[monsterNumber][0] = "";
    monsters[monsterNumber][1] = "";
}

string Monsters::getMonsterLevel(int monsterNumber) // gets a monster at a certain level
{
    return monsters[monsterNumber][1];
}

string Monsters::getMonsterOfLevel(string level) // gets a monster of a certain level and then displays it
{
    for (int i = 0; i < maxMonsters; i++)
    {
        if (monsters[i][1] == level)
        {
            cout << monsters[i][0] << " AHEAD THEY LOOK HOSTILE" << endl;
            deleteMonster(i);
            return monsters[i][1];
        }
    }
    return "";
}