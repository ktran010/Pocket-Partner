// CS1300 Fall 2020
// Author: Katherine Tran
// Recitation: 323 -- Christopher Gavin
// Project 3 -- Simulator driver class implementation file

#include "Simulator.h"
#include "Character.h"
#include "Location.h"
#include "Line.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cctype>
#include <iomanip>
#include <string>
#include <stdlib.h>
#include <time.h>
using namespace std;

Simulator::Simulator() // Default constructor
{
    Character characters[5];
	Location locations[5];
    Line lines[5];
}

int search(string str, char ch) // Function that checks for user error
{
    if(ch == '@') // checking for user error for entering username
    {
        if(str == "" || str[0] == ' ')
        {
            return 1;
        }

        for(int i = 0; i < str.length(); i++)
        {
            if(!isalpha(str[i]) && str[i] != ' ' || str[i] == ' ' && str[i+1] == ' ')
            {
                return 1;
            }
        }
    }
    else if(ch == '#') // checking for user error in entering user description, likes, dislikes
    {
        int count = 0;

        if(str == ".")
        {
            cout << endl << "Whoops! That didn't work. Try again." << endl;
            return 1;
        }
    
        for(int i = 0; i < str.length(); i++)
        {
            if(str[i] == '.')
            {
                count++;
                for(int j = i+1; j < str.length(); j++)
                {
                    cout << endl << "Whoops! That didn't work. Try again." << endl;
                    return 1;
                }
                return 0;
            }
        }

        if(count == 0)
        {
            cout << endl << "Make sure there's a period at the end! Try again." << endl;
            return 2;
        }
    }
    else if(ch == '$') // checking for user error in entering letters A-D
    {
        if(str == "A" || str == "B" || str == "C" || str == "D")
        {
            return 0;
        }
        else
        {
            cout << endl << "Invalid input! Try again." << endl;
            return 1;
        }
    }
    else if(ch == '%') // checking for user error in entering YES or NO
    {
        if(str == "YES" || str == "NO")
        {
            return 0;
        }
        else
        {
            cout << endl << "Invalid input! Try again." << endl;
            return 1;
        }
    }

return 0;
}

string uppercase(string YesNo) // Function that converts user input to capital letters
{
    string up;
    for (int i = 0; i < YesNo.length(); i++) // Traverse through the length of string YesNo
    {
        if (isalpha(YesNo[i])) // Only check/convert string value of Yes/No
        {
            up += toupper(YesNo[i]); //convert string value to be all lowercased
        }
    }
return up; // return the string value (now all lowercased)
}

void showAffection(Character characters[]) // Function that prints the affection level
{
    // menu that prints the affection level
    string upper;
    upper = uppercase(characters[4].getUsername()); // changes username to all capitals
    
    cout << endl << "          ❤   ＡＦＦＥＣＴＩＯＮ  ＬＥＶＥＬＳ  ❤" << endl << endl <<
    "【LEON: " << characters[0].getAffectionLevel() << "/25】【AUGUST: " << characters[1].getAffectionLevel() <<
    "/25】【PIPER: " << characters[2].getAffectionLevel() << "/25】【ELISE: " << characters[3].getAffectionLevel() <<
    "/25】" << endl << endl;
}

void printMenu(Character characters[], int ch) // Function that prints the info of each character
{
    // function that prints out the info of each character
    cout << endl << "About: " << characters[ch].getUsername() << endl
    << "──────" << endl;
    cout << "✧ " << characters[ch].getDescription() << endl << endl;
    cout << "Likes: " << characters[ch].getLikes() << endl
    << "──────" << endl;
    cout << "Disikes: " << characters[ch].getDislikes() << endl
    << "────────" << endl << endl;
    if(ch != 4)
    {
        cout << "❥ Interact with " << characters[ch].getUsername() << "?" << endl;
        cout  << "Yes" << setw(10) << "No" << endl; 
    }
    else
    {
        cout << "❥ Go back?" << endl;
        cout  << "Yes?" << endl;
    }
return;
}

int randomFunction() // RNG Function
{
    // random number generator
    srand(time(0));
    int random = (rand() % 11);

return random; // returns the randomly generated number
}

void hitEnter(string response) // Helper function, for user to hit "enter"
{
    // function that prints out these two lines -- saves lines
    cout << "(Please hit enter)" << endl;
    getline(cin, response);
return;
}

void Simulator::setLines(Character characters[], Line lines[], int numLetter) // Function that sets Line objects
{
    // function that sets each Line object's data member
    string tempA, tempB, tempC, tempD;
    tempA = "Dear " + characters[numLetter].getUsername() + ",";
    tempB = "To " + characters[numLetter].getUsername() + ":";
    tempC = characters[numLetter].getUsername() + ",";
    tempD = "Hey " + characters[numLetter].getUsername() + ",";

    lines[0] = Line(tempA, tempB, tempC, tempD); // first line, greeting

    lines[1] = Line("Something's been on my mind for a while.", "So, I really have to tell you something.",
                    "I've been thinking about something, a lot, lately.", "I have something important that I want you to know."); // second line, body
    lines[2] = Line("To tell you the truth, there's nothing more that I want than to be with you. You're more than what I could ever deserve.",
                    "I'm really nervous to admit this, but I have feelings for you. And I'd really like to spend more time with you.",
                    "I don't know what it is, but I can't get you out of my head, and I can't help wanting to be with you whenever I can.",
                    "I realized that, whenever I'm with you, I feel so much more happy, more content. Everything feels right when you're there."); // third line, body
    lines[3] = Line("Will you go out with me?", "I think we'd make a great couple. What do you think?",
                    "Can you see us together in a relationship?", "Do you feel the same way?"); // fourth line, body

    tempA = "Sincerely, " + characters[4].getUsername();
    tempB = "Cheers, " + characters[4].getUsername();
    tempC = "Yours, " + characters[4].getUsername();
    tempD = "Love, " + characters[4].getUsername();
    lines[4] = Line(tempA, tempB, tempC, tempD); // last line closing

return;
}

void Simulator::writeMessage(string filename, Character characters[], Line lines[], int numLetter) // Function that writes to a file
{
    string choice;
    setLines(characters, lines, numLetter); // call upon setLines function
    ofstream out_file; // ofstream to write to a file

    out_file.open(filename, std::ios_base::trunc); // open stream in truncate mode to clear pre-existing data
    out_file.close(); // close the stream after truncating

    out_file.open(filename, std::ios_base::app); // open stream in append mode to start writing to the file
    if (out_file.is_open()) // check if file opened successfully
    {
        for(int i = 0; i < 5; i++)
        {
            cout << endl << "Please enter the letter of your choice:" << endl // asking for user input
            << "───────────────────────────────────────" << endl;
            cout << endl << "A. " << lines[i].getOptionA() << endl << "B. " << lines[i].getOptionB() << endl << "C. " << lines[i].getOptionC() << endl << "D. " << lines[i].getOptionD() << endl;
            getline(cin, choice);
            choice = uppercase(choice); // converts user input to uppercase

            while(search(choice, '$') != 0) // checks for user error
            {
                cout << endl << "Please, enter the letter of your choice:" << endl
                << "───────────────────────────────────────" << endl;
                getline(cin, choice);
                choice = uppercase(choice);
            }

            if(choice == "A") // writing to the file depending on what option the user chooses
            {
                out_file << endl << lines[i].getOptionA() << endl;
            }
            else if(choice == "B")
            {
                out_file << endl << lines[i].getOptionB() << endl;
            }
            else if(choice == "C")
            {
                out_file << endl << lines[i].getOptionC() << endl;
            }
            else if(choice == "D")
            {
                out_file << endl << lines[i].getOptionD() << endl;
            }
        }
    }
    else
    {
        cout << "File failed to open!" << endl;
    }

    out_file.close(); // close the writing stream to prevent corruption

return;
}

void readMessage(string filename) // Function that reads a file
{
    string line;
    ifstream in_file; // stream to read from a file
    in_file.open(filename); // open the stream

    if(in_file.is_open()) // check if file is open
    {
        while(getline(in_file, line)) // reads each line of the text file
        {
            cout << line << endl; // prints every line of the text file
        }
    }
    else
    {
        cout << "File failed to open!" << endl;
    }
    
    in_file.close(); // close the file to prevent corruption

    cout << endl << "❥ Would you like to keep your message?" << endl;
    cout  << "Yes" << setw(10) << "No" << endl;

return;
}

int countseparators(string splitMe, char separator) // Helper function in the split function
{   
    int separator_count = 0;
    for (int i = 0; i < splitMe.length(); i++)
    {
        if (splitMe[i] == separator){
            separator_count++; // counter for how many separators there are
        }
    }
return separator_count;
}

int split(string splitMe, char separator, string array[], int size) // Split helper function
{
    int separator_count = countseparators(splitMe, separator); // call upon helper function
    int pieces = separator_count + 1; // number of pieces will be 1 larger than number of separators

    if(splitMe == "") //if the string is empty, there are no pieces
    {
        pieces = 0;
    }
    else if(pieces < size) // if number of pieces less than the size of the array
    {
        splitMe = splitMe + separator; // add a separator at the end to store all of split pieces into array
        pieces = 0; // set pieces back equal to 0, will serve as counter

        if(splitMe.find(separator) != -1){ // if a separator is found, the .find() function doesn't return -1
            for(int i = 0; i < splitMe.length(); i++)
            {
                if(splitMe[i] == separator){ // if ith character in string is a separator
                    string before = splitMe.substr(0,i); // creates a substring of characters leading up to the separator
                    array[pieces] = before; // places the substring into the array starting from pieces = 0
                    pieces++; // increment pieces so that next substring gets placed into next position in array

                    string after = splitMe.substr(i+1); // creates a substring of characters after the separator
                    splitMe = after; // splitMe is now equivalent to the substring after the separator
                    i = 0; // set i back equal to 0, traverse from beginning of splitMe again
                }
            }
        }
    }
    else if (pieces > size) // if number of pieces greater than the size of the array
    {
        splitMe = splitMe + separator; // add a separator at the end to store all of split pieces into array
        pieces = 0; // set pieces back equal to 0, will serve as counter
    
        if(splitMe.find(separator) != -1){ // if a separator is found, the .find() function returns -1
            for(int i = 0; i < splitMe.length(); i++)
            {
                if(splitMe[i] == separator && pieces < size){ // if ith character in string is a separator
                    string before = splitMe.substr(0,i); // strings will fill array if pieces < size, to prevent seg. fault
                    array[pieces] = before;
                    pieces++;

                    string after = splitMe.substr(i+1);
                    splitMe = after;
                    i = 0; 
                }
            }
        }
    pieces = -1; // since pieces > size, set pieces equal to -1 to be returned
    }
return pieces;
}

void readLocations(string fileName1, string fileName2, Location locations[], const int SIZE) // Function that reads two files, with two input streams
{
    int locationIndex = 0; // refers to each Location object
    ifstream in_file1;
    ifstream in_file2;// open two file streams
    in_file1.open(fileName1);
    in_file2.open(fileName2); // open the files

    if(in_file1.fail())
    {
        cout << "File1 failed to open!" << endl; // check if file failed to open   
    }
    else
    {
        if(in_file2.fail())
        {
            cout << "File1 failed to open!" << endl; // check if file failed to open
        }
        else
        {
            string line = "";
            string arr_temp1[4];
            string arr_temp2[4];

            while(getline(in_file1,line) && (locationIndex < 4)) // reads each line of the text file
            {
                if(line.length() > 0) // only reads non empty lines
                {
                    split(line, ',', arr_temp1, 50); // splits up each line getting read, stores the fragments in arr_temp1
                    for(int i = 0; i < SIZE; i++)
                    {
                        locations[locationIndex].setChoice1At(i, arr_temp1[i]);
                    }
                    locationIndex++;
                }
            }
            locationIndex = 0; // set index back to zero, to be incremented again in the following while loop
            while(getline(in_file2,line) && (locationIndex < 4)) // reads each line of the text file
            {
                if(line.length() > 0) // only reads non empty lines
                {
                    split(line, ',', arr_temp2, 50); // splits up each line getting read, stores the fragments in arr_temp2
                    for(int i = 0; i < SIZE; i++)
                    {
                        locations[locationIndex].setChoice2At(i, arr_temp2[i]);
                    }
                    locationIndex++;
                }
            }
        }
    }

in_file1.close();
in_file2.close(); // close the files to prevent corruption

return;
}

int openLocation(int ch, Location locations[], int choice, const int SIZE) // Function that prints the appropriate data members of the appropriate Location objects
{
    readLocations("choice1.txt", "choice2.txt", locations, SIZE); // call upon readLocations function
    string choice1, choice2; // strings storing the user's input
    string letters[4] = {"A. ", "B. ", "C. ", "D. "}; // array to print out letters in menu

    if(choice == 1) // if the choice1Array is going to be printed
    {
        cout << endl << "Please enter the letter of your choice below: " << endl;
        for (int i = 0; i < SIZE; i ++)
        {
            cout << letters[i] << locations[ch].getChoice1At(i) << endl;
        }
        getline(cin, choice1);
        choice1 = uppercase(choice1); // checking for user input being uppercase

        while(search(choice1, '$') != 0) // checking for user input error
        {
            cout << endl << "Please enter the letter of your choice below: " << endl;
            for (int i = 0; i < SIZE; i ++)
            {
                cout << letters[i] << locations[ch].getChoice1At(i) << endl;
            }
            getline(cin, choice1);
            choice1 = uppercase(choice1);
        }
        if(choice1 == "C")
        {
            return 1; //Special dialogue
        }
        else
        {
            return 0;
        }
    }
    else if (choice == 2) // if the choice2Array is going to be printed
    {
        cout << endl  << "Please enter the letter of your choice below: " << endl;
        for (int i = 0; i < SIZE; i ++)
        {
            cout << letters[i] << locations[ch].getChoice2At(i) << endl;
        }
        getline(cin, choice2);
        choice2 = uppercase(choice2);

        while(search(choice2, '$') != 0)
        {
            cout << endl << "Please enter the letter of your choice below: " << endl;
            for (int i = 0; i < SIZE; i ++)
            {
                cout << letters[i] << locations[ch].getChoice2At(i) << endl;
            }
            getline(cin, choice2);
            choice2 = uppercase(choice2);
        }
        if(choice2 == "A")
        {
            return 1; // Special dialogue
        }
        else
        {
            if(choice2 == "B")
            {
                return 2; // Rand event
            }
            else if (choice2 == "C")
            {
                return 3;
            }
            else if (choice2 == "D")
            {
                return 0;
            }
        }
    }
    
return 0;
}

