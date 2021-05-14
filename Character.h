#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
using namespace std;

class Character
{
    public:
        Character();
        Character(string _name, string _desc, string _li, string _disli, int _aff);

        void setUsername(string _name);
		void setDescription(string _desc);
		void setLikes(string _li);
		void setDislikes(string _disli);
		void setAffection(int _aff);
		void addAffection(int _addaff);
		void subAffection(int _subaff);
		
		string getUsername() const;
		string getDescription() const;
		string getLikes() const;
		string getDislikes() const;
		int getAffectionLevel() const;

    private:
        string username;
        string description;
        string likes;
        string dislikes;
        int affectionLevel;

};
#endif