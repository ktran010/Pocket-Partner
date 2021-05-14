// CS1300 Fall 2020
// Author: Katherine Tran
// Recitation: 323 -- Christopher Gavin
// Project 3 -- Line class implementation file


#include "Line.h"
#include <string>
using namespace std;


Line::Line()
{
    OptionA = "";
	OptionB = "";
	OptionC = "";
	OptionD = ""; // initalizes all data members of each object to empty
}

Line:: Line(string _opA, string _opB, string _opC, string _opD)
{
    OptionA = _opA;
	OptionB = _opB;
	OptionC = _opC;
	OptionD = _opD; // each respective data member is equal to the respective parameter passed in
}

void Line::setOptionA(string _opA) // whatever is passed in as a parameter is equal to option A
{
    OptionA = _opA;
}

void Line::setOptionB(string _opB) // whatever is passed in as a parameter is equal to option B
{
    OptionB = _opB;
}

void Line::setOptionC(string _opC) // whatever is passed in as a parameter is equal to option C
{
    OptionC = _opC;
}

void Line::setOptionD(string _opD) // whatever is passed in as a parameter is equal to option D
{
    OptionD = _opD;
}

string Line::getOptionA() const // retrieve option A
{
    return OptionA;
}

string Line::getOptionB() const // retrieve option B
{
    return OptionB;
}
string Line::getOptionC() const // retrieve option C
{
    return OptionC;
}
string Line::getOptionD() const// retrieve option D
{
    return OptionD;
}