void Simulator::LeonPlaythrough(Character characters[], Location locations[], const int SIZE, int locationChoice, string response, string YesNo, string answer, int random) // Dialogue for Leon
{
    int cell = 0, introduce = 0; // initializing necessary variables

    cout << endl << "「WEEK 1」" << endl;
    cout << endl << "Today is Monday. It's time to head to your first class of the day, and you're determined to start your week off strong! " << endl << endl << "Well, at least, that was the plan. You had slept in, and now you've got to book it to class." << endl;
    hitEnter(response);

    cout << endl << "You rush to calculus, and -- argh! Someone's nabbed your usual seat! No surprise there." << endl << "And the professor's already flying through content. Great." << endl;
    hitEnter(response);

    cout << endl << "You sit down quickly at a nearby seat." << endl << "As you set down your belongings, you glance around the aisle and meet the eyes of the person sitting next to you." << endl << endl << "You notice his lips turn upward in slight amusement at your breathless state." << endl;
    hitEnter(response);

    cout << endl << "Your attention snaps towards the front of the room, where the professor begins to write on the board." << endl << "You shift your focus to taking notes while your professor speaks. They throw out a problem for your class to work through, and encourage you to turn and talk to a neighbor." << endl;
    hitEnter(response);

    cout << endl << "You start working out the problem, so far so good, until -- shoot. You're stumped. You don't remember how to do this part." << endl;
    hitEnter(response);

    cout << endl << "You peek to your right -- that guy you made eye contact with earlier. Maybe you should ask him what he did." << endl;
    hitEnter(response);

    cout << endl << "❥ Do you want to try talking to him?" << endl; //ask for user input
    cout  << "Yes" << setw(10) << "No" << endl;

    getline(cin, YesNo);
    YesNo = uppercase(YesNo);
    while(search(YesNo, '%') != 0) //check for user error
    {
        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
    }

    if(YesNo == "YES") //if user input "YES"
    {
        cout << "⇡❤" << endl << endl;
        characters[0].addAffection(1);

        cout  << "✦ \"Hey. What answer did you get?\"" << endl;

        cout << endl << "He looks up from his paper and then glances down." << endl << "\"Uh, it looks like I'm getting 1/2, but I honestly have no idea what I'm doing.\"" << endl << endl << "He laughs a bit after that." << endl << "\"How about you?\"" << endl;
        hitEnter(response);

        cout << endl << "✦ \"Yeah, I'm not having much luck. I'm kind of stuck right here.\"" << endl << "You push your work a bit towards him to show him your work." << endl;
        hitEnter(response);

        cout << endl << "\"Oh, thanks! Here let me see… \"" << endl << "He leans a bit closer towards you, and you catch a faint whiff of vanilla and coffee beans." << endl;
        hitEnter(response);

        cout << endl << "\"Oh! I see, it looks like you made a sign error here, so you probably got stuck later down here.\"" << endl << endl << "You look down to your page and see your mistake." << endl;
        hitEnter(response);

        cout << endl << "✦ \"Ohhhh, yeah, I see. Geez, I made that same mistake in the homework from last night too. And it was already so annoying to work through.\"" << endl << "You said, in exasperation." << endl;
        hitEnter(response);

        cout << endl << "\"God, I know! That homework was brutal, it took me like, hours to finish. This unit has been pretty rough so far.\"" << endl << endl << "✦ \"Yeah, I agree. Thanks for the help!\"" << endl;
        hitEnter(response);

        cout << endl << "He nods and smiles at your thanks. The conversation has died a bit at this point." << endl;
        hitEnter(response);
        
        cout << endl << "❥ Any interest in continuing it?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;

        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if(YesNo == "YES") // if user input "YES"
        {
            cout << "⇡❤" << endl << endl;
            characters[0].addAffection(1);
            introduce++;

            cout << "✦ \"Hey, I'm " << characters[4].getUsername() << ", by the way. It's nice to meet you.\"" <<  endl;
            hitEnter(response);
            
            cout << endl << "His smile brightens a bit, and he turns to face you more clearly. " << "\"I'm Leon, it's nice meeting you as well! What are you majoring in?\"" << endl;
            hitEnter(response);
            
            cout << endl << "You and Leon converse a bit about majors, dorms, the usual." << endl << endl << "\"You know, you should've seen the professor glaring at you when you walked in late.\"" << endl << "Leon grins." << endl;
            hitEnter(response);
            
            cout << endl << "You groan at the mention of it, but Leon's infectious smile has you grinning as well." << endl << endl << "✦ \"I know, I woke up late and had to run all the way here. This class is on the other side of campus from my dorm!\"" << endl
            << endl << "Leon chuckles a bit, but before he could say anything else, the professor begins talking and brings back the attention of the class." << endl;
            hitEnter(response);
            
            cout << endl << "Class ends without a problem. You get up to leave and see Leon doing the same." << endl << "You did miss out on quite a bit of content, since you were late." << endl;
            hitEnter(response);

            cout << endl << "❥ Are you up for asking him to lend you some notes?" << endl;
            cout  << "Yes" << setw(10) << "No" << endl;
        }
        else // if "NO"
        {
            cout << endl << "You slide your notebook back towards your workspace and focus on fixing your work. Hopefully now you'll remember about those pesky sign changes." << endl;
            hitEnter(response);
            cout << endl << "Class ends without a problem. You get up to leave and see that guy from earlier doing the same." << endl << "You did miss out on quite a bit of content, since you were late." << endl;
            hitEnter(response);
            
            cout << endl <<  "❥ Are you up for asking this guy to lend you some notes?" << endl;
            cout  << "Yes" << setw(10) << "No" << endl;
        }
    }
    else // if "NO"
    {
        cout << endl << "Nah, guess not. You turn back towards your paper and continue working out the problem, searching for where you went wrong." << endl;
        hitEnter(response);
        
        cout << endl << "Class ends without a problem. You get up to leave and see that guy from earlier doing the same." << endl << "You did miss out on quite a bit of content, since you were late." << endl;
        hitEnter(response);

        cout << endl << "❥ Are you up for asking this guy to lend you some notes?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;
    }

    getline(cin, YesNo);
    YesNo = uppercase(YesNo);
    while(search(YesNo, '%') != 0) // check for user error
    {
        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
    }

    if(YesNo == "YES") // if user input "YES"
    {
        if(characters[0].getAffectionLevel() > 1)
        {
            cout << "⇡❤" << endl << endl;
            characters[0].addAffection(3);
            cell++;

            cout << "✦ \"Hey, I hope I'm not bothering you too much when I ask you this, but is it alright if I get some notes from you? I kind of missed a lot of stuff at the beginning…as you know…\"" << endl << endl << "Leon chuckles, and nods." << "\"Sure, I don't mind. I actually gotta head out for my next class, but I can send you notes.\"" << endl;
            hitEnter(response);

            cout << endl << "✦ \"That'd be really helpful, thank you! Here's my number.\"" << endl << endl << "\"Thanks " << characters[4].getUsername() <<  "! Here's mine. I'll send you notes later tonight!\"" << endl;
            hitEnter(response);

            cout << endl << "The two of you separate. You go on your merry way to your next class. You find yourself looking forward to hearing back from Leon soon. Guess this morning wasn't so bad, after all. Here's to a good rest of the day!" << endl;
            hitEnter(response);

            random = randomFunction();
            if (random <= 4)
            {
                cout << endl << "Leon sends you the notes, and the two of you actually end up having some enjoyable conversation, mainly poking fun at some of your favorite professors. ⇡❤" << endl << endl;
                characters[0].addAffection(2);
            }

            cout << "「END OF WEEK 1」" << endl;
            hitEnter(response);
        }
        else
        {
            cout << "⇡❤" << endl << endl;
            characters[0].addAffection(3);
            cell++;

            cout << "✦ \"Hey, I hope I'm not bothering you too much when I ask you this, but is it alright if I get some notes from you? I came in late and missed a lot of stuff.\"" << endl << endl << "The guy smiles kindly at you, and nods. " << endl << "\"Sure, I don't mind. I actually gotta head out for my next class, but I can send you notes.\"" << endl;
            hitEnter(response);

            cout << endl << "✦ \"That'd be really helpful, thank you! I'm " << characters[4].getUsername() << ", by the way. Here's my number.\"" << endl << endl << "\"Thanks " << characters[4].getUsername() <<  ", and I'm Leon. Here's mine. I'll send you notes later tonight!\"" << endl;
            hitEnter(response);

            cout << endl << "The two of you separate. You go on your merry way to your next class. Hopefully, the rest of today will make up for this morning's rough start." << endl;
            hitEnter(response);

            random = randomFunction();
            if (random <= 4)
            {
                cout << endl << "Leon sends you the notes, and the two of you actually end up having some enjoyable conversation, mainly poking fun at some of your favorite professors. ⇡❤" << endl << endl;
                characters[0].addAffection(2);
            }

            cout << "「END OF WEEK 1」" << endl;
            hitEnter(response);
        }
    }
    else // if "NO"
    {
        cout << endl << "Eh, forget it. Not worth the effort. You'll probably be fine." << endl << "You go on your merry way to your next class. Hopefully, the rest of today will make up for this morning's rough start." << endl << endl;
        hitEnter(response);

        cout << "「END OF WEEK 1」" << endl;
        hitEnter(response);
    }

// ---------------------------------------------------------------------------------------------

    cout << "「WEEK 2」" << endl;

    cout << endl << "Finally! The weekend could not arrive any faster! After a busy school week, you deserve a fun little outing, don't you think?" << endl;
    hitEnter(response);

    cout << endl << "It's been a hot minute since you've gone out for some coffee. And hey, you need the energy boost." << endl << "Let's visit the newly-opened café down the street, you've been dying to check it out!" << endl;
    hitEnter(response);

    cout << endl << "You enter the café, engulfed in the scent of freshly roasted coffee beans. You walk up to the register, intently scanning the menu, until --" << endl; 
    hitEnter(response);

    cout << endl << "\"Hey! Thanks for waiting, what can I get for you?\"" << endl << "You glance down to meet the eyes of whoever was talking to you." << endl; 
    hitEnter(response);

    if(introduce > 0) // user doesn't have intro
    {
        cout << endl << "\"Oh! " << characters[4].getUsername() << ", it's great to see you!\"" << endl;
        hitEnter(response);
        
        cout << endl << "✦ \"Leon! Hey, it's good seeing you too! I didn't realize you worked here!\"" << endl;
        hitEnter(response);
        
        cout << endl << "Leon flashed you a charming smile." << endl << "\"Yeah, this place opened up pretty recently and I took the opportunity! I love the smell of coffee, so I fit right in!\"" << endl << "\"Anyways, I'll be taking care of you, so if you're ready to order, go ahead!\"" << endl; 
        hitEnter(response);
        
        locationChoice = openLocation(0, locations, 1, SIZE); // call upon locationChoice function
    }
    else
    {
        cout << endl << "Oh, the barista kind of looks familiar. Someone in your class, maybe? You glance down at his nametag -- Leon. Huh. Who knows." << endl; 
        locationChoice = openLocation(0, locations, 1, SIZE); // call upon locationChoice function
    }

    if(locationChoice == 1) // if locationChoice returns 1
    {
        cout << "⇡❤" << endl << endl;
        characters[0].addAffection(5);
        cout << endl << "Leon grins. " << "\"Hey! Awesome choice! That's my favorite drink. I'll make it extra special for you!\""<< endl;
        hitEnter(response);
    }

    cout << endl << "\"Alrighty! Coming right up, that'll be 3 dollars.\"" << endl << endl << "You reach into your pockets and -- oh…no. There's nothing there. Where's your wallet, dummy? You left it at home didn't you?! Augh!" << endl;
    hitEnter(response);

    cout << endl << "✦ \"Oh god, this is embarrassing. I just realized I left my wallet at home. I'm so sorry for the trouble!\"" << endl;
    hitEnter(response);

    cout << endl << "Leon smiles reassuringly." << endl << "\"Oh, that's okay! It happens to the best of us, no worries. Here, how about this time, it's on me, okay?\"" << endl;
    hitEnter(response);

    cout << endl << "What a guy. You're quite surprised at the kind offer." << endl << "✦ \"That's really sweet of you, are you sure? You really don't have to!\"" << endl;
    hitEnter(response);

    cout << endl << "\"It's not a problem, I don't mind. Do you like vanilla? If you let me, I'll add it to your drink since that's my favorite part, and my favorite scent!\"" << endl;
    hitEnter(response);

    cout <<  "✦ \"Go for it! Do whatever you'd like, it's only fair. Thank you so much!\"" << endl << "You stand and wait until your drink gets called. The sweet smell of vanilla comforts you as you turn to scan the room." << endl;
    hitEnter(response);

    cout << "Well! Now you've got your drink, mission accomplished! What would you like to do now?" << endl; 

    locationChoice = openLocation(0, locations, 2, SIZE); // call upon locationChoice function

    if (locationChoice == 1) // if locationChoice returns 1
    {
        cout << "You grab a seat near the drink bar -- the heart of the rustle and bustle of the café." << endl << "You observe the baristas behind the counter, noticing Leon's particularly swift movements and casual chatter with his coworkers." << endl << "As if sensing your gaze, Leon glances over to look at you, and he smiles a bit." << endl;
        hitEnter(response);
        
        cout << endl << "\"Hey! How's the drink? I didn't do a shabby job, did I?\"" << endl << "Leon jokes." << endl << "✦ \"No, it's great, thank you again! I don't know how I've never visited before, the coffee is way better here.\"" << endl;
        hitEnter(response);
        
        cout << endl << "\"Oh definitely. Obivously, it's 'cause I'm here.\"" << endl << "Leon grins." << endl << "You laugh a bit in response." << endl;
        hitEnter(response);
        
        cout << "✦ \"On second thought, I take it back. That vanilla was a terrible idea!\"" << endl << "Leon's laugh rings throughout the café. ⇡❤" << endl;
        characters[0].addAffection(2);
        hitEnter(response);
        
        cout << endl << "You and Leon continue to chat for a bit longer until he has to go back to work." << endl;
        
        if(cell < 1) // if user doesn't have Leon's number
        {
            cout << endl << "He seems like a fun person to be around." << endl;
            hitEnter(response);
        
            cout << endl << "❥ Maybe you want to get his contact info to talk to him some more?" << endl; // ask for user input
            
            cout  << "Yes" << setw(10) << "No" << endl;
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
            while(search(YesNo, '%') != 0) // check for user error
            {
                getline(cin, YesNo);
                YesNo = uppercase(YesNo);
            }

            if(YesNo == "YES") // if user inputs "YES"
            {
                cout << "⇡❤" << endl << endl;
                characters[0].addAffection(3);
                cell++;
                cout << "You catch Leon when he was finished with a customer. He smiles and exchanges his number with you, before he turns to help out his coworker." << endl;
            }
            else // if "NO"
            {
                cout << "Well, maybe it's fine. You don't particularly feel like bothering him about it." << endl;
            }
        }
            
        cout << endl << "You figure it's probably a good time to head out. You move to grab your drink and leave, but you accidently knock it over! Shoot!" << endl << "There's a small mess on the table now, but nothing too bad. At least there's nothing on you." << endl;
        hitEnter(response);
        
        cout << endl << "❥ Do you want to clean up the mess?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;

        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if(YesNo == "YES") // if user inputs "YES"
        {
            cout << "⇡❤" << endl << endl; 
            characters[0].addAffection(3);
            cout << "You quickly get some napkins and clean up the mess. Seeing as how the baristas are occupied, you don't want to cause them any more trouble." << endl << "You throw away the napkins and take your leave." << endl;
            hitEnter(response);

            cout << endl << "Leon catches you leaving out of the corner of his eye. He looks towards the seats near the drink bar, noticing the cleaned spot." << endl << "He's relieved you took care of it, and smiles softly before resuming work." << endl;
            hitEnter(response);
            cout << "「END OF WEEK 2」" << endl;
            hitEnter(response);
        }
        else // if "NO"
        {
            cout << "⇣❤" << endl << endl;
            characters[0].subAffection(3);
            cout << "You shrug, not a big deal. The barista's are going to clean up the café anyways, and beisdes, you gotta head out." << endl << "You take your leave." << endl;
            hitEnter(response);
            
            cout << endl << "Leon catches you leaving out of the corner of his eye. He looks towards the seats near the drink bar, noticing the mess." << endl << "He frowns, feeling somewhat slighted. He's not willing to confront you about it, though." << endl << "He sighs, making a note to take care of the mess later." << endl;
            hitEnter(response);

            cout << "「END OF WEEK 2」" << endl;
            hitEnter(response);
        }

    }
    else if(locationChoice == 2) // if locationChoice returns 2
    {
        cout << "A glance back and you see Leon, busy making drinks. You turn and decide to sit down at an empty table to enjoy your drink." << endl << "Pulling out your phone, you scroll through some news, sift through some emails, and respond to some messages." << endl << "You suddenly look down and realize your drink's all gone! How long have you been here? Who knows. Probably time to head home." << endl;
        hitEnter(response);
        
        random = randomFunction(); // random event
        if (random <= 5)
        {
            cout << "You want to thank Leon for his kindness, but he's still pretty busy." << endl << "You decide to leave a little thank-you note at the bar for Leon." << endl 
            << "You're gone by the time he read your note, but your message made his whole day. ⇡❤" << endl;
            characters[0].addAffection(2);
        }

        cout << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }
    else if(locationChoice == 3) // if locationChoice returns 3
    {
        cout << "A glance back and you see Leon, busy making drinks. You turn to exit the café, content with your drink. You decide to enjoy a seat outside in the wonderful weather." << endl << "You start to think about some work you need to get done, and you get lost in thought for a bit." << endl << "You suddenly look down and realize your drink's gone stale! Drat! Well, looks like it's a good time to head home, anyways." << endl;
        hitEnter(response);
        
        cout << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }
    else
    {
        cout << "A glance back and you see Leon, busy making drinks. You turn to exit the café, content with your drink. Time to head home." << endl;
        hitEnter(response);
        
        cout << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }

// ---------------------------------------------------------------------------------------------

    if(cell < 1) // if user doesn't have Leon's number
    {
        cout << "「END OF LEON PLAYTHROUGH」" << endl;
        hitEnter(response);
        return;
    }
    else
    {
        cout << "「WEEK 3」" << endl;
        
        cout << endl << "Surprise! You got all your work done yesterday, and now you have the weekend free!" << endl << "Today's a great day to do something fun. Let's see who's free to hang out!" << endl;
        hitEnter(response);
        
        cout << endl << "You open your phone to see a message from Leon." << endl << "You were last talking about baking, and he had sent you a simple cake mug recipe." << endl;
        hitEnter(response);
        
        cout << "Hey! Maybe you should ask Leon if he's free to hang out. You two could bake cookies!" << endl;
        hitEnter(response);
        
        cout << endl << "❥ Should you invite Leon over?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;

        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if(YesNo == "YES") // if user inputs "YES"
        {
            cout << "⇡❤" << endl << endl;
            characters[0].addAffection(2);
            
            cout << "You invite Leon over to your place for some baking. You wait patiently for his response." << endl << "You hear an alert, and check your phone." << endl;
            hitEnter(response);
            
            cout << "\"Leon: That sounds awesome! I'll be over soon!\"" << endl;
            hitEnter(response);
            
            cout << endl << "You're setting up the kitchen and getting out some ingredients when you hear a knock at your door." << endl;
            hitEnter(response);
            
            cout << endl << "You open your door to see Leon, with a small tin in hand." << endl << "\"Hey! I hope you don't mind, I love baking and I had some leftover pastries from last night!" << endl << "Leon grins, offering the tin." << endl;
            hitEnter(response);
            
            if (characters[0].getAffectionLevel() >= 10) // if affection above certain threshold
            {
                cout << "You don't notice the small blush creeping up his neck." <<  endl;
            }
            
            cout << endl << "✦ \"Leon! That's really nice of you, I appreciate it very much!\"" << endl << "You usher him inside, and the two of you get started on the baking." << endl; 
            hitEnter(response);
            
            cout << endl << "✦ \"You're really good at baking Leon! These cookies are going to turn out awesome!\"" << endl << "Leon laughs." << endl << endl << "\"Thank you! I've been doing it since I was pretty young -- I have quite the sweet tooth, so I bake all the sweets I want." << endl;
            hitEnter(response);
            
            cout << endl << "✦ \"Why don't I just pay you to bake me sweets? I won't ever need to go out again.\"" << endl << endl << "\"Ha! That's alright, I quite like giving gifts to people, anyways. And besides, I don't want your money!\"" << endl;
            hitEnter(response);
            
            cout << endl << "✦ \"What?! Then what am I supposed to give you in return? I have to pay you back somehow!\"" << endl << "You replied, laughing." << endl;
            hitEnter(response);
            
            cout << endl << "Leon turns to face you intently, softly smiling at you." << endl << "\"Pay me back, hm? Well, you know what you can do for me?\"" << endl;
            hitEnter(response);
            
            cout << endl << "His eyes bore into yours, and you start to get a bit nervous from his gaze." << endl << "✦ \"What, what is it?\"" << endl;
            hitEnter(response);
            
            cout << endl << "Leon's smile suddenly turns devious and he hits you straight in the face with a handful of flour." << "\"You can take this!!\"" << endl << "He laughs at your demise." << endl;
            hitEnter(response);
            
            cout << endl << "Things get...messy...to say the least, and at the end of it, you're both covered head to toe in flour and laughing." << endl;
            hitEnter(response);

            cout << endl << "\"Alright alright, that's enough, let's not forget these cookies!\"" << endl << "Says Leon, brushing some flour off the top of his head." << endl;
            hitEnter(response);
            
            cout << endl << "\"By the way, what kind of cookies are we making?\"" << endl << "He asks." << endl << endl << "✦ \"I was thinking of sugar doodle cookies with crème.\"" << endl;
            hitEnter(response);
            
            cout << endl << "\"Oh sweet! What kind of crème? I can help you prepare that too.\"" << endl << "You pause for a second to think." << endl;
            hitEnter(response);

            cout << endl << "✦ \"Hmm, I was thinking...well, your favorite scent! That'll be our kind of crème!\"" << endl;
            hitEnter(response);
            
            cout << endl << "Leon laughs." << endl << "\"What? My favorite? You don't know my favorite scent!\"" << endl;
            hitEnter(response);
            
            cout << endl << "✦ \"Yes I do! You told me! I know what your favorite is!\"" << endl;
            
            cout << endl << "❥ (What is Leon's favorite scent? Enter below)" << endl; // ask for user input
            
            getline(cin, answer);
            answer = uppercase(answer);
            
            if (answer == "VANILLA") // if user input correct
            {
                cout << "⇡❤" << endl << endl;
                characters[0].addAffection(5);
                
                cout << endl << "Leon laughs in amazement." << endl << "\"It totally is! I'm surprised you remember!" << endl; 
                
                cout << endl << "He's grinning from ear to ear, and it's got you smiling too." << endl;
                hitEnter(response);
            }
            else // if user input not correct
            {
                cout << endl << "\"Leon flicks your forehead with his finger, chuckling.\" << endl << \"Told you! You don't know what it is. It's vanilla!\"" << endl;
                hitEnter(response);

                cout << endl << "✦ \"Well, whatever!\"" << endl << "You scoff at him. Rats! You thought you had it!" << endl;
                hitEnter(response);
            }

            cout << endl << "Two hours later, the two of you finished the sugar doodle vanilla cookies, content with your hard work and delicious food." << endl;
            hitEnter(response);
            
            cout << endl << "It's late in the evening now, and Leon's about ready to leave." << endl << "\"Hey, I really had a fun time today. Thanks a lot for having me over, we should hang out again soon.\"" << endl;
            hitEnter(response);
            
            if (answer == "VANILLA") // if user input correct
            {
                cout << endl << "Leon smiles fondly at you, holding eye contact for a bit before he suddenly turns quickly to leave." << endl << "He's happy you remembered what he told you, and he's quick to hide any redness in his face." << endl;
                hitEnter(response);

                cout << "「END OF WEEK 3」" << endl;
                cout << "「END OF LEON PLAYTHROUGH」" << endl;
                hitEnter(response);
                return;
            }
            
            cout << endl << "Leon flashes you another of his bright smiles, and he takes his leave." << endl;
            hitEnter(response);
            
            cout << "「END OF WEEK 3」" << endl;
            cout << "「END OF LEON PLAYTHROUGH」" << endl;
            hitEnter(response);
            return;
        }
        else // if "NO"
        {
            cout << "Hm, guess not. He could be busy. You could bake those cookies yourself no problem! …Right?" << endl;
            hitEnter(response);

            cout << endl << "After several hours and some burns here and there, finally!!! You've got some...hard...ashen...cookies. Maybe this wasn't a good idea, after all..." << endl;
            hitEnter(response);

            cout << "「END OF WEEK 3」" << endl;
            cout << "「END OF LEON PLAYTHROUGH」" << endl;
            hitEnter(response);
        }
    }

return;
}

