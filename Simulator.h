#ifndef SIMULATOR_H
#define SIMULATOR_H
#include "Character.h"
#include "Location.h"
#include "Line.h"
#include <string>
using namespace std;

class Simulator
{
    public:
        Simulator();

        void LeonPlaythrough(Character characters[], Location locations[], const int SIZE, int locationChoice, string response, string YesNo, string answer, int random);
        void AugustPlaythrough(Character characters[], Location locations[], const int SIZE, int locationChoice, string response, string YesNo, string answer, int random);
        void PiperPlaythrough(Character characters[], Location locations[], const int SIZE, int locationChoice, string response, string YesNo, string answer, int random);
        void ElisePlaythrough(Character characters[], Location locations[], const int SIZE, int locationChoice, string response, string YesNo, string answer, int random);
        
        void setLines(Character characters[], Line lines[], int numLetter);
        void writeMessage(string filename, Character characters[], Line lines[], int num);
        
        void start();

    private:
        Character characters[5];
        Location locations[4];
        Line lines[5];

};
#endif