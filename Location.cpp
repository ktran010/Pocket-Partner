// CS1300 Fall 2020
// Author: Katherine Tran
// Recitation: 323 -- Christopher Gavin
// Project 3 -- Location class implementation file

#include "Location.h"
#include <string>
using namespace std;

Location::Location()
{
    string locationName = ""; // initalize the locationName string to empty

    for (int i = 0; i < SIZE; i++) // makes every element of choice1 and choice2 arrays empty
    {
        choice1Array[i] = "";
        choice2Array[i] = "";
    }
}

Location::Location(string _Arr1[], string _Arr2[])
{
    for (int i = 0; i < SIZE; i++) // makes every element of choice1 and choice2 arrays empty
    {
        choice1Array[i] = _Arr1[i];
        choice2Array[i] = _Arr2[i];
    }
}

void Location::setLocationName(string _loc)
{
    string locationName = _loc; // whatever is passed in as a parameter is equal to locationName
}

void Location::setChoice1At(int _ind, string _choice)
{
    if(_ind >= 0 && _ind < 4) // only takes in the choice string from indexes 0-4
    {
        choice1Array[_ind] = _choice;
    }
}

void Location::setChoice2At(int _ind, string _choice)
{
    if(_ind >= 0 && _ind < 4) // only takes in the choice string from indexes 0-4
    {
        choice2Array[_ind] = _choice;
    }
}

string Location::getLocationName() const
{
    return locationName; // retrieve the location name
}

string Location::getChoice1At(int _ind) const
{
    if(_ind >= 0 && _ind < 4) // string of the choice1 array retrieved if index is from 0-4
    {
        return choice1Array[_ind];
    }
    else
    {
        return "fail";
    }
}

string Location::getChoice2At(int _ind) const
{
    if(_ind >= 0 && _ind < 4) // string of the choice2 array retrieved if index is from 0-4
    {
        return choice2Array[_ind];
    }
    else
    {
        return "fail";
    }
}