void Simulator::AugustPlaythrough(Character characters[], Location locations[], const int SIZE, int locationChoice, string response, string YesNo, string answer, int random) // Dialogue for August
{
    int bell = 0, cell = 0, introduce = 0; // initalize necessary variables

    cout << endl << "「WEEK 1」" << endl;
    cout << endl << "Today is Monday. It's time to head to your first class of the day, and you're determined to start your week off strong! " << endl << endl << "Well, at least, that was the plan. You had slept in, and now you've got to book it to class." << endl;
    hitEnter(response);

    cout << endl << "You rush to calculus, and -- argh! Someone's nabbed your usual seat! No surprise there." << endl << "And the professor's already flying through content. Great." << endl;
    hitEnter(response);

    cout << endl << "You sit down quickly at a nearby seat." << endl << "As you set down your belongings, you glance around the aisle and meet the eyes of the person sitting next to you." << endl << endl << "They seem rather annoyed at your hasty entrance. Geez." << endl;
    hitEnter(response);

    cout << endl << "You quickly look away, focusing on the professor as they begin to write on the board." << endl << "The professor throw out a problem for your class to work through, and encourages you to turn and talk to a neighbor." << endl;
    hitEnter(response);

    cout << endl << "You start working out the problem, so far so good, until -- shoot. You're stumped. You don't remember how to do this part." << endl;
    hitEnter(response);

    cout << endl << "You peek to your right, the only person sitting adjacent to you. Maybe you should ask them what they did." << endl;
    hitEnter(response);
    
    cout << endl << "❥ Do you want to try it?" << endl; // ask for user input
    cout  << "Yes" << setw(10) << "No" << endl;

    getline(cin, YesNo);
    YesNo = uppercase(YesNo);
    while(search(YesNo, '%') != 0) // check for user error
    {
        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
    }

    if(YesNo == "YES") // if user input "YES"
    {
        cout << "⇡❤" << endl << endl;
        characters[1].addAffection(1);

        cout  << "✦ \"Hey. What answer did you get?\"" << endl;

        cout << endl << "They barely spare you a glance." << endl << "✦ \"...Uh, I'm having a bit of trouble on this problem.\"" << endl << "You say, attepting to get their attention." << endl << endl << "You watched their eyes narrow before they turn to look at you." << endl;
        hitEnter(response);

        cout << endl << "\"What. What is it.\"" << endl << "They ask, flatly." << endl << "Geez. You're starting to regret asking them for help." << endl; 
        hitEnter(response);

        cout << endl << "✦ \"I'm not really getting anywhere with this problem. I'm not sure where I went wrong.\"" << endl;
        hitEnter(response);

        cout << endl << "They sigh, and then motion with their hand." << endl << "\"Let me see.\"" << endl << "And you hand them your work." << endl;
        hitEnter(response);

        cout << endl << "You wait in silence, the atmostphere somewhat tense." << endl << "\"There. You put down the wrong sign.\"" << endl << endl << "You look to where they're pointing at your page." << endl;
        hitEnter(response);

        cout << endl << "✦ \"Oh, yeah, I see. Thank you.\"" << endl << "You say, quickly, not wanting to stay in the conversation for much longer." << endl;
        hitEnter(response);

        cout << endl << "They give a short grunt in response, and then turn back towards their paper. They say nothing else." << endl << "Well, so much for that. At least you got what you needed." << endl;
        hitEnter(response);

        cout << endl << "The professor begins again, and you're relieved you don't have to sit in that silence anymore." << endl;
        hitEnter(response);

        cout << endl << "Class ends without a problem. You get up to leave and see that person from earlier doing the same." << endl << "You realize that you missed a lot of content, since you were late." << endl;
        hitEnter(response);

        cout << endl << "❥ Are you up for asking them to lend you some notes?" << endl;
        cout  << "Yes" << setw(10) << "No" << endl;
    }
    else // if "NO"
    {
        cout << endl << "Nah, guess not. You turn back towards your paper and continue working out the problem, searching for where you went wrong." << endl;
        hitEnter(response);
        
        cout << endl << "Class ends without a problem. You get up to leave and see that person from earlier doing the same." << endl << "You realize that you missed a lot of content, since you were late." << endl;
        hitEnter(response);

        cout << endl << "❥ Are you up for asking them to lend you some notes?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;
    }

    getline(cin, YesNo);
    YesNo = uppercase(YesNo);
    while(search(YesNo, '%') != 0) // check for user error
    {
        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
    }

    if(YesNo == "YES") // if user input "YES"
    {
        cout << "⇡❤" << endl << endl;
        characters[1].addAffection(1);

        cout << "✦ \"Uh, hey, I hope I'm not bothering you too much when I ask you this, but is it alright if I get some notes from you? I was late and missed a lot of stuff.\"" << endl << endl << "You see that person pause for a bit before they turn to look at you." << endl;
        cout << endl << "You see that same annoyed expression from before." << endl << endl << "\"Sucks.\"" << endl;
        hitEnter(response);

        cout << "Then they turn away without a word, leaving you standing there, surprised." << endl << "Wow. That's a jerk move. They could've just said no." << endl << "You huff at their response, but brush it off. Whatever, you'll figure it out." << endl << endl;
        hitEnter(response);

        cout << "Looking down to make sure you have all your stuff before you leave, you see something shining gold on the ground." << endl << "What? What is that....?" << endl;
        hitEnter(response);
    
        cout << "You pick it up and it's...a bell? A small golden bell, with cherry-brown straps. How strange. Where did it come from?" << endl;
        hitEnter(response);

        cout << endl << "❥ Do you want to hold onto it?" << endl; // ask for user input 
        cout  << "Yes" << setw(10) << "No" << endl;
    
        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if(YesNo == "YES") // if user input "YES"
        {
            cout << "⇡❤" << endl << endl;
            characters[1].addAffection(1);
            bell++;

            cout << endl << "It's quite charming, and you don't really know what to do with it, but you decide to pocket it anyways." << endl;
            hitEnter(response);
            
            cout << endl << "You take your leave. Hopefully, the rest of today will make up for this morning's rough start." << endl << endl;
            hitEnter(response);
            
            cout << "「END OF WEEK 1」" << endl;
            hitEnter(response);
        }
        else // if "NO"
        {
            cout << endl << "Guess not. Better not touch something that's not yours, and you don't know who it belongs to." << endl;
            hitEnter(response);

            cout << endl << "You take your leave. Hopefully, the rest of today will make up for this morning's rough start." << endl << endl;
            hitEnter(response);

            cout << "「END OF WEEK 1」" << endl;
            hitEnter(response);
        }
    }
    else // if "NO"
    {
        cout << endl << "Eh, forget it. Not worth the effort. You'll probably be fine." << endl << "You go on your merry way to your next class. Hopefully, the rest of today will make up for this morning's rough start." << endl << endl;
        hitEnter(response);

        cout << "「END OF WEEK 1」" << endl;
        hitEnter(response);
    }

// ---------------------------------------------------------------------------------------------

    cout << "「WEEK 2」" << endl;

    cout << endl << "Finally! The weekend could not arrive any faster! After a busy school week, you deserve a fun little outing, don't you think?" << endl;
    hitEnter(response);

    cout << endl << "It's been a while since you've visited the record shop. You love the atmostphere there, and really enjoy finding records to add to your collection." << endl << "To the record shop, it is!" << endl;
    hitEnter(response);

    cout << endl << "You enter the shop, immediately hit with a wave of excitement. You take a second to absorb the view, before moving to scan the aisles." << endl; 
    hitEnter(response);

    cout << endl << "You head to a random aisle, exploring and looking at covers that catch your eye. Oh! Suddenly, you remember one that you've been wanting for a while." << endl;
    hitEnter(response);

    cout << endl << "You turn the corner to the aisle you're looking for, and you're surpised to spot someone already there, looking through some items." << endl; 
    hitEnter(response);

    cout << endl << "They're standing in front of the arrangement of records you wanted to look at. Hm. They probably won't mind if you went to grab yours real quick." << endl;
    hitEnter(response);

    cout << endl << "You head towards the display, and you see them turn their attention towards you." << endl << "Wait a second...they look kind of familiar." << endl;
    hitEnter(response);

    cout << endl << "Oh!...Oh. Okay. It's that person. From your class. Of all the people you could've run into..." << endl;
    hitEnter(response);    

    cout << endl << "You quickly glance away, focusing on finding your record quickly. You could still feel their eyes on you, observing." << endl;
    hitEnter(response);

    cout << endl << "What record are you looking for?" << endl << endl;
        
    locationChoice = openLocation(1, locations, 1, SIZE); // call upon locationChoice function

    if(locationChoice == 1) // if locationChoice returns 1
    {
        cout << "⇡❤" << endl << endl;
        characters[1].addAffection(3);
    }

    cout << endl << "You skim the labels until you come across the artist you were looking for. Aha! There it! ....isn't...." << endl << "There are records for the artist's other albums, but not the one you were looking for." << endl;
    hitEnter(response);

    cout << endl << "You sigh, dismayed at your luck. As you turn to leave, you glance over at that person, eyes passing over the record they had in their hand." << endl << "You do a double take." << endl;
    hitEnter(response);

    cout << endl << "Whoa! Wait a second, that's the one you wanted! Did they grab the last one? That's so unlucky!" << endl;
    hitEnter(response);

    cout << endl << "\"...Are you looking for this?\"" << endl;
    hitEnter(response);

    cout << endl << "You hear them ask you. You're surprised at their question." << endl << "✦ \"Oh, uh, yeah. But it's alright, you got to it first.\"" << endl << "You say quickly." << endl;
    hitEnter(response);

    cout << endl << "There's a pause, and you wait for what they have to say." << endl << endl << "\"Take it.\"" << endl << endl << "You're startled by their offer." << endl;
    hitEnter(response);

    cout << endl << "✦ \"Oh, no! It's alright, you don't have to do--\"" << endl << endl << "\"Just take it. I won't say it again.\"" << endl;
    hitEnter(response);

    cout << endl << "✦ \"....Thank you.\"" << endl << endl << "They don't say anything." << endl;

    if(locationChoice == 1) // if locationChoice returns 1
    {
        cout << endl << "There's another pause, and you're not sure if they're even going to say anything." << endl << "You're about to turn and leave, when, finally, they speak up." << endl;
        hitEnter(response);

        cout << endl << " \"...You have good taste. That's one of my favorites.\"" << endl;
        hitEnter(response);

        cout << endl << "✦ \"..Oh! Yeah, uh, thank you. I've been a fan of their music for a while now. I've been meaning to get this one.\"" << endl << endl << "\"Hm.\"" << endl;
        hitEnter(response);
    }

    cout << endl << "The uneasy feeling doesn't quite leave you, but you feel like filling the empty space of conversation." << endl;
    hitEnter(response);

    cout << endl << "❥ Should you say something?" << endl; // ask for user input
    cout  << "Yes" << setw(10) << "No" << endl;

    getline(cin, YesNo);
    YesNo = uppercase(YesNo);
    while(search(YesNo, '%') != 0) // check for user error
    {
        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
    }

    if(YesNo == "YES") // if user input "YES"
    {
        cout << "⇡❤" << endl << endl;
        characters[1].addAffection(1);
        introduce++;

        cout << endl << "✦ \"...By the way, my name is " << endl << characters[4].getUsername() << ". I appreciate the kindness.\"" << endl;
        hitEnter(response);

        cout << endl << "\"...August. And...you're welcome.\"" << endl;
        hitEnter(response);
    }
    else // if "NO"
    {
        cout << "...Nah, it's alright. It'll be fine." << endl;
        hitEnter(response);
    }

    cout << "You offer a small smile, and then excuse yourself to go to the register. You finish checking out, and when you look around, you don't see them anywhere." << endl;
    hitEnter(response);

    cout << "Well! You've got the record. You exit the shop, and observe your surroundings." << endl << "You see people walking by and hear faint scuffling nearby, around the corner of the shop." << endl;
    hitEnter(response);
    
    cout << endl << "What would you like to do now?" << endl; 

    locationChoice = openLocation(1, locations, 2, SIZE); // call upon locationChoice function

    if (locationChoice == 1) // if locationChoice returns 1
    {
        cout << endl << "You head in the direction of the noise, the scuffling slowly growing louder and louder. You round the corner and stop dead in your tracks -- in front of you, a meowing stray cat." << endl;
        hitEnter(response);

        if (introduce > 0) // if user got introduction
        {
            cout << endl << "Even more surprising than that, you see August, their back turned to you and their outstretched hand petting the cat." << endl;
            hitEnter(response);
        }
        else // user didn't get intro
        {
            cout << endl << "Even more surprising than that, you see that person from the record shop, their back turned to you and their outstretched hand petting the cat." << endl;
            hitEnter(response);
        }
            
        cout << endl << "You open your mouth to say something, when suddenly --" << endl << endl << "\"Shh. Don't scare it away.\"" << endl;
        hitEnter(response);

        cout << endl << "You immediately stop, and freeze, trying not to make any sudden movements." << endl << "You listen to them gently hushing the meowing stray." << endl;
        hitEnter(response);

        cout << endl << "\"Hey, it's alright. I'm here with you. Don't be scared. You're alright.\"" << endl << "You're surprised to see how gentle and sweet they are towards the cat." << endl;
        hitEnter(response);

        cout << endl << "❥ Would you like to stay?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;

        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if (YesNo == "YES") // if user input "YES"
        {
            cout << "⇡❤" << endl << endl;
            characters[1].addAffection(3);

            cout << endl << "You slowly crouch down next to them, carefully and cautiously offering out your hand to the cat." << endl << "It sniffs your hand, and allows you to pet it, purring softly." << endl;
            hitEnter(response);

            cout << endl << "Out of the corner of your eye, instead of the usual frown or scowl, you see a soft smile." << endl;
            hitEnter(response);

            cout << endl << "✦ \"It's really cute. I wonder what it's doing out here all alone.\"" << endl << "You say, stroking the stray's soft ears." << endl;
            hitEnter(response);         

            if(introduce > 0) // if user got intro
            {
                cout << endl << "The cat suddenly gets up and stalks over to August, rubbing up against them and purring." << endl << "A soft chuckle leaves their lips." << endl << endl << "\"What, what is it? What do you need, hm?\"" << endl << "August murmurs." << endl;
                hitEnter(response);

                cout << endl << "You smile softly at how sweet they are to the stray. It's a comforting atmosphere, completely different from before." << endl << endl << "✦ \"That cat seems to like you a lot.\"" << endl;
                hitEnter(response);
            }
            else // if user didn't get intro
            {
                cout << endl << "The cat suddenly gets up and stalks over to the individual, rubbing up against them and purring." << endl << "A soft chuckle leaves their lips." << endl << endl << "\"What, what is it? What do you need, hm?\"" << endl << "They murmur." << endl;
                hitEnter(response);

                cout << endl << "You smile softly at how sweet they are to the stray. It's a comforting atmosphere, completely different from before." << endl << endl << "✦ \"I'm " << characters[4].getUsername() << ". That cat seems to like you a lot.\"" << endl;
                hitEnter(response);

                cout << endl << "\"...August.\"" << endl << "They say, simply." << endl;
                hitEnter(response);
            }
                
            cout << endl << "The cat nuzzles into August's side." << endl << endl << "\"..Yeah, it looks like it.  It reminds me a lot of my own cat, actually.\"" << endl << "You perk up at the mention of another cat." << endl;
            hitEnter(response); 

            cout << endl << "✦ \"Aw. That's nice. I love cats, they're really lovely. What's your cat's name?\"" << endl;
            hitEnter(response);

            cout << endl << "\"Chester. He's an orange somali, and really troublesome, but very sweet.\" ⇡❤" << endl << "August's smile grows as they talk about their pet. They have a wonderful smile." << endl;
            hitEnter(response);
            characters[1].addAffection(2);

            cout << endl << "You continue chatting about cats and other animals, at large. Turns out, August has quite the soft spot for animals." << endl;
            hitEnter(response);

            cout << endl << "You're thinking about asking them for their contact info, you quite like this side of them and you've grown comfortable in their presence." << endl << "Plus, you're hoping to see what their cat looks like!" << endl;
            hitEnter(response);

            cout << endl << "❥ Do you want to ask for their contact info?" << endl; // ask for user input
            cout  << "Yes" << setw(10) << "No" << endl;

            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
            while(search(YesNo, '%') != 0) // check for user error
            {
                getline(cin, YesNo);
                YesNo = uppercase(YesNo);
            }

            if(YesNo == "YES") // if user inputs "YES"
            {
                cout << "⇡❤" << endl << endl;
                cell++;
                characters[1].addAffection(3);

                cout << endl << "August hesitates for a bit at your question. You watch them as they consider their next words." << endl << endl << "\"...Why?\"" << endl;
                hitEnter(response);

                cout << endl << "✦ \"...Would you believe me if I told you I wanted pictures of your cat..?\"" << endl << "You offer, meekly, hoping it was convincing enough." << endl;
                hitEnter(response);

                cout << endl << "They gaze at you for a bit, seemingly contemplating whether you're messing with them or not." << endl << "After a bit of time..." << endl << endl << "\"Okay. Here.\"" << endl;
                hitEnter(response);

                cout << endl << "The two of you exchange numbers, and you smile softly. You didn't think you'd get this far at all." << endl << "August looks away from you, distracting themself by petting the stray." << endl;
                hitEnter(response);
            }
            else // if "NO"
            {
                cout << endl << "Well, maybe you don't need to. They might just say no, anyways." << endl;
            }

            cout << endl << "You glance at the time in your phone, and figure it's a good time to head home. You bid August goodbye, and you leave them -- still with the stray." << endl << "You had a lot of fun today, and you're excited to head home and end the day listening to your new record." << endl;
            hitEnter(response);

            cout << "「END OF WEEK 2」" << endl;
            hitEnter(response); 
        }
        else // if "NO"
        {
            cout << "⇣❤" << endl << endl;
            characters[1].subAffection(3);

            cout << endl << "You decide not to step into this situation, and take your leave." << endl << "However, you accidently step on some loose gravel and stumble backwards, and startle the cat." << endl;
            hitEnter(response);

            if(introduce > 0)
            {
                cout << endl << "The cat hisses and claws at August, and they yank their arm back in pain. The cat runs away, leaving you and a glowering August." << endl << "They turn around and shoot you a dirty look." << endl;
                hitEnter(response);
            }
            else
            {
                cout << endl << "The cat hisses and claws at the person, and they yank their arm back in pain. The cat runs away, leaving you and a glowering individual." << endl << "They turn around and shoot you a dirty look." << endl;
                hitEnter(response);            
            }

            cout << endl << "You quickly apologize and offer to patch them up, but they huff in annoyance and turn away." << endl << "You take that as a sign to leave, and you do exactly that. You didn't mean to, honest!" << endl;
            hitEnter(response); 

            cout << "「END OF WEEK 2」" << endl;
            hitEnter(response); 
        }
    }
    else if(locationChoice == 2) // if locationChoice returns 2
    {
        cout << "Let's grab a yummy snack at the convenience store over there!" << endl << "You enter the store, and after some searching, you find some peanut-butter-filled pretzels. Score!" << endl;
        hitEnter(response);
        
        random = randomFunction(); // random event
        if (random <= 5)
        {
            cout << endl << "You're standing in line, waiting for your turn to check out. You suddenly see some movement out of the corner of your eye." << endl;
            hitEnter(response);

            if(introduce > 0) // if user got intro
            {
                cout << endl << "Hey! It's August! You see them clutching their arm, looking as if they're in some pain. They rush to the bathroom." << endl;
                hitEnter(response);

                cout << endl << "Are they hurt? You wonder. Did they fall or something?" << endl << "Your thoughts are interrupted by the cashier greeting you." << endl;
                hitEnter(response);

                cout << endl << "You glance over to the side and see packs of bandaids. You add a box to your purchase." << endl << endl << "You catch August on their way out, and offer them the bandaid. They're quite surprised at your consideration." << endl;
                hitEnter(response);

                cout << endl << "You gently reach out for their arm, and place the bandaid carefully on the wound. They turned out to be several fresh cat scratches." << endl;
                hitEnter(response);

                cout << endl << "You're too busy to notice the fierce blush on August's cheeks, and they've practically turned their entire face away to avoid looking at you." << endl;
                hitEnter(response);

                cout << endl << "They grumble out a quick 'thanks' and leave. ⇡❤" << endl << endl << "You take your leave as well. You hope they're not in too much pain." << endl;
                hitEnter(response);
                characters[1].addAffection(2);
            }
            else // user didn't get intro
            {
                cout << endl << "Hey! It's that person from the record shop! You see them clutching their arm, looking as if they're in some pain. They rush to the bathroom." << endl;
                hitEnter(response);

                cout << endl << "Are they hurt? You wonder. Did they fall or something?" << endl << "Your thoughts are interrupted by the cashier greeting you." << endl;
                hitEnter(response);

                cout << endl << "You glance over to the side and see packs of bandaids. You add a box to your purchase." << endl << endl << "You catch them on their way out, and offer them the bandaid. They're quite surprised at your consideration." << endl;
                hitEnter(response);

                cout << endl << "You gently reach out for their arm, and place the bandaid carefully on the wound. They turned out to be several fresh cat scratches." << endl;
                hitEnter(response);

                cout << endl << "You're too busy to notice the fierce blush on their cheeks, and they've practically turned their entire face away to avoid looking at you." << endl;
                hitEnter(response);

                cout << endl << "They grumble out a quick 'thanks' and leave. ⇡❤" << endl << endl << "You hope they're not in too much pain." << endl;
                hitEnter(response);
                characters[1].addAffection(2);
            }
        }

        cout << endl << "Content, you take your leave." << endl;
        hitEnter(response);

        cout << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }
    else if(locationChoice == 3) // if locationChoice returns 3
    {
        cout << "You take a seat at bench to get some shade. You look down, and run your hands along the art cover of the record." << endl << "You sit and marvel at the item, drinking in all the details." << endl;
        hitEnter(response);

        cout << "You can't wait to get home and play the record later. It'll be a great addition to your collection!" << endl;
        hitEnter(response);
        
        cout << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }
    else // if locationChoice returns 0
    {
        cout << "Yeah, you should head home. Let's check out how that record performs!" << endl;
        hitEnter(response);
        
        cout << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }

// ---------------------------------------------------------------------------------------------

if(cell < 1 || bell < 1) // if user hasn't gotten August's number nor the bell
    {
        cout << "「END OF AUGUST PLAYTHROUGH」" << endl;
        hitEnter(response);
        return;
    }
    else
    {
        cout << "「WEEK 3」" << endl;
        
        cout << endl << "Surprise! You got all your work done yesterday, and now you have the weekend free!" << endl << "Today's a great day to do something fun. Let's see who's free to hang out!" << endl;
        hitEnter(response);
        
        cout << endl << "You open your phone to see a message from August." << endl << "You had asked them about their cat, and they had sent you a really adorable picture." << endl;
        hitEnter(response);

        cout << endl << "Hey! Maybe you should ask August if they're free to hang out. You two could listen to your records!" << endl;
        hitEnter(response);

        cout << endl << "❥ Should you invite August over?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;

        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }
    
        if(YesNo == "YES") // if user input "YES"
        {     
            cout << "You invite August over to your place to listen to music. You wait patiently for their response." << endl << "You hear an alert, and check your phone." << endl;
            hitEnter(response);

            cout << "\"August: No.\"" << endl;
            hitEnter(response);

            cout << endl << "You grumble, and then sigh. You glance down at your phone again." << endl << "Your eyes fall upon the picture of their cat, scanning it's face, when something suddenly strikes your attention." << endl;
            hitEnter(response);

            cout << endl << "There was a cherry-brown collar around the neck of the cat...with a small golden bell." << endl;
            hitEnter(response);

            cout << endl << "Your eyes widened, and you straightened up. That bell you picked up a long time ago, could it be?" << endl << "You rummage through your items trying to find it, when at long last you retrieve it from the bottom of your backpack." << endl;
            hitEnter(response);

            cout << endl << "Indeed, it was the collar you had found weeks ago." << endl << "You pick up your phone to messge August, sending a picture of it as well." << endl;
            hitEnter(response);

            cout << endl << "They respond immediately." << endl << endl << "\"August: Where the hell did you get from?\"" << endl;
            hitEnter(response);

            cout << endl << "✦ \"I'll explain later, but you can come over to pick it up, okay?\"" << endl << endl << "\"August: Fine. Be there soon.\"" << endl;
            hitEnter(response);

            cout << endl << "You're wiping off some dirt and such from the collar when you hear a knock at your door." << endl;
            hitEnter(response);

            cout << endl << "You open your door to see August, grumbling and running their fingers through their hair." << endl << "You return them the collar and explain how you found it on the ground after class a few weeks ago." << endl;
            hitEnter(response);

            cout << endl << "✦ \"Why do you even have a collar with you in class?\"" << endl << endl << "They roll their eyes at you." << endl << endl << "\"I was going to get the clasp repaired after class.\"" << endl;
            hitEnter(response);

            cout << endl << "✦ \"Ah, I see. Makes sense.\"" << endl << endl << "There's a pause, and August is scratching the back of their head. You wait for them to speak." << endl;
            hitEnter(response);

            cout << endl << "At last, August speaks up." << endl << endl << "\"" << characters[4].getUsername() << "... Thank you. I was looking for this. I appreciate it.\"" << endl;
            hitEnter(response);

            cout << "⇡❤" << endl << endl;
            characters[1].addAffection(2);

            cout << endl << "August is avoiding eye contact with you, scrunching up their nose and looking off to the side." << endl << "The sight makes you chuckle a bit. Seems like it's quite hard for them to say that." << endl;
            hitEnter(response);

            cout << endl << "✦ \"Yes, you're welcome, August.\"" << endl << "You smile." << endl << endl << "There's a bit longer of a pause." << endl;
            hitEnter(response);

            if(characters[1].getAffectionLevel() >= 14) // August's affection above a certain threshold
            {
                cout << endl << "\"...Did you want to listen to music?\"" << endl;
                hitEnter(response);

                cout << endl << "You brighten at the mention. You enthusiastically pull August inside, and the two of you walk over to your record display." << endl << endl << "You didn't notice the blush tipping their ears and flushing their neck." << endl;
                hitEnter(response);

                cout << endl << "You share your records with August, and they listen intently to your words." << endl << "They talk to you about their favorite records, you sit and appreciate the art covers together." << endl;
                hitEnter(response);

                cout << endl << "August pulls out one of your records from the bottom of a small pile. They scan the back of the cover." << endl << "\"These are all classical compositions.\"" << endl << "They muse." << endl;
                hitEnter(response);

                cout << endl << "✦ \"Oh, yeah, my friend gifted me that one last year. She tried to show me how to waltz, but I'm not very good at it!\"" << endl << "You laugh." << endl;
                hitEnter(response);

                cout << endl << "August hums thoughtfully in response." << endl << "You continue on talking about another record she had gifted you, not noticing the steadily growing flush on August's face." << endl;
                hitEnter(response);

                cout << endl << "Out of the blue, August interrupts you." << endl << endl << "\"I can show you.\"" << endl;
                hitEnter(response);

                cout << endl << "You're stunned at the offer. You sputter a bit." << endl;
                hitEnter(response);

                cout << endl << "\"Actually, nevermind. Sorry. Don't worry about it.\"" << endl << "August quickly covers." << endl;
                hitEnter(response);

                cout << endl << "✦ \"O-oh, no it's okay, really. I'd like that, if...you don't mind..?\"" << endl;
                hitEnter(response);

                cout << endl << "They nervously scratch the back of the neck, looking away from you." << endl << "They hesitate." << endl;
                hitEnter(response);

                cout << endl << "\"...Here, stand up. I'll lead.\"" << endl;
                hitEnter(response);

                cout << endl << "They place the record on the turntable and gently lower the needle onto the record." << endl << endl << "Then, they gently take your hands and walk you through the simple box step of a waltz." << endl;
                hitEnter(response);

                cout << endl << "You're surprised at how elegantly they move, patiently guiding you through any mistakes. The two of you sway gently to the music." << endl;
                hitEnter(response);  

                cout << endl << "You dance together to a few songs. During a lull in the track, you smile and speak up." << endl << endl << "✦ \"Do you ever dance with Chester?\"" << endl;
                hitEnter(response);  

                cout << endl << "August laughs softly." << endl << "\"I do actually dance with him, and he is a lot better than you are.\"" << endl;
                hitEnter(response);

                cout << endl << "You laugh at that." << endl << "✦ \"It's not my fault he's got talent! It's because of his breed! It's probably in his genes!" << endl;
                hitEnter(response);

                cout << endl << "August chuckles." << endl << "\"You don't even know what breed he is, anyways.\"" << endl;
                hitEnter(response);

                cout << endl << "✦ \"Yes I do! You told me what breed he is! He's an orange ...\"" << endl;
            
                cout << endl << "(What is Chester's breed? Enter below)" << endl; // ask for user input
                
                getline(cin, answer);
                answer = uppercase(answer);
                
                if (answer == "SOMALI") // if user input correct
                {
                    cout << "⇡❤" << endl << endl;
                    characters[1].addAffection(5);
                    
                    cout << endl << "August's eyes widen in amazement." << endl << "\"Wow, I guess I did tell you. I'm surprised you remember." << endl; 
                    hitEnter(response);

                    cout << endl << "You see them break into a really beautiful, genuinine smile, one you haven't seen before." << endl << "You can't help but smile too, as the two of you continue to sway to the music." << endl;
                    hitEnter(response);
                }
                else // if user input not correct
                {
                    cout << endl << "August snorts at your response." << endl << "\"I told you, you wouldn't know. He's a somali.\"" << endl;
                    hitEnter(response);

                    cout << endl << "✦ \"Well, whatever!\"" << endl << "You scoff at them. Rats! You thought you had it!" << endl;
                    hitEnter(response);
                }

                cout << endl << "After a while, the record finishes playing and you end up playing a few more while chatting and eating a bit." << endl;
                hitEnter(response);
                
                cout << endl << "It's late in the evening now, and August is about to leave." << endl << "\"Thanks for spending time with me, and thank you again for the collar.\"" << endl;
                hitEnter(response);
                
                if (answer == "SOMALI") // if user input correct
                {
                    cout << endl << "August reaches out to gently touch your arm as they say this, holding eye contact for a bit before suddenly turning around quickly to leave." << endl << "There's an intense flush that they know they couldn't hide." << endl;
                    hitEnter(response);

                    cout << "「END OF WEEK 3」" << endl;
                    cout << "「END OF AUGUST PLAYTHROUGH」" << endl;
                    hitEnter(response);
                    return;
                }
                
                cout << endl << "August gives you a soft smile, and then takes their leave." << endl;
                hitEnter(response);
                
                cout << "「END OF WEEK 3」" << endl;
                cout << "「END OF AUGUST PLAYTHROUGH」" << endl;
                hitEnter(response);
                return;
            }
            else // if affection level isn't high enough
            {
                cout << endl << "August suddenly turns around to leave." << endl << "\"I'll be leaving now. Thanks, again.\"" << endl << endl << "And then they were gone as soon as they came." << endl;
                hitEnter(response);

                cout << endl << "You sigh. They came all the way here, they could've at least stayed for a bit. Ah, well. At least they got the collar back." << endl;
                hitEnter(response);

                cout << endl << "You head back inside, making up your mind to get some cleaning done while playing music." << endl;
                hitEnter(response);

                cout << "「END OF WEEK 3」" << endl;
                cout << "「END OF AUGUST PLAYTHROUGH」" << endl;
                hitEnter(response);
                return;
            }
        }
        else // if "NO"
        {
            cout << "Hm, guess not. They could be busy. You could stay in today, and rock out to some music by yourself!" << endl;
            hitEnter(response);

            cout << endl << "You get some cleaning done all the while your record player plays all your favorite music. You deserved this treat! Go you!" << endl;
            hitEnter(response);

            cout << "「END OF WEEK 3」" << endl;
            cout << "「END OF AUGUST PLAYTHROUGH」" << endl;
            hitEnter(response);
        }
    }

