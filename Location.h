#ifndef LOCATION_H
#define LOCATION_H
#include <string>
using namespace std;

class Location
{
    public:
        Location();
        Location(string _Arr1[], string _Arr2[]);

        void setLocationName(string _loc);
        void setChoice1At(int _ind, string _choice);
		void setChoice2At(int _ind, string _choice);

		string getLocationName() const;
        string getChoice1At(int index) const;
        string getChoice2At(int index) const;

    private:
        string locationName;
        string choice1Array[4];
        string choice2Array[4];
        static const int SIZE = 4;

};
#endif