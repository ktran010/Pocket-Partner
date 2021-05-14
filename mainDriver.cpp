// CS1300 Fall 2020
// Author: Katherine Tran
// Recitation: 323 -- Christopher Gavin
// Project 3

#include "Simulator.h"
#include "Character.h"
#include "Location.h"
#include "Line.h"
#include <iostream>
using namespace std;

int main()
{

    cout << endl << endl <<
            ".・゜゜・　　・゜゜・．.・゜゜・　　・゜゜・．" << endl <<
            ".・゜　.・゜゜・　           ・゜゜・．゜・．" << endl << endl <<
            "                 ᴡᴇʟᴄᴏᴍᴇ ᴛᴏ…                " << endl << endl <<
            "     ❤  ＰＯＣＫＥＴ ＰＡＲＴＮＥＲ ❤         " << endl << endl <<
            "     ᴀ ᴍɪɴɪ ɪɴᴛᴇʀᴀᴄᴛɪᴠᴇ ᴅᴀᴛɪɴɢ ꜱɪᴍᴜʟᴀᴛᴏʀ    " << endl << endl <<
            ".・゜　.・゜゜・　           ・゜゜・．゜・．" << endl <<
            ".・゜゜・　　・゜゜・．.・゜゜・　　・゜゜・．" << endl << endl; // print a title screen


    Simulator SimObject; // creating an object of the driver class, Simulator
    SimObject.start(); // using a member function of the Simulator class (where the gameplay takes place)

return 0;
}