return;
}

void Simulator::PiperPlaythrough(Character characters[], Location locations[], const int SIZE, int locationChoice, string response, string YesNo, string answer, int random) // Dialogue for Piper
{
    int cell = 0, introduce = 0; // initialize necessary variables

    cout << endl << "「WEEK 1」" << endl;
    cout << endl << "Today is Monday. It's time to head to your first class of the day, and you're determined to start your week off strong! " << endl << endl << "Well, at least, that was the plan. You had slept in, and now you've got to book it to class." << endl;
    hitEnter(response);

    cout << endl << "You rush to calculus, and -- argh! Someone's nabbed your usual seat! No surprise there." << endl << "And the professor's already flying through content. Great." << endl;
    hitEnter(response);

    cout << endl << "You sit down quickly at a nearby seat." << endl << "As you set down your belongings, you glance around the aisle and meet the eyes of the person sitting next to you." << endl << endl << "They quickly glance away, not meaning to seem rude or anything." << endl;
    hitEnter(response);

    cout << endl << "You turn your focus on the professor as they begin to write on the board." << endl << "The professor throw out a problem for your class to work through, and encourages you to turn and talk to a neighbor." << endl;
    hitEnter(response);

    cout << endl << "You start working out the problem, so far so good, until -- shoot. You're stumped. You don't remember how to do this part." << endl;
    hitEnter(response);

    cout << endl << "You peek to your right, wondering if the person next to you could help you out." << endl;
    hitEnter(response);

    cout << endl << "❥ Do you want to ask them?" << endl; // ask for user input
    cout  << "Yes" << setw(10) << "No" << endl;

    getline(cin, YesNo);
    YesNo = uppercase(YesNo);
    while(search(YesNo, '%') != 0) // check for user error
    {
        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
    }

    if(YesNo == "YES") // if user input "YES"
    {
        cout << "⇡❤" << endl << endl;
        characters[2].addAffection(1);

        cout  << "✦ \"Hey. What answer did you get?\"" << endl;

        cout << endl << "They turn to face you." << endl << "\"Hey! Uh, I'm almost done, just one sec.\"" << endl << endl << "✦ \"Oh sure, no problem! Sorry.\"" << endl;
        hitEnter(response);

        cout << endl << "You give them another moment, before they turn back to you and push their work towards you." << endl << endl << "\"So, it looks like I'm getting 1/2. You?\"" << endl;
        hitEnter(response);

        cout << endl << "✦ \"Er, no, I'm kind of stuck....can I see what you did?\"" << endl << endl << "\"Yeah, go for it!\"" << endl;
        hitEnter(response);

        cout << endl << "✦ \"Oh! Geez, I see, I screwed up my signs right here. That totally fixed it, thank you!\"" << endl << "You say, giving them an appreciative smile." << endl;
        hitEnter(response);

        cout << endl << "\"Hey, no problem! Glad I could help!\"" << endl << "They respond." << endl << endl << "\"I'm Piper, it's nice to meet you.\"" << endl;
        hitEnter(response);

        cout << endl << "✦ \"Likewise! My name is " << characters[4].getUsername() << "!\"" << endl;
        hitEnter(response);
        introduce++;

        cout << endl << "Before Piper could say anything else, the professor begins again." << endl;
        hitEnter(response);

        cout << endl << "The rest of class goes by smoothly, and finishes without a problem." << endl << "You get up to leave and see Piper doing the same." << endl << "You realize that you missed a lot of content, since you were late." << endl;
        hitEnter(response);

        cout << endl << "❥ Are you up for asking them to lend you some notes?" << endl;
        cout  << "Yes" << setw(10) << "No" << endl;
    }
    else // if "NO"
    {
        cout << endl << "Nah, guess not. You turn back towards your paper and continue working out the problem, searching for where you went wrong." << endl;
        hitEnter(response);
        
        cout << endl << "Class ends without a problem. You get up to leave and see your neighbor doing the same." << endl << "You realize that you missed a lot of content, since you were late." << endl;
        hitEnter(response);

        cout << endl << "❥ Are you up for asking them to lend you some notes?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;
    }

    getline(cin, YesNo);
    YesNo = uppercase(YesNo);
    while(search(YesNo, '%') != 0) // check for user error
    {
        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
    }

    if(YesNo == "YES") // if user input "YES"
    {
        cout << "⇡❤" << endl << endl;
        characters[2].addAffection(1);

        if (introduce > 0) // if user did get introduction
        {
            cout << endl << "✦ \"Uh, hey, I hope I'm not bothering you too much when I ask you this, but is it alright if I get some notes from you? I was late and missed a lot of stuff.\"" << endl << endl << "Piper looks over their shoulder and nods without a moment of hesitation." << endl;
            hitEnter(response);
        }
        else
        {
            cout << endl << "✦ \"Uh, hey, I hope I'm not bothering you too much when I ask you this, but is it alright if I get some notes from you? I was late and missed a lot of stuff.\"" << endl << endl << "They look over their shoulder and nod without a moment of hesitation." << endl;
            hitEnter(response);
        }
        
        cout << endl << "\"Of course! Here, let's go out into the hallway, you can take a picture of my notes right now. I don't have class yet.\"" << endl;
        hitEnter(response);

        cout << endl << "What a godsend! They're awesome!" << endl << endl << "✦ \"Hey, thank you so much for helping me out, I really appreciate it!\"" << endl;
        hitEnter(response);

        cout << endl << "\"You two stop over at a table in the hallway, where you snap some pictures of their notes.\"" << endl;
        hitEnter(response);

        if (introduce < 1) // if user didn't get introduction
        {
            cout << endl << "\"Oh, I'm Piper, by the way. it's nice to meet you.\"" << endl;
            hitEnter(response);

            cout << endl << "✦ \"Likewise! My name is " << characters[4].getUsername() << "!\"" << endl;
            hitEnter(response);
            introduce++;
        }

        cout << endl << "\"...You know, " << characters[4].getUsername() << ", I've come to the conclusion that this class has destroyed my will to live.\"" << endl;
        hitEnter(response);

        cout << endl << "You sputter at the sudden comment, and then burst into a small laugh." << endl << endl << "✦ \"Dude, truer words have never been spoken. Everyday is pain!\"" << endl;
        hitEnter(response);

        cout << endl << "Piper chuckles." << endl << endl << "\"I know! Let me tell you, I've never had a professor more merciless than ours. My homework is stained with tears!!\"" << endl;
        hitEnter(response); 

        cout << endl << "The two of you end up walking together out of the building, chatting about classes, majors, and dorms." << endl;
        hitEnter(response); 

        cout << endl << "Turns out, you two share a few other classes this semester!" << endl << "You're tempted to get their contact info, so you could study together." << endl;
        hitEnter(response);

        cout << endl << "❥ Will you ask them?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;
    
        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if(YesNo == "YES") // if user input "YES"
        {
            cout << "⇡❤" << endl << endl;
            characters[2].addAffection(3);
            cell++;

            cout << endl << "The two of you exchange numbers, and you part ways." << endl;
            hitEnter(response);

            random = randomFunction(); // random event
            if (random <= 5)
            {
                cout << endl << "You're walking to your next class when you get an alert from your phone." << endl << "You check it and see a text from Piper -- a meme. ⇡❤" << endl;
                hitEnter(response);
                characters[2].addAffection(2);

                cout << endl << "Yep, this friendship is already off to a great start. Hopefully the rest of today looks good as well." << endl;
                hitEnter(response);
            }
    
            cout << "「END OF WEEK 1」" << endl;
            hitEnter(response);
        }
        else // if "NO"
        {
            cout << endl << "Hmm, maybe not. You'll probably see each other again later, maybe you could just casually study together instead." << endl;
            hitEnter(response);

            cout << endl << "The two of you part ways. Hopefully, the rest of today will make up for this morning's rough start." << endl << endl;
            hitEnter(response);

            cout << "「END OF WEEK 1」" << endl;
            hitEnter(response);
        }
    }
    else // if "NO"
    {
        cout << endl << "Eh, forget it. Not worth the effort. You'll probably be fine." << endl << "You go on your merry way to your next class. Hopefully, the rest of today will make up for this morning's rough start." << endl << endl;
        hitEnter(response);

        cout << "「END OF WEEK 1」" << endl;
        hitEnter(response);
    }

// ---------------------------------------------------------------------------------------------------------

cout << "「WEEK 2」" << endl;

    cout << endl << "Finally! The weekend could not arrive any faster! After a busy school week, you deserve a fun little outing, don't you think?" << endl;
    hitEnter(response);

    cout << endl << "Your friend, Katherine, is begging you to come along to the arcade." << endl << "Sounds like a get-together with a bunch of people! Let's join in!" << endl;
    hitEnter(response);

    cout << endl << "You enter the arcade about half an hour later, texting Katherine to find out where she was." << endl;
    hitEnter(response);
    
    cout << endl << "Since you're focused on your phone, you're not paying attention to what's in front of -- oof!" << endl;
    hitEnter(response);

    cout << endl << "Oh geez. Looks like you totally ran into someone." << endl << "You look up to apologize to them, when your eyes meet familiar ones." << endl;
    hitEnter(response);

    if(introduce < 1)
    {
        cout << endl << "Isn't that that person from your class? You can see their eyes flickering with some sort of recognition, of you, as well." << endl;
        hitEnter(response);

        cout << endl << "✦ \"Hey, I'm so sorry about that, I wasn't paying attention!\"" << endl << "You say." << endl;
        hitEnter(response);

        cout << endl << "They smile kindly at you." << endl << endl << "\"You're all good, no worries. By the way, do I know yo--\"" << endl;
        hitEnter(response);
    }
    else
    {
        cout << endl << "\"Whoa, " << characters[4].getUsername() << "! Of all the people I could've literally bumped into!\"" << endl << "Piper laughs." << endl;
        hitEnter(response);

        cout << endl << "✦ \"Piper! It's good seeing you!\"" << endl << "You exclaim." << endl << "✦ \"What are --\"" << endl;
        hitEnter(response); 
    }
    
    cout << endl << "You're interrupted by Katherine jumping on you from behind, tightly embracing you." << endl;
    hitEnter(response);

    cout << endl << "\"Hey! Hey, hi! I'm so glad you're here, " << characters[4].getUsername() << "! I wanna show you -- Oh!\"" << endl;
    hitEnter(response);

    cout << endl << "Katherine jumps off of you to give Piper a hug as well." << endl << endl << "\"Hey Piper!! It's good to see you again!\"" << endl;
    hitEnter(response);

    cout << endl << "Katherine grabs your hand and Piper's hand, and pulls you both across the arcade." << endl << "She leads you to a larger group of people -- friends, acquaintances, strangers, even." << endl;
    hitEnter(response);

    cout << endl << "You and Piper share a look of amusement." << endl;
    hitEnter(response);

    cout << endl << "With everyone together, the group discusses buying tokens and splitting up the price." << endl << "\"How much for 15 tokens?\"" << endl << "Piper asks." << endl;
    hitEnter(response);

    cout << endl << "\"12 dollars! If you hand it to me, I can go get them for us.\"" << endl << "Katherine responds." << endl;

    cout << endl << "\"12? Sweet! That's my lucky number! Here.\"" << endl << "Piper grins." << endl << "You hand Katherine the same amount." << endl;
    
    cout << endl << "With tokens purchased, the group begins to split off to enjoy the arcade games." << endl << "Katherine pressed a bunch of tokens into your palm before running excitedly off to play skee ball." << endl;
    hitEnter(response);

    cout << endl << "You're thinking about what game you'd like to play, when your stomach grumbles." << endl << "Geez, you didn't eat anything yet before you came here, silly!" << endl << "You stop over to the small food court to grab a bite before heading back to the arcade floor." << endl;
    hitEnter(response);

    cout << endl << "Alrighty! With that taken care of, what game would you like to go play?" << endl;
    hitEnter(response);

    locationChoice = openLocation(2, locations, 1, SIZE); // call upon locationChoice function

    if(locationChoice == 1) // if locationChoice returned 1
    {
        cout << "⇡❤" << endl << endl;
        characters[2].addAffection(5);

        cout << endl << "You head towards the classic fighter games, searching for Street Fighter." << endl << "You round the corner to see two people already playing the game, fingers furiously pressing the buttons." << endl;
        hitEnter(response);

        cout << endl << "Curious, you approach closer, wanting to get a look at the health bars and see who's leading." << endl << "Suddenly, one of the bar empties and a yell of frustration erupts." << endl;
        hitEnter(response);

        cout << endl << "You realize it's Piper laughing victoriously while their companion is throwing their hands up in exasperation." << endl << "\"Come on! One more time! Maybe this time you'll win!\"" << endl << "You hear Piper teasing." << endl;
        hitEnter(response);

        cout << endl << "\"Nah, I'm done dude! I'm playing something else this is BS!\"" << endl << "Piper's friend huffs. They get up to leave and see you standing nearby." << endl << "\"Oh, sorry!\"" << endl;
        hitEnter(response);

        cout << endl << "✦ \"Oh you're good, no worries!\"" << endl << "You smile." << endl << endl << "At the sound of your voice, Piper whips around." << endl;
        hitEnter(response);

        cout << endl << "\"Oh! " <<  characters[4].getUsername() << "! Perfect timing, come fight me!\"" << endl << "Piper urges, patting the seat beside them." << endl;
        hitEnter(response);

        cout << endl << "✦ \"Oh, heck yeah! Don't be disappointed when you lose too hard!\"" << endl << "You laugh." << endl;
        hitEnter(response);

        cout << endl << "You and Piper square off across 10 matches, switching characters every so often and yelling loudly." << endl << "But there can only be one victor! And in the end...." << endl;
        hitEnter(response);


        random = randomFunction(); // random event
        if (random > 5)
        {
            cout << endl << "You came out on top! At 6 wins and 4 losses, you've secured victory!" << endl << "Piper refuses to admit defeat, but you win bragging rights. Suckerrrr!" << endl;
            hitEnter(response);

            cout << endl << "✦ \"I DIDN'T COME HERE TO LOSE, PIPER! YOU SHOULD'VE HEEDED MY WARNING!\"" << endl << "You exclaim." << endl << endl << "\"THIS IS UNBELIEVABLE, I WANT A REMATCH IMMEDIATELY!\"" << endl;
        }
        else
        {
            cout << endl << "You got destroyed! At 6 losses and 4 wins, you've got to save whatever dignity you have left!" << endl << "Piper's won bragging rights, and you just need to take it!" << endl;
            hitEnter(response);

            cout << endl << "\"Oh, what? What was that about me losing too hard? Didn't you say that before you lost horrendously to me?\"" << endl << "Piper grins devilishly." << endl << endl << "✦ \"God, you make it so hard not to punch you!\"" << endl; 
            hitEnter(response);
        }
    }
    else // if locationChoice didn't return 1
    {
        cout << endl << "You hurry off to go find the machine to play your game! To your dismay, there are already people crowding around it. Unlucky!" << endl;
        hitEnter(response);

        cout << endl << "You try to peek around the mass of people, confused about the crowd. It's not usually this occupied." << endl;
        hitEnter(response);

        cout << endl << "You hear a triumphant yell, and lots of excited cheering." << endl << "You manage to peer in between the heads of two people, and see some kid standing in a mass of tickets." << endl << "An endless stream of tickets is flying out of the machine, the ticket counter quickly racking up." << endl;
        hitEnter(response);

        cout << endl << "...Welp, there goes your chances. That kid's going to be there for a while. Shucks!" << endl;
        hitEnter(response);

        cout << endl << "You decide to go bother Katherine at skee ball, that's sure to be a good time." << endl;
        hitEnter(response);
    }

    cout << "After a while more of playing, you're content with the tickets you've gathered so far." << endl;
    hitEnter(response);

    if(locationChoice == 1) // if locationChoice returned 1
    {
        cout << "You and Piper had parted ways a bit ago, when one of their buddies dragged them away for another game." << endl;
        hitEnter(response);
    }
    else
    {
        cout << "You and Katherine had parted ways a bit ago, when one of her buddies dragged her away for another game." << endl;
        hitEnter(response);
    }

    cout << "What do you feel like doing now?" << endl;
    hitEnter(response);

    locationChoice = openLocation(2, locations, 2, SIZE); // call upon locationChoice function

    if (locationChoice == 1) // if locationChoice returned 1
    {
        cout << "You check your phone to see where Katherine is. She tells you to meet her at the food court with some others." << endl;
        hitEnter(response);

        cout << "You make your way there, keeping an eye out for her or any others in your group you might recognize." << endl;
        hitEnter(response);

        cout << "You're squinting off into the distance, when suddenly you hear...." << endl << endl << "\"" << characters[4].getUsername() << "! Over here! Hey!\"" << endl;
        hitEnter(response);

        cout << "You look to your right to see Katherine and Piper waving you over, smiling." << endl << "You make your way over, greeting your friends." << endl;
        hitEnter(response);

        cout << "\"Hey! Hey! " << characters[4].getUsername() << ", I'm kinda hungry and I didn't bring enough money. Can you cover for me? I did it for you last time!\"" << endl << "She pouts at you." << endl;
        hitEnter(response);

        cout << "Yikes. You're now remembering how you bought something to eat earlier. Plus, you wanted to save what you had left. But, you owe her." << endl;
        hitEnter(response);

        cout << "❥ Do you want to tell her the truth?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;

        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if (YesNo == "YES") // if user input "YES"
        {
            cout << "⇡❤" << endl << endl;
            characters[2].addAffection(3);

            cout << endl << "You hesitate a bit, and then sigh before you meet Katherine's eyes." << endl;
            hitEnter(response);

            cout << endl << "✦ \"I'm sorry, I spent money earlier to eat and what I have left I need to save. I know! I know! I forgot I owe you, I'm sorry.\"" << endl << endl << "You offer to cover her next time." << endl;
            hitEnter(response);

            cout << endl << "Katherine punches you lightly." << endl << endl << "\"Duuuuuuude! It's alright though, thanks for being honest. But!! Next time!! Don't forget!\"" << endl << "She pinches your nose, laughing as you yelp." << endl;
            hitEnter(response);

            cout << endl << "You glance over to see Piper, smiling a bit at your shenanigans." << endl << "Their eyes linger on yours for a bit, before prying Katherine off of you. ⇡❤" << endl;
            hitEnter(response);
            characters[2].addAffection(2);

            cout << endl << "\"Come on, Katherine. Pick something out, I'll buy it for you.\"" << endl << "They glance over at you." << endl << endl << "\"Do you want anything too? I'll cover, but you'll have to owe me next time too!\"" << endl;
            hitEnter(response);

            cout << endl << "You scoff at Piper." << endl << "The three of you get some food, and enjoy the rest of the time with the group." << endl;
            hitEnter(response);

            cout << endl << "It's now starting to get late, and you decide that it's a good time to head out. You say your goodbyes, and make your way home." << endl;
            hitEnter(response);
            
            cout << "「END OF WEEK 2」" << endl;
            hitEnter(response);
        }
        else // if "NO"
        {
            cout << "⇣❤" << endl << endl;
            characters[2].subAffection(3);

            cout << endl << "✦ \"Er, sorry Katherine, I can't, I don't have enough.\"" << endl << "You lied. She pouted, but shrugged it off." << endl;
            hitEnter(response);

            cout << endl << "Piper frowns." << endl << endl << "\"But didn't I see you buy something to eat here earlier?\"" << endl;
            hitEnter(response);

            cout << endl << "Crap. The game is up. You didn't realize Piper saw you." << endl << endl << "Obviously caught in your lie, you stutter a bit, not knowing what to say." << endl;
            hitEnter(response);

            cout << endl << "Katherine punches you lightly." << endl << endl << "\"Dude, come on! You didn't have to lie. You could've just told me you didn't want to pay this time around.\"" << endl;
            hitEnter(response);

            cout << endl << "She sighs, again, before pinching your nose." << endl << "You avert your eyes in shame, and apologize hastily." << endl;
            hitEnter(response);

            cout << endl << "\"Just tell me next time, okay? It's alright. Come on! Let's go grab some water.\"" << endl;
            hitEnter(response);

            cout << endl << "She's pulling you along, but you glance up when you pass Piper." << endl << "Their frown has lessened, but they look away when you meet their eyes." << endl;
            hitEnter(response);

            cout << endl << "You're left wondering if you screwed up worse than you anticipated." << endl;
            hitEnter(response);

            cout << endl << "You hang out with the group for a bit longer at the court before you take your leave." << endl << "It's been a long day, and you're really needing some rest." << endl;
            hitEnter(response);

            cout << "「END OF WEEK 2」" << endl;
            hitEnter(response);
        }
    }
    else if(locationChoice == 2) // if locationChoice returned 2
    {
        cout << "You head off to redeem your tickets at the ticket shop!" << endl;

        random = randomFunction(); // random event
        if (random > 5)
        {
            cout << endl << "Right when you enter, you see Piper rushing out, bumping into you and clumsily apologizing quickly before disappearing." << endl;
            hitEnter(response);

            cout << endl << "How strange. You wonder where they might be going, rushing off like that. You hope they're alright." << endl << "You look back into the shop and see a sizeable tangle of tickets on the ground, as well as a wallet." << endl;
            hitEnter(response);

            cout << endl << "Your eyes widened and you head over to the mess, picking up the wallet and checking the I.D." << endl;
            hitEnter(response);

            cout << endl << "Oh geez, it's Piper's! You whip around to see if they've returned, but they're nowhere in sight and you're not sure where they've went." << endl;
            hitEnter(response);

            cout << endl << "You sigh, and hold onto to wallet to keep it safe for them. You look at the tangled mess of tickets before you, and pause." << endl << "Well, you're not sure if Piper will be back, and they seemed rather concerned." << endl;
            hitEnter(response);

            cout << endl << "You decide to gather up their tickets and fold them neatly together." << endl << "Piper probably doesn't need any more chaos right now than they might already be dealing with, you figure." << endl;
            hitEnter(response);

            cout << endl << "You decide to take your time to wait for Piper." << endl << "You were looking at the rows of cute stuffed animals on a shelf, when you see movement out of the corner of your eye." << endl;
            hitEnter(response);

            cout << endl << "You turn to see Piper entering the shop again, sighing and running their hands through their hair." << endl;
            hitEnter(response);

            cout << endl << "You walked over to them, while they were standing in the shop looking around for the pile of tickets they had left." << endl;
            hitEnter(response);

            cout << endl << "✦ \"Piper! Hey, you left your wallet. Also, here.\"" << endl << "You say, handing over the wallet and pressing the neatly folded tickets into their hand." << endl;
            hitEnter(response);

            cout << endl << "They blush a bit when they realize what you've done for them." << endl << endl << "\"Oh, " << characters[4].getUsername() << ", that's really thoughtful of you. You really didn't have to do that for me.\" ⇡❤" << endl;
            hitEnter(response);
            characters[2].addAffection(2);

            cout << endl << "You smile at their thanks. They explain to you that Katherine had gotten sick, hence why they left quickly." << endl;
            hitEnter(response);

            cout << endl << "You're surprised at the information, and you thank Piper for letting you know." << endl << "You open up your phone to message Katherine, and decided to take your leave to check on her to make sure she's okay." << endl;
            hitEnter(response);

            cout << endl << "Piper walks out with you to your car and waves you goodbye." << endl << "You don't notice them nervously brushing back their hair and red-tipped ears as you drive away." << endl;
            hitEnter(response);

            cout << "「END OF WEEK 2」" << endl;
            hitEnter(response);
        }
        else // didn't get random event dialogue
        {
            cout << endl << "You're investigating the rows of cute stuffed animals, plastic toy swords, and boxes of sweets." << endl;
            hitEnter(response);

            cout << endl << "You've just finished selecting some items and redeeming your tickets, when you recieve a message from Katherine." << endl;
            hitEnter(response);

            cout << endl << "She told you that she was heading out early because she was feeling rather sick." << endl << "You figure that you're not really wanting to stay at the arcade anymore then if she's gone." << endl;
            hitEnter(response);

            cout << endl << "Plus, you've already got your prizes. You're content with your goods, and you decide to head on out." << endl;
            hitEnter(response);

            cout << "「END OF WEEK 2」" << endl;
            hitEnter(response);
        }
    }
    else if(locationChoice == 3) // if locationChoice returned 0
    {
        cout << endl << "Duty calls, you know? You send Katherine a message to meet you and hold onto your tickets while you take care of business." << endl << "She's taking her sweet time. You're about to say screw it and hide the tickets somewhere, when she finally runs up to you." << endl;
        hitEnter(response);

        cout << endl << "She's about to open her mouth to apologize when you shove the tickets at her and run inside before you burst." << endl << "Thank god, a few seconds later and it would've been over." << endl;
        hitEnter(response);

        cout << endl << "After you finished washing up, you exit the bathroom to look for Katherine, but she's nowhere to be seen." << endl << "You check your phone to see a message from her." << endl;
        hitEnter(response);

        cout << endl << "She told you that she saved your tickets into her arcade card, and that she needed you to meet her outside." << endl << "Turns out she had gotten sick from eating too many churros." << endl;
        hitEnter(response);

        cout << endl << "She's outside, pale and miserable, with Piper stroking her back to ease her queasiness. God, this girl." << endl;
        hitEnter(response);

        cout << endl << "Piper waves you over, and the two of you walk Katherine over to your car." << endl << "You thank Piper for their help, and they smile softly while watching you take care of her." << endl;
        hitEnter(response);

        random = randomFunction(); // random event
        if (random > 5)
        {
            cout << endl << "\"Mind if I join you?\"" << endl << "Piper asks." << " \"I can make sure she doesn't throw up in your car.\"" << endl;
            hitEnter(response);

            cout << endl << "Your heart swells at the kind offer." << endl << endl << "✦ \"God, please, that would be awesome.\"" << endl << endl << "Piper smiles warmly at you." << endl << "\"No promises to prevent any spillage, though!\"" << endl;
            hitEnter(response);

            cout << endl << "Katherine's passed out, leaning against Piper's shoulder, as you drive home." << endl << endl << "You and Piper have comfortable, pleasant conversation." << endl << "You can't help checking the rearview mirror to look at them as they speak, and they smile softly everytime they catch your eye. ⇡❤" << endl;
            hitEnter(response);
            characters[2].addAffection(2);
        }
        else
        {
            cout << endl << "You wave goodbye to Piper before heading off, the last thing you see being Piper disappearing back into the arcade." << endl;
        }
        
        cout << endl << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }
    else // if locationChoice returned 0
    {
        cout << endl << "Well! You've had a grand ol' time, you could probably catch Katherine on your way out to give her your tickets." << endl << "You already quite exhausted, and it's a good time to head home and rest." << endl;
        hitEnter(response);
        
        cout << endl << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }

     // ---------------------------------------------------------------------------------------------

    if(cell < 1) // if user doesn't have Piper's number
    {
        cout << "「END OF PIPER PLAYTHROUGH」" << endl;
        hitEnter(response);
        return;
    }
    else
    {
        cout << "「WEEK 3」" << endl;
        
        cout << endl << "Surprise! You got all your work done yesterday, and now you have the weekend free!" << endl << "Today's a great day to do something fun. Let's see who's free to hang out!" << endl;
        hitEnter(response);
        
        cout << endl << "You open your phone to see a message from Piper." << endl << "You were talking about some childhood games, and they had sent you a link to some playthrough." << endl;
        hitEnter(response);
        
        cout << endl << "Hey! Maybe you should ask Piper if they're free to hang out. You could play some games!" << endl;
        hitEnter(response);

        cout << endl << "❥ Should you invite Piper over?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;

        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if(YesNo == "YES") // if user input "YES"
        {
            cout << "⇡❤" << endl << endl;
            characters[2].addAffection(2);
            
            cout << "You invite Piper over to your place to hang out. You wait patiently for their response." << endl << "You hear an alert, and check your phone." << endl;
            hitEnter(response);
            
            cout << "\"Piper: Y E S please!! I'll be there in a moment!\"" << endl;
            hitEnter(response);
            
            cout << endl << "You're setting up some games when you hear a knock at your door." << endl;
            hitEnter(response);
            
            cout << endl << "You open your door to see Piper, grinning." << endl << "\"Yo! Thanks for having me over!\"" << endl;
            hitEnter(response);
            
            cout << endl << "✦ \"Piper! Get in here! I'm almost done setting up.\"" << endl << "You usher them inside." << endl; 
            hitEnter(response);

            cout << endl << "They glance around your space, and see the haphazard games and wires you have strewn about." << endl << endl << "\"Hey, let me help you out.\"" << endl;
            hitEnter(response);

            cout << endl << "They rearrange the game pieces, cards, and other miscellaneous items spilled on the ground." << endl << "They give you a hand in plugging in the necessary wires." << endl;
            hitEnter(response);
            
            cout << endl << "✦ \"Oh, shoot! Piper, I forgot I was going to make some popcorn and get out some snacks." << endl << "You groaned. You completely forgot about that!" << endl;
            hitEnter(response);

            cout << endl << "Their ears perk up." << endl << endl << "\"Hey! Don't worry about it, you finish setting up, I'll take care of it, okay?\"" << endl;
            hitEnter(response);

            cout << endl << "✦ \"...I don't know, I don't wanna make you do so much work! It's my place, after all.\"" << endl << endl << "\"It's alright. I really like helping out my friends, so let me do this for you.\"" << endl;
            hitEnter(response);

            cout << endl << "They smile reassuringly at you, and you give a thankful smile in return." << endl << "They head off to the kitchen." << endl;
            hitEnter(response);

            cout << endl << "A bit later, you call Piper over." << endl << endl << "✦ \"Oh! Yes! Hey, Piper! I got it working! Come here!\"" << endl;
            hitEnter(response); 

            cout << endl << "Piper joins you, a big bowl of popcorn in one hand and several sweet and savory snacks in the other." << endl << "Your eyes widened." << endl;
            hitEnter(response);

            cout << endl << "✦ \"Oh! My god! Thank you for getting everything set up! You really saved me there!\"" << endl << "You grin." << endl;
            hitEnter(response);

            cout << endl << "\"Oh, of course! It's my pleasure.\"" << endl << "They smile brightly at your thanks." << endl << endl << "\"Now, let's get started!\"" << endl;
            hitEnter(response);

            cout << endl << "\"The two of you spend the evening playing Uno, Family Game Night, Mario Kart, and many others." << endl << "There was a lot of popcorn throwing, controller slamming, and exasperated yells." << endl;
            hitEnter(response);

            cout << endl << "At one point, you rush to block their view of the screen in Mario Kart with your hands." << endl;
            hitEnter(response);
            
            cout << endl << "\"DUDE!! WHAT ARE YOU DOING, I'M GONNA FALL OFF!\"" << endl << "Piper yells, laughing wildly as you snort." << endl;
            hitEnter(response);
            
            cout << endl << "All of a sudden, they grab both your wrists and yank you towards them." << endl << "Your eyes widened as you stared into theirs, gleaming brightly with mischief." << endl;
            hitEnter(response);
            
            cout << endl << "Then, they smash your face into the sofa, tossing your controller somewhere you couldn't manage to find." << endl << endl << "They win first place in the match, all the while you sat dead last, still looking for your controller." << endl;
            hitEnter(response);
            
            cout << endl << "They're snickering at your misery before they drop to their knees to help you find it." << endl;
            hitEnter(response);
            
            cout << endl << "You groan." << endl << endl << "✦ \"God, Piper! Where did you throw it??\"" << endl << endl << "\"I don't know! I just threw it somewhere over my shoulder! I wasn't looking!\"" << endl;
            hitEnter(response);
  
            cout << endl << "✦ \"We've been searching for a while now! How long as it even been!\"" << endl << endl << "\"...Uh...I'm checking my phone...22 minutes?\"" << endl;
            hitEnter(response);
  
            cout << endl << "✦ \"...Well, at least that's my lucky number. That's a sign! We'll find it soon!\"" << endl << endl << "\"Your lucky number huh? Psh.\"" << endl;
            hitEnter(response);
  
            cout << endl << "✦ \"Whatever! Better than yours, anyways!\"" << endl << endl << "\"What! You don't even know it, you can't roast me for that!\"" << endl;
            hitEnter(response);
            
            cout << endl << "✦ \"Yeah I do! You said it a while ago! It's: \"" << endl;
            hitEnter(response);

            cout << endl << "❥ (What is Piper's lucky number? Enter an integer below)" << endl;
            
            getline(cin, answer);
            int numAnswer = stoi(answer); // convert answer to integer
            
            if (numAnswer == 12) // if user entered input correctly
            {
                cout << "⇡❤" << endl << endl;
                characters[2].addAffection(5);
                
                cout << endl << "Piper raises their eyebrows in surprise." << endl << "\"Damn! Alright, I had no idea you knew that! Your point.\"" << endl; 
                
                cout << endl << "They're chuckling, and the sight makes me smile as well." << endl;
                hitEnter(response);
            }
            else // if user didn't enter input correctly
            {
                cout << endl << "Piper laughs, triumphant." << endl << "\"Ha! Told ya, buddy! You don't know what it is. It's 12!\"" << endl;
                hitEnter(response);

                cout << endl << "✦ \"Well, whatever!\"" << endl << "You scoff. Rats! You thought you had it!" << endl;
                hitEnter(response);
            }

            cout << endl << "Two hours later, the two of you finished your snacks and cleaned up the mess." << endl;
            hitEnter(response);
            
            cout << endl << "It's late in the evening now, and Piper's about ready to leave." << endl << "\"I had a lot of fun today! Let's do this again soon, alright? I'd love to see you again.\"" << endl;
            hitEnter(response);
            
            if (numAnswer == 12) // if user entered input correctly
            {
                cout << endl << "Piper reaches over to give you a side hug, before they turn quickly to leave." << endl << "They walk away with a huge grin on their face, their cheeks tinted pink." << endl;
                hitEnter(response);

                cout << "「END OF WEEK 3」" << endl;
                cout << "「END OF PIPER PLAYTHROUGH」" << endl;
                hitEnter(response);
                return;
            }
            
            cout << endl << "Piper waves you goodbye, and they head out." << endl;
            hitEnter(response);
            
            cout << "「END OF WEEK 3」" << endl;
            cout << "「END OF PIPER PLAYTHROUGH」" << endl;
            hitEnter(response);
            return;
        }
        else // if "NO"
        {
            cout << "Hm, guess not. They could be busy. You don't want to bother them if that's the case." << endl;
            hitEnter(response);

            cout << endl << "You went ahead and spent the day catching up on some work, playing some games, and messaging Katherine." << endl;
            hitEnter(response);

            cout << endl << "It was nice to stay inside, every once in a while. You make a mental note to invite Piper over next time around." << endl;
            hitEnter(response);

            cout << "「END OF WEEK 3」" << endl;
            cout << "「END OF PIPER PLAYTHROUGH」" << endl;
            hitEnter(response);
        }
    }

return;
}

