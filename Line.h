#ifndef LINE_H
#define LINE_H
#include <string>
using namespace std;

class Line
{
    public:
        Line();
        Line(string _opA, string _opB, string _opC, string _opD);

        void setOptionA(string _opA);
		void setOptionB(string _opB);
		void setOptionC(string _opC);
		void setOptionD(string _opD);
		
		string getOptionA() const;
		string getOptionB() const;
		string getOptionC() const;
		string getOptionD() const;
    
    private:
        string OptionA;
		string OptionB;
		string OptionC;
		string OptionD;

};
#endif