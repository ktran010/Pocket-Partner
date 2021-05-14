// CS1300 Fall 2020
// Author: Katherine Tran
// Recitation: 323 -- Christopher Gavin
// Project 3 -- Character class implementation file


#include "Character.h"
#include <string>
using namespace std;


Character::Character()
{
    username = "";
    description = "";
    likes = "";
    dislikes = ""; // initalizes all string data members of each object to empty
    affectionLevel = 0; // initalizes affection level to 0
}

Character::Character(string _name, string _desc, string _li, string _disli, int _aff)
{
    username = _name;
    description = _desc;
    likes = _li;
    dislikes = _disli; // initalizes each respective string data member of each object to the respective strings passed in
    affectionLevel = _aff; // initalizes each respective affectionLevel of each object to the respective integer passed in
}

void Character::setUsername(string _name) // whatever is passed in as a parameter is equal to username
{
    username = _name;
}

void Character::setDescription(string _desc) // whatever is passed in as a parameter is equal to description
{
    description = _desc;
}

void Character::setLikes(string _li) // whatever is passed in as a parameter is equal to likes
{
    likes = _li;
}

void Character::setDislikes(string _disli) // whatever is passed in as a parameter is equal to dislikes
{
    dislikes = _disli;
}

void Character::setAffection(int _aff) // the integer passed in as a parameter is equal to affectionLevel
{
    affectionLevel = _aff;
}

void Character::addAffection(int _addaff) // the integer passed in is added to affectionLevel, increasing the value
{
    affectionLevel +=_addaff;
}

void Character::subAffection(int _subaff) // the integer passed in is subtracted from affectionLevel, decreasing the value
{
    affectionLevel -=_subaff;
}

string Character::getUsername() const // retrieve username
{
    return username;
}

string Character::getDescription() const // retrieve description
{
    return description;
}

string Character::getLikes() const // retrieve likes
{
    return likes;
}

string Character::getDislikes() const // retrieve dislikes
{
    return dislikes;
}

int Character::getAffectionLevel() const // retrieve affectionLevel
{
    return affectionLevel;
}