void Simulator::ElisePlaythrough(Character characters[], Location locations[], const int SIZE, int locationChoice, string response, string YesNo, string answer, int random) // Dialogue for Elise
{
    int cell = 0, gallery = 0; // initialize necessary variables

    cout << endl << "「WEEK 1」" << endl;

    cout << endl << "Today is Monday. It's time to head to your first class of the day, and you're determined to start your week off strong! " << endl << endl << "Well, at least, that was the plan. You had slept in, and now you've got to book it to class." << endl;
    hitEnter(response);

    cout << endl << "You rush to calculus, and -- argh! Someone's nabbed your usual seat! No surprise there." << endl << "And the professor's already flying through content. Great." << endl;
    hitEnter(response);

    cout << endl << "You sit down quickly at a nearby seat." << endl << "As you set down your belongings, you glance around the aisle and meet the eyes of the person sitting next to you." << endl << endl << "She shoots you a quick smile before looking away." << endl;
    hitEnter(response);

    cout << endl << "You turn your focus on the professor as they begin to write on the board." << endl << "The professor throw out a problem for your class to work through, and encourages you to turn and talk to a neighbor." << endl;
    hitEnter(response);

    cout << endl << "You start working out the problem, so far so good, until -- shoot. You're stumped. You don't remember how to do this part." << endl;
    hitEnter(response);

    cout << endl << "You peek to your right, wondering if the person next to you could help you out." << endl;
    hitEnter(response);

    cout << endl << "To your surprise, you see that girl already glancing your way." << endl << "She meets your gaze, and smiles brightly at you." << endl;
    hitEnter(response);

    cout  << "\"Hey! I'm totally stuck on this, could I ask you what you did?\"" << endl;
    hitEnter(response);

    cout << endl << "You laugh a bit." << endl << endl << "✦ \"What a coincidence, I was actually going to ask you the same thing!\"" << endl;
    hitEnter(response);

    cout << endl << "She chuckles softly at that." << endl << endl << "\"Here, let's compare what we have!\"" << endl;
    hitEnter(response);

    cout << endl << "\"Oh! My name's Elise by the way, I like your shirt!\"" << endl;
    hitEnter(response);

    cout << endl << "You're surprised at how friendly she is, and her smile makes you smile as well." << endl;
    hitEnter(response);

    cout << endl << "✦ \"Thank you, that's very kind of you! I'm " << characters[4].getUsername() << ". I don't think I've met anyone as friendly as you are!\"" << endl;
    hitEnter(response);

    cout << endl << "You laugh lightly, and Elise turns pink at your compliment." << endl;
    hitEnter(response);
    cout << "⇡❤" << endl << endl;
    characters[3].addAffection(1);

    cout << endl << "The two of you puzzle over your work, and you point out a simplification error. She notices your sign error." << endl;
    hitEnter(response);

    cout << endl << "Both of you chuckle over your ridiculously small mistakes." << endl;
    hitEnter(response);

    cout << endl << "Somehow, even though you've just met her, you feel quite comfortable around her already." << endl << "You're thinking of getting her contact info to study together, and get some notes from earlier that you've missed." << endl;
    hitEnter(response);

    cout << endl << "❥ Do you want to ask her?" << endl; // ask for user input
    cout  << "Yes" << setw(10) << "No" << endl;

    getline(cin, YesNo);
    YesNo = uppercase(YesNo);
    while(search(YesNo, '%') != 0) // check for user error
    {
        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
    }

    if(YesNo == "YES") // if user input "YES"
    {
        cout << "⇡❤" << endl << endl;
        characters[3].addAffection(3);
        cell++;

        cout << endl << "✦ \"Uh, hey, I hope I'm not bothering you too much when I ask you this, but is it alright if I get some notes from you? I was late and missed a lot of stuff.\"" << endl << endl << "Elise nods enthusiastically, reaching for her phone." << endl;
        hitEnter(response);
        
        cout << endl << "\"Yes, totally! We should also study together sometime, if you'd like! We make a good team!\"" << endl;
        hitEnter(response);

        cout << endl << "✦ \"Yeah, I would love that! Thank you so much for helping me out, I really appreciate it!\"" << endl;
        hitEnter(response);

        cout << endl << "You two exchange numbers, and you chat a bit about your majors." << endl;
        hitEnter(response);

        cout << endl << "The professor begins speaking again before you get too far, and you both turn to focus." << endl;
        hitEnter(response);

        cout << endl << "Class later ends without much more excitement." << endl << "You get up to leave and see Elise also doing the same." << endl;
        hitEnter(response);

        cout << endl << "You wonder if you should continue your conversation from earlier." << endl;
        hitEnter(response);

        cout << endl << "❥ Walk out with Elise?" << endl; // ask for user input
        cout  << "Yes" << setw(10) << "No" << endl;

        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if(YesNo == "YES") // if user inputs "YES"
        {
            cout << "⇡❤" << endl << endl;
            characters[3].addAffection(1);

            cout << endl << "You catch Elise on her way out, and you guys talk and walk together." << endl;
            hitEnter(response);

            cout << endl << "The conversations between you two flow very casually, very comfortably." << endl;
            hitEnter(response);

            cout << endl << "She talks quite fast, almost stumbling over them while trying to get them out. It's rather endearing, and you can't help but smile." << endl;
            hitEnter(response);

            cout << endl << "\"Hey! Hey hey, are you free sometime next week?\"" << endl << "Elise asks, suddenly." << endl;
            hitEnter(response);
 
            cout << endl << "✦ \"Hmm, next weekend? Um, I think so! Why? What's up?\"" << endl << "You reply." << endl;
            hitEnter(response);
 
            cout << endl << "\"Please come check out this pop-up art gallery! I don't know if you like this kind of stuff, but I'd love to see you there!\"" << endl << "She exclaims." << endl;
            hitEnter(response);
 
            cout << endl << "That sounded rather interesting, actually. Plus, when she's excited like this, you find it hard to say no." << endl << endl << "✦ \"Sure, Elise! That sounds wonderful!\"" << endl;
            hitEnter(response);
            gallery++;
 
            cout << endl << "Her smile brightens at that." << endl << "\"Really? Thank you so much!! I'll send you the address soon, alright? Keep an eye out!\"" << endl;
            hitEnter(response);
 
            cout << endl << "And with that, Elise excuses herself to head to her class. You do the same." << endl << "You smile, looking forward to her message." << endl;
            hitEnter(response);

            random = randomFunction(); // random event
            if (random <= 5)
            {
                cout << endl << "Elise sends you the address of the gallery later that night." << endl << "You two end up talking a bit about art and animation, and she sends you lots of wonderful works." << endl;
                hitEnter(response);

                cout << endl << "She's really passionate about art, and you enjoy hearing her talking about it." << endl << "You two have a wonderful conversation. ⇡❤" << endl;
                hitEnter(response);
                characters[3].addAffection(2);
            }

            cout << "「END OF WEEK 1」" << endl;
            hitEnter(response);
        }
        else // if "NO"
        {
            cout << endl << "..Actually, on second thought, she might have to head quickly to class. You don't want to bother her too much." << endl;
            hitEnter(response);

            cout << endl << "You're left wondering if you'll see her again." << endl << "You head towards your next class. Hopefully, the rest of today goes smoothly." << endl;
            hitEnter(response);

            cout << "「END OF WEEK 1」" << endl;
            hitEnter(response);
        }
    }
    else // if "NO"
    {
        cout << endl << "Hm, no, it's alright. It might be too soon for that. You might see her around again later, anyways." << endl;
        hitEnter(response);

        cout << endl << "The professor begins speaking again. You focus on taking notes." << endl << "Class later ends without much more excitement." << endl;
        hitEnter(response);

        cout << endl << "You get up to leave and see Elise already beelining it out the door." << endl << endl << "You're left wondering if you'll see her again." << endl;
        hitEnter(response);

        cout << endl << "You head towards your next class. Hopefully, the rest of today goes smoothly." << endl << endl;
        hitEnter(response);

        cout << "「END OF WEEK 1」" << endl;
        hitEnter(response);
    }


// ---------------------------------------------------------------------------------------------------------

cout << "「WEEK 2」" << endl;

    cout << endl << "Finally! The weekend could not arrive any faster! After a busy school week, you deserve a fun little outing, don't you think?" << endl;
    hitEnter(response);

    if(gallery > 0 && cell > 0) // if user has had the gallery dialogue and has Elise's number
    {
        cout << endl << "You're thinking about what to do today, when you suddenly remember!" << endl << "Today was the day Elise asked you to check out that gallery!" << endl;
        hitEnter(response);

        cout << endl << "You take out your phone to double-check the address, and then you head out." << endl;
        hitEnter(response);
        
        cout << endl << "It doesn't take you long to find the gallery. It was set-up at the corner of a relatively busy street." << endl;
        hitEnter(response);
    }
    else if (gallery < 1 && cell > 0) // if user hasn't had the gallery dialogue but has Elise's number
    {   
        cout << endl << "You check your phone to see a message from Elise. She's invited you to a pop-up art gallery, along with its address." << endl;
        hitEnter(response);

        cout << endl << "You consider it for a bit, before you think, why not? You gather your things and head out." << endl;
        hitEnter(response);

        cout << endl << "It doesn't take you long to find the gallery. It was set-up at the corner of a relatively busy street." << endl;
        hitEnter(response);
    }
    else if (cell < 1) // if user doesn't have Elise's number
    {
        cout << endl << "You're thinking of heading out and exploring some of the shops nearby. You might go buy some food for a movie marathon!" << endl;
        hitEnter(response);

        cout << endl << "You gather your things and head out." << endl << "You're walking down the street when you notice a lot of bustling down at the corner." << endl;
        hitEnter(response);

        cout << endl << "What could that be?" << endl;
        hitEnter(response);
    }

    cout << endl << "You approached the corner, noticing the white drapes overhead that shaded the art pieces from the sun." << endl << "There are already quite a bit of people in the area." << endl;
    hitEnter(response);

    cout << endl << "The crowd's murmuring and lively chatter draws your curiosity." << endl << "Before you, are several easels." << endl;
    hitEnter(response);

    cout << endl << "What artwork would you like to visit first?" << endl;
    hitEnter(response);

    locationChoice = openLocation(3, locations, 1, SIZE); // call upon openLocation function

    if(locationChoice == 1) // if locationChoice returns 1
    {
        cout << "⇡❤" << endl << endl;
        characters[3].addAffection(5);

        cout << endl << "You stand under the drape, observing \"Tadow\" in particular. It's an interesting work, to say the least." << endl << "You see various body parts, well, you're not entirely sure if they're body parts." << endl << "You see harsh lines -- jagged and broken, with smears of black ink." << endl;
        hitEnter(response);

        cout << endl << "You take a quick glance at the other art pieces, and they seem to have similar elements across them." << endl;
        hitEnter(response);
    }
    else // if locationChoice doesn't return 1
    {
        cout << endl << "You stand before the piece, taking in the dark, brooding streaks across the canvas." << "There are dramatic shadows strewn about the piece, and a variety of browns and greens litter the edges of the work." << endl;
        hitEnter(response);
    }

    cout << endl << "The piece has left you feeling rather...unsettled. Like something out of a fever dream, or a nightmare." << endl << "You've never seen anything like it before, really." << endl;
    hitEnter(response);

    cout << endl << "You're still in thought, observing the piece, when suddenly you feel a tap on your shoulder." << endl << "You turn around to see Elise smiling at you, head cocked to the side." << endl;
    hitEnter(response);

    cout << endl << "\"Hey hey! What's up! I'm super stoked to see you here!\"" << endl << "She beams." << endl;
    hitEnter(response);

    cout << endl << "You smile warmly at her." << endl << endl << "✦ \"Hey, Elise! It's good seeing you too.\"" << endl;
    hitEnter(response);

    if (locationChoice == 1) // if locationChoice returns 1
    {
        cout << endl << "Elise nods at the painting in front of you." << endl << endl << "\"That one, \"Tadow\", is my favorite.\"" << endl << "You watch her eyes twinkle as they scan the piece." << endl;
        hitEnter(response);
    }

    cout << endl << "You're about to open your mouth to ask her what she thinks about the gallery, but she suddenly turns." << endl;
    hitEnter(response);

    cout << endl << "You hear a voice somewhere nearby calling out her name." << endl << endl << "\"Oh! Someone's calling me, I gotta leave for sec. I'll catch up with you soon!\"" << endl;
    hitEnter(response);

    cout << endl << "And Elise is gone just as soon as she appeared. Huh. You hope to see her soon." << endl;
    hitEnter(response);
    
    cout << "❥ Well, What do you feel like doing now?" << endl; // ask for user input
    hitEnter(response);

    locationChoice = openLocation(3, locations, 2, SIZE); // call upon openLocation function

    if (locationChoice == 1) // if locationChoice returns 1
    {
        cout << endl << "You decide to explore more of what the gallery has to offer." << endl << "Across the entire street corner, there are numerous paitings, posters, flags, and Work-In-Progress pictures." << endl;
        hitEnter(response);

        cout << endl << "You stand in wonder and amazement at the intricacy of the small gallery, it seemed incredibly well-planned." << endl;
        hitEnter(response);

        cout << endl << "It's another moment before you feel a familiar tap on the shoulder, and you turn to see Elise." << endl << "She's flashing another one of her brilliant smiles." << endl;
        hitEnter(response);

        cout << endl << "\"" << characters[4].getUsername() << ", sorry for leaving so abruptly! I had to take care of something." << endl << "\"Anyways! I wanted to ask for your opinion of the gallery so far!\"" << endl;
        hitEnter(response);

        cout << endl << "You gaze at her bright eyes, and pause to think for a bit before you gave an answer." << endl << "You want to be honest about your thoughts." << endl;
        hitEnter(response);

        cout << endl << "❥ Will you refrain from being harsh about it?" << endl; // asking for user input
        cout  << "Yes" << setw(10) << "No" << endl;

        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // check for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if (YesNo == "YES") // if user inputs "YES'"
        {
            cout << "⇡❤" << endl << endl;
            characters[3].addAffection(3);

            cout << endl << "✦ \"I think it's...interesting. I've never really seen art like this before. To be totally honest, it unnerves me, but I keep coming back to it.\"" << endl;
            hitEnter(response);

            cout << endl << "\"...Dude, that's perfect!\"" << endl << "There's a wide grin on Elise' face." << endl << "You're a bit confused." << endl;

            cout << endl << "\"I guess I should've told you that this was my gallery, huh?\"" << endl << "Elise laughs." << endl;
            hitEnter(response);       

            cout << endl << "\"I'm trying to be better with handling critcism, but I appreciate that you took time to be careful about your words. It means a lot.\"" << endl << "\"But, yeah! This is my gallery, my art! And your reaction is exactly what I'm wanting!\"" << endl;
            hitEnter(response); 

            cout << endl << "✦ \"Really? That's quite unusual, I guess, to me. Why is this what you wanted?\"" << endl;
            hitEnter(response); 

            cout << endl << "Elise turns excitedly to you." << endl << "\"I'm so glad you asked!\"" << endl;
            hitEnter(response); 

            cout << endl << "She gestures to one of her paintings." << endl << endl << "\"My art style is surrealism! It's..weird. It's a mash-up of reality and dreams, of the conscious and the unconscious.\"" << endl;
            hitEnter(response); 

            cout << endl << "\"This kind of stuff is so fascinating to me! It stirs something within you, doesn't it? And I love it!!\"" << endl;
            hitEnter(response); 

            cout << endl << "You smile at her excitement. You chuckle softly, and Elise turns to look at you, laughing as well." << endl << "\"What! Why are you laughing!\"" << endl;
            hitEnter(response); 

            cout << endl << "✦ \"I don't know. I just love seeing you so passionate. It's obvious how hard you've worked on this, and it makes me happy that you're happy. ⇡❤" << endl;
            characters[3].addAffection(2);

            cout << endl << "Elise suddenly pauses, and you glance over at her." << endl << endl << "You see a bright red flush dancing across her cheeks, and her eyes are looking everywhere else but you." << endl;
            hitEnter(response); 

            cout << endl << "The sight is endearing, and you can't help but laugh at it, which only deepened her blush." << endl << endl << "\"Quit it!! You're embarassing meeee!\"" << endl << "Elise whines." << endl;
            hitEnter(response); 

            cout << endl << "You're about to tease her further when you get interrupted by Elise snapping her attention to the left." << endl;
            hitEnter(response); 
        
        }
        else // if "NO"
        {
            cout << "⇣❤" << endl << endl;
            characters[3].subAffection(3);

            cout << endl << "✦ \"I think it's a mess. I don't get it, and it creeps me out. There's no uniformity.\"" << endl;
            hitEnter(response);

            cout << endl << "There's a slight pause, as Elise doesn't immediately say anything." << endl;
            hitEnter(response);

            cout << endl << "\"...I guess I should've told you that this was my gallery, huh?\"" << endl << "Elise laughs a bit, nervously." << endl;
            hitEnter(response);

            cout << endl << "Oh, no. You feel pretty bad now." << endl << "✦ \"Oh, wait, Elise, I'm sorry. I didn't know it was yours. I didn't mean to -- \"" << endl;
            hitEnter(response);

            cout << endl << "Elise quickly interrupts you." << endl << endl << "\"Oh, no! Please, it's okay! It's best for you to be honest, you know? And critcism helps me grow!\"" << endl;
            hitEnter(response);

            cout << endl << "She puts on a small smile, hoping to put you ease." << endl << "You can't shake the feeling that you must've hurt her feelings by being too harsh about it." << endl;
            hitEnter(response);

            cout << endl << "✦ \"Well...alright, if you say so. But, really, Elise, I'm sorry.\"" << endl << endl << "Elise offers you another comforting smile, before snapping her attention to the left." << endl;
            hitEnter(response);
        }
        
        cout << endl << "Someone was looking around frantically, calling out Elise's name." << endl;
        hitEnter(response);

        cout << endl << "\"Oh geez, hey, I gotta go. That's one of my mentors. Hey, thanks again for coming, okay? I'll catch up later!\"" << endl;
        hitEnter(response);

        cout << endl << "And again, she's gone all too quick." << endl << "You sigh a bit, as you watch her back disappear. You figure it's time to head out." << endl;
        hitEnter(response);

        cout << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }
    else if(locationChoice == 2) // if locationChoice returns 2
    {
        cout << endl << "You decide to sit down at a bench to watch the people crowd in and around the gallery." << endl;
        hitEnter(response);

        cout << endl << "You overhear a mixture of everything from wonder and amazement from critcism and harsh judgement." << endl << "To each their own, you muse." << endl;
        hitEnter(response);

        cout << endl << "The crowd starts to grow before long, and you can no longer distinguish much of what was going on. You decided it was a good time to head out." << endl;
        hitEnter(response);

        random = randomFunction(); // random event
        if (random > 5)
        {
            cout << endl << "You were getting up to leave, when you see a flurry of birds flying around a part of the drapes that had fallen." << endl << "Some were perching on an easel, and you suddenly felt a bit of distress." << endl;
            hitEnter(response);

            cout << endl << "You rush over and frantically try to wave off the birds, and fix the drapes that had slipped off a hook." << endl;
            hitEnter(response);

            cout << endl << "You didn't realize that Elise, momentarily free, happened to look over and see you." << endl << "She giggled at you, waving your arms like a wacky waving inflatable tube man. ⇡❤" << endl;
            hitEnter(response);
            characters[3].addAffection(2);
        }

        cout << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }
    else if(locationChoice == 3) // if locationChoice returns 3
    {
        cout << endl << "You peer around the easels to the center of the gallery, where there is a lone wooden table." << endl;
        hitEnter(response);

        cout << endl << "You approach the table, and see a small bunch of papers on a clipboard." << endl;
        hitEnter(response);

        cout << endl << "\"ATTENDEE LIST\" it said, at the top. You scan the pages, and see names upon names, filling them." << endl;
        hitEnter(response);

        cout << endl << "At the bottom of each page, you see a signature: \"Elise\". Your eyes widened. This is Elise' gallery?" << endl;
        hitEnter(response);

        cout << endl << "You look around, trying to find her, but you don't see her. You scratch your head, and then flip to a page with an empty row." << endl;
        hitEnter(response);

        cout << endl << "You're quite amazed that she was able to set this up. You sign your name, and attempt once more to find her, before you decide to head home." << endl;
        hitEnter(response);
        
        cout << endl << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }
    else // if locationChoice returns 0
    {
        cout << endl << "Well, you're not too interested in staying for much longer." << endl << "The crowd is steadily getting larger too, and you're not wanting to stay in the mass of noise." << endl;
        hitEnter(response);

        cout << endl << "You figure you should head home before it gets too chaotic." << endl;
        hitEnter(response);

        if(cell < 1) // if user doesn't have Elise' number
        {
            cout << endl << "You're already home when you realize you forgot to get some snacks. Ugh! Oh well, next time, huh?" << endl;
        }
        
        cout << endl << "「END OF WEEK 2」" << endl;
        hitEnter(response);
    }

// ---------------------------------------------------------------------------------------------

    if(cell < 1) // if user doesn't have Elise' number
    {
        cout << "「END OF ELISE PLAYTHROUGH」" << endl;
        hitEnter(response);
        return;
    }
    else
    {
        cout << "「WEEK 3」" << endl;
        
        cout << endl << "Surprise! You got all your work done yesterday, and now you have the weekend free!" << endl << "Today's a great day to do something fun. Let's see who's free to hang out!" << endl;
        hitEnter(response);
        
        cout << endl << "You open your phone to see a message from Elise." << endl << "You were talking about Bob Ross, and she had sent you a terrible Ross Halloween costume." << endl;
        hitEnter(response);
        
        cout << endl << "Hey! Maybe you should ask Elise if they're free to hang out. You could paint and watch videos together!" << endl;
        hitEnter(response);

        cout << endl << "❥ Should you invite Elise over?" << endl; // asking for user input
        cout  << "Yes" << setw(10) << "No" << endl;

        getline(cin, YesNo);
        YesNo = uppercase(YesNo);
        while(search(YesNo, '%') != 0) // checking for user error
        {
            getline(cin, YesNo);
            YesNo = uppercase(YesNo);
        }

        if(YesNo == "YES") // if user inputs "yes"
        {
            cout << "⇡❤" << endl << endl;
            characters[3].addAffection(2);
            
            cout << "You invite Elise over to your place to hang out. You wait patiently for their response." << endl << "You hear an alert, and check your phone." << endl;
            hitEnter(response);
            
            cout << "\"Elise: Ohmygosh! Yes I'd love that! I'll be there in a moment!\"" << endl;
            hitEnter(response);
            
            cout << endl << "You're setting up some paint and laying out a tarp when you hear a knock at your door." << endl;
            hitEnter(response);
            
            cout << endl << "You open your door to see Elise, bubbly and smiling." << endl << "\"Oh!! Thanks for inviting me! I'm so excited!!\"" << endl;
            hitEnter(response);

            cout << endl << "\"I hope you don't mind, I got a little too excited, maybe, and brought over some of my paints and canvases!\"" << endl;
            hitEnter(response);

            cout << endl << "Ugh, god she is so fun to be around. You usher them inside." << endl; 
            hitEnter(response);

            cout << endl << "The two of you get set up on the tarp, and get started on painting." << endl << "You're chatting about the Bob Ross painting tutorials while painting on some canvases." << endl;
            hitEnter(response);
 
            cout << endl << "You're looking and laughing at the mess of your canvas." << endl << endl << "✦ \"These are supposed to be mountains? I've got something abstract going on!\"" << endl;
            hitEnter(response);
 
            cout << endl << "Elise laughs at that." << endl << "\"You gotta trust the process!\"" << endl;
            hitEnter(response);
 
            cout << endl << "✦ \"Hmm. You think Bob's got a video on your art style? We could try that!\"" << endl;
            hitEnter(response);
 
            cout << endl << "Elise raises an eyebrow at that." << endl << endl << "\"My art style? Do you remember what it was?\"" << endl;
            hitEnter(response);
 
            cout << endl << "✦ \"Of course I do, Elise! It's: \"" << endl;
 
            cout << endl << "❥ (What is Elise's art style? Enter below)" << endl; // asking for user input
            getline(cin, answer);
            answer = uppercase(answer);
            
            if (answer == "SURREALISM") // user input correct answer
            {
                cout << "⇡❤" << endl << endl;
                characters[3].addAffection(5);
                
                cout << endl << "Elise jumps at that." << endl << "\"Yes! Exactly! I'm so happy you remembered!\"" << endl << "She giggles, softly." << endl;
                hitEnter(response);

                cout << endl << "The sight makes your heart swell." << endl;
                hitEnter(response);
            }
            else // if user did not input correct answer
            {
                cout << endl << "Elise giggles, and then wipes paint onto the tip of your nose." << endl << "You jerk backwards in surprise." << endl;
                hitEnter(response);

                cout << endl << "\"Wrong!! It's surrealism, silly! Gotcha there!\"" << endl;
                hitEnter(response);

                cout << endl << "✦ \"Well, whatever!\"" << endl << "You scoff. Rats! You thought you had it!" << endl;
                hitEnter(response);
            }

            cout << endl << "After a few hours of letting your paintings dry, you two share your art and watch a few more videos together." << endl;
            hitEnter(response);
            
            cout << endl << "You clean up your mess. It's late in the evening now, and Elise is about ready to leave." << endl << "\"Today was super fun, I'm lucky I have someone like you in my life!\"" << endl;
            hitEnter(response);
            
            if (answer == "SURREALISM") // user input correct answer
            {
                cout << endl << "Elise tugs you into a tight embrace, smiling at you before letting go and turning quickly to leave." << endl << "They're giddy as they rush away, trying to hide their intense redness." << endl;
                hitEnter(response);

                cout << "「END OF WEEK 3」" << endl;
                cout << "「END OF ELISE PLAYTHROUGH」" << endl;
                hitEnter(response);
                return;
            }
            
            cout << endl << "Elise gives you one last, bright smile, before heading out." << endl;
            hitEnter(response);
            
            cout << "「END OF WEEK 3」" << endl;
            cout << "「END OF ELISE PLAYTHROUGH」" << endl;
            hitEnter(response);
            return;
        }
        else // if "NO"
        {
            cout << "Hm, guess not. She could be busy. You'd feel bad to bother her." << endl;
            hitEnter(response);

            cout << endl << "You went ahead and spent the day catching up on some work, playing some games, and researching different art movements." << endl;
            hitEnter(response);

            cout << endl << "You're thinking of talking about what you've learned with Elise. You would love to see her get excited about it." << endl;
            hitEnter(response);

            cout << "「END OF WEEK 3」" << endl;
            cout << "「END OF ELISE PLAYTHROUGH」" << endl;
            hitEnter(response);
        }
    }

return;
}

void showEnding(Character characters[], int numLetter, int random) // Function that prints an ending for the user
{
    // prints out an ending for the player, based on the affection level of the character they select
    if (characters[numLetter].getAffectionLevel() >= 20) // best ending with this affection level
    {
        cout << endl << "「BEST ENDING」:" << endl << endl << characters[numLetter].getUsername() << " returned your feelings! The two of you go on to make lots of happy memories together." << endl
        << "You bring out the best in each other, and support one another throughout your hardships. You look forward to a long and happy future together!" << endl << endl;
        cout << "\"Who ever loved that loved not at first sight?\"" << endl << endl << "Thanks for playing! ❤" << endl << endl;
    }
    else if(characters[numLetter].getAffectionLevel() >= 10 && characters[numLetter].getAffectionLevel() < 20) // this range of affection gets three different endings
    {
        random = randomFunction(); // randomly generate a number to pick from one of these endings
        if(random >= 7 && random <=10) // normal ending 1
        {
            cout << endl << "「NORMAL ENDING」:" << endl << endl << characters[numLetter].getUsername() << " accepted your feelings! Overtime, they found themselves falling in love with you." << endl
            << "You two have your difficulties, but somehow always manage to bounce back. There's nothing more you could ask!" << endl << endl;
            cout << "\"There are all kinds of love in the world, but never the same love twice.\"" << endl << endl << "Thanks for playing! ❤" << endl << endl;
        }
        else if(random >= 3 && random < 7) // normal ending 2
        {
            cout << endl << "「NORMAL ENDING」:" << endl << endl << characters[numLetter].getUsername() << " accepted your feelings! Overtime, they found themselves falling in love with you." << endl
            << "However, your relationship doesn't last. Somewhere down the road, the spark disappeared." << endl
            << "Neither of you tried hard enough to stay together -- maybe, neither of you were willing to." << endl << endl;
            cout << "\"They slipped briskly into an intimacy from which they never recovered.\"" << endl << endl << "Thanks for playing! ❤" << endl << endl;
        }
        else if(random >= 0 && random < 3) // normal ending 3
        {
            cout << endl << "「NORMAL ENDING」:" << endl << endl << characters[numLetter].getUsername() << " accepted your feelings! They find you charming, and they're glad to be with you." << endl
            << "However, your relationship doesn't last. You two seemed better off as friends -- nothing more, unfortunately. At least they're still in your life." << endl << endl;
            cout << "\"I don't ask you to love me always like this, but I ask you to remember.\"" << endl << endl << "Thanks for playing! ❤" << endl << endl;
        }
    }
    else // worst ending with this affection level
    {
        cout << endl << "「WORST ENDING」:" << endl << endl << characters[numLetter].getUsername() << " rejected you, and couldn't reciprocate your feelings." << endl
            << "Hey, You're alright, buddy. Let's give it another go." << endl << endl;
        cout << "\"This is a good sign, having a broken heart. It means we have tried for something.\"" << endl << endl << "Thanks for playing! ❤" << endl << endl;
    }

return;
}

void Simulator::start()
{
    Character characters[5]; // creating an array of Character objects, and then setting their data members
    Character Char1;
    Char1 = Character("Leon",
                    "Friendly and charismatic. Sometimes impulsive because he likes to buy gifts for others. Lots of light-hearted teasing and he doesn't take many things seriously. Often forgetful and bad with confrontation.",
                    "Baking Delicious Sweets.", "Spiders.", 0);

    Character Char2;
    Char2 = Character("August",
                    "Clever and perceptive. Typically blunt and standoffish with others and they have a hard time opening up. Actually quite nurturing and incredibly patient but they rarely show it. A very soft spot for animals.",
                    "Cats -- Even The Hairless Ones.", "Spicy Food.", 0);

    Character Char3;
    Char3 = Character("Piper",
                    "Brilliant and genuine. Shows their appreciation by helping others and sharing in their burdens. They can't help but to wear their heart on their sleeve and they somehow always know the right words to say.",
                    "Playing Videogames.", "Dishonesty.", 0);

    Character Char4;
    Char4 = Character("Elise",
                    "Expressive and creative. Rather strong-willed and doesn't always know her limits. She's scared of letting down the people she loves but strives to prove those who underestimate her wrong.",
                    "Painting and Graphic Design.", "Loud Chewing.", 0);
    
    Character Char5; // creating the 5th Character object

    Line lines[5];
    Line Line1;
    Line Line2;
    Line Line3;
    Line Line4;
    Line Line5; // creating Line objects

    lines[0] = Line1;
    lines[1] = Line2;
    lines[2] = Line3;
    lines[3] = Line4;
    lines[4] = Line5; // setting each Line object to an element of the lines array of objects

    Location locations[4]; // creating locations array of objects
    string choice1Array[4];
    string choice2Array[4];
    const int SIZE = 4; // initializing necessary arrays and variable, SIZE

// -----------------------------------------------------------------------------------

    cout << endl << "Before we get started, introduce yourself! :)" << endl;
    cout << endl << "What is your name?" << endl
    << "──────────────────" << endl;
    string use_name;
    getline(cin, use_name);

    while(search(use_name, '@') != 0) // check for user error in input
    {
        cout << "That's not a valid name! Only letters, please." << endl;
        cout << endl << "What is your name?" << endl
        << "──────────────────" << endl;
        getline(cin, use_name);
    }

    cout << endl << "How would you describe yourself in a single sentence? (Please conclude with a period.)" << endl
    << "──────────────────────────────────────────────────────────────────────────────────────" << endl;
    string use_desc;
    getline(cin, use_desc);

    while(search(use_desc, '#') != 0) // check for user error in input
    {
        cout << endl << "How would you describe yourself in a single sentence? (Please conclude with a period.)" << endl
        << "──────────────────────────────────────────────────────────────────────────────────────" << endl;
        getline(cin, use_desc);
    }

    cout << endl << "What is something you like? (Please conclude with a period.)" << endl
    << "────────────────────────────────────────────────────────────" << endl;
    string use_like;
    getline(cin, use_like);

    while(search(use_like, '#') != 0) // check for user error in input
    {
        cout << endl << "What is something you like? (Please conclude with a period.)" << endl
        << "────────────────────────────────────────────────────────────" << endl;
        getline(cin, use_like);
    }

    cout << endl << "What is something you dislike? (Please conclude with a period.)" << endl
    << "───────────────────────────────────────────────────────────────" << endl;
    string use_dislike;
    getline(cin, use_dislike);

    while(search(use_dislike, '#') != 0) // check for user error in input
    {
        cout << endl << "What is something you dislike? (Please conclude with a period.)" << endl
        << "───────────────────────────────────────────────────────────────" << endl;

        getline(cin, use_dislike);
    }

    Char5 = Character(use_name, use_desc, use_like, use_like, 0); // setting the info for the 5th Character object

    characters[0] = Char1;
    characters[1] = Char2;
    characters[2] = Char3;
    characters[3] = Char4;
    characters[4] = Char5; // setting each Character object to an element of the characters array of objects

    cout << endl << "Thanks for the info! Let's play ❤" << endl << endl;

// ------------------------------------------------------------------------------------------------

    string str, strLetter, YesNo, response, answer;
    int num = 0, numLetter = 0, locationChoice = 0, random = 0; // initialiizng necessary variables

    while(num != 7) // while input is not equal to number 7, enter loop
    {
        showAffection(characters); // call upon showAffection function
       
        cout << endl << "Now, please enter a number from one of the options below:" << endl
        << "─────────────────────────────────────────────────────────" << endl << endl
        << "1.  «:──────:﹡  Leon  ﹡:──────:»" << endl << endl
        << "2.  ⊱✥┈┈┈┈┈┈(⊱  August  ⊰)┈┈┈┈┈┈✥⊰" << endl << endl
        << "3.  ≿⊱—————»❈  Piper  ❈«—————⊰≾" << endl << endl
        << "4.  *｡︵‿︵ʚ˚ɞ  Elise  ʚ˚ɞ︵‿︵｡*" << endl << endl
        << "5.  ✦━━«⋆⋆»━━  VIEW PROFILE  ━━«⋆⋆»━━✦" << endl << endl 
        << "6.  ➳✉  SEND A LOVE LETTER  ➳✉" << endl << endl
        << "7. 『  EXIT GAME  』" << endl << endl;

        getline(cin, str);
        num = stoi(str);
            
        switch (num) // switch statement to go through the options
        {
            case 1: // Choosing the Leon Playthrough
                printMenu(characters, 0); //gives info on the character at index 0 of the array of character objects
                getline(cin, YesNo);
                YesNo = uppercase(YesNo);

                while(search(YesNo, '%') != 0) // checks for user error
                {
                    cout << endl << "❥ Interact with Leon?" << endl;
                    cout  << "Yes" << setw(10) << "No" << endl;
                    getline(cin, YesNo);
                    YesNo = uppercase(YesNo);
                }

                if(YesNo == "YES") // confirming to interact with Leon
                {
                    characters[0].setAffection(0);
                    LeonPlaythrough(characters, locations, SIZE, locationChoice, response, YesNo, answer, random); // call upon LeonPlaythrough function
                    break;
                }
            // choosing not to interact with Leon, then looping back to the menu
            break;
            
            case 2: // Choosing the August Playthrough
                printMenu(characters, 1); //gives info on the character at index 1 of the array of character objects
                getline(cin, YesNo);
                YesNo = uppercase(YesNo);

                while(search(YesNo, '%') != 0) // checks for user error
                {
                    cout << endl << "❥ Interact with August?" << endl;
                    cout  << "Yes" << setw(10) << "No" << endl;
                    getline(cin, YesNo);
                    YesNo = uppercase(YesNo);
                }

                if(YesNo == "YES") // confirming to interact with August
                {
                    characters[1].setAffection(0);
                    AugustPlaythrough(characters, locations, SIZE, locationChoice, response, YesNo, answer, random); // call upon AugustPlaythrough function
                    break;
                }                
            // choosing not to interact with August, then looping back to the menu
            break;
                
            case 3: // Choosing the Piper Playthrough
                printMenu(characters, 2); //gives info on the character at index 2 of the array of character objects
                getline(cin, YesNo);
                YesNo = uppercase(YesNo);

                while(search(YesNo, '%') != 0) // checks for user error
                {
                    cout << endl << "❥ Interact with Piper?" << endl;
                    cout  << "Yes" << setw(10) << "No" << endl;
                    getline(cin, YesNo);
                    YesNo = uppercase(YesNo);
                }

                if(YesNo == "YES") // confirming to interact with Piper
                {
                    characters[2].setAffection(0);
                    PiperPlaythrough(characters, locations, SIZE, locationChoice, response, YesNo, answer, random); // call upon PiperPlaythrough function
                    break;
                }
            // choosing not to interact with Piper, then looping back to the menu
            break;

            case 4: // Choosing the Elise Playthrough
                printMenu(characters, 3); //gives info on the character at index 3 of the array of character objects
                getline(cin, YesNo);
                YesNo = uppercase(YesNo);

                while(search(YesNo, '%') != 0) // checks for user error
                {
                    cout << endl << "❥ Interact with Elise?" << endl;
                    cout  << "Yes" << setw(10) << "No" << endl;
                    getline(cin, YesNo);
                    YesNo = uppercase(YesNo);
                }

                if(YesNo == "YES") // confirming to interact with Elise
                {
                    characters[3].setAffection(0);
                    ElisePlaythrough(characters, locations, SIZE, locationChoice, response, YesNo, answer, random); // call upon ElisePlaythrough function
                    break;
                }
            // choosing not to interact with Elise, then looping back to the menu
            break;

            case 5: // Choosing to view profile
                printMenu(characters, 4); //gives info on the character at index 4 of the array of character objects
                getline(cin, YesNo);
                YesNo = uppercase(YesNo);

                while(YesNo != "YES") // checks for user error
                {
                    cout << endl << "Invalid Input! Try again." << endl;
                    cout << endl << "❥ Go back?" << endl;
                    cout  << "Yes?" << endl;
                    getline(cin, YesNo);
                    YesNo = uppercase(YesNo);
                }
            // choosing to exit viewing the profile
            break;

            case 6: // Choose to send a letter

                cout << endl << "Write and send a sweet message to the person of your choice ~!" << endl << endl << 
                "Maybe they'll return your love! ❤" << endl << endl <<
                "「HINT」: the higher the affection level, the better your chances!" << endl; // the better the ending the user will obtain

                cout << endl << "❥ Send a letter to someone?" << endl;
                cout  << "Yes" << setw(10) << "No" << endl;
                getline(cin, YesNo);
                YesNo = uppercase(YesNo);

                while(search(YesNo, '%') != 0) // checks for user error
                {
                    cout << endl << "❥ Send a letter to someone?" << endl;
                    cout  << "Yes" << setw(10) << "No" << endl;
                    getline(cin, YesNo);
                    YesNo = uppercase(YesNo);
                }
    
                if(YesNo == "YES") // user chooses to send a letter
                {
                    cout << endl << "For whom would you like to write a letter? Enter a number:" << endl // select someone to write a letter to
                    << "──────────────────────────────────────────────────────────" << endl << endl
                        << "1.  ﹡  Leon  ﹡" << endl << endl
                        << "2.  ⊱  August  ⊰" << endl << endl
                        << "3.  ❈  Piper  ❈" << endl << endl
                        << "4.  ɞ  Elise  ʚ" << endl << endl;
                    
                    getline(cin, strLetter);
                    numLetter = stoi(strLetter);

                    while(numLetter <= 0 || numLetter > 4) // checks for user error in input
                    {
                        cout << endl << "Invalid Input! Try again." << endl;
                        cout << endl << "For whom would you like to write a letter? Enter a number:" << endl
                        << "──────────────────────────────────────────────────────────" << endl << endl
                        << "1.  ﹡  Leon  ﹡" << endl << endl
                        << "2.  ⊱  August  ⊰" << endl << endl
                        << "3.  ❈  Piper  ❈" << endl << endl
                        << "4.  ɞ  Elise  ʚ" << endl << endl;
                        getline(cin, strLetter);
                        numLetter = stoi(strLetter);
                    }

                    numLetter -= 1; // whatever is inputted as numLetter, is one value greater than the indices of the array of character objects

                    do
                    {
                        writeMessage("message.txt", characters, lines, numLetter); // call upon writeMessage function

                        cout << endl << "Here is your letter:" << endl;
                        cout << "━━━━━━ ◦ ❖ ◦ ━━━━━━" << endl;

                        readMessage("message.txt"); // call upon readMessage function when the message is written
        
                        getline(cin, YesNo);
                        YesNo = uppercase(YesNo);

                        while(search(YesNo, '%') != 0) // loop to check for user error
                        {
                            cout << endl << "❥ Would you like to keep your message?" << endl;
                            cout  << "Yes" << setw(10) << "No" << endl;
                            getline(cin, YesNo);
                            YesNo = uppercase(YesNo);
                        }
                    }
                    while(YesNo == "NO"); // if user wants to rewrite message, then stay in do-while loop

                    showEnding(characters, numLetter, random); // endgame is reached when the user writes a letter
                    exit(0); // this ends the program, ends the game so that this character selection menu won't loop again
                }
            // choosing not to write a letter, then looping back to the menu
            break;

            case 7: // Choose to exit the game
                
                cout << endl << "Thanks for playing! ❤" << endl;

            break;

            default: // if invalid input (like not a number, blank space, or empty string)

                cout << endl << "Oops! Invalid input! Choose again, please. And choose wisely." << endl;

            break;
        }
    }

return;
}