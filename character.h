#pragma once
#include <string>
#include <vector>
using namespace std;

class Character{
protected:
	string name;
	int HP;
	int XP;
	int ptsLeft; //the total XP needed for the next level
	int maxHP;
	//character has already acted in this turn
	bool hasActed;
public:
	Character(string, int, int, int);
	void setName(string);
	string getName();
	int getHP();
	int getXP();

	//pure virtual functs
	virtual void print() = 0;
	virtual int getAttack() = 0;
	virtual void reduceHP(int) = 0;
	virtual int increaseXP(int) = 0; //altered to return levels gained
									//and recover 1/10 missing HP when level up
	void heal();

	//added
	void setActed(bool);
	bool getActed();
	void printHelper(); //to print the shared Character stats
	bool isDead(); //call this after taking damage in app
	void printHPandMax(); //print "HP / MaxHP"

	//these are primarily for just one class, but need them here since
	//we're using base class pointers
	virtual int action(vector<Character*>&); //for wizard to heal/fight (return attk)
	virtual int getLuck(); //for novice when traveling (0 for others)
	virtual void equipWep(string, int){}; //for knight (does nothing for others)
	virtual bool canEquip(); //only knights can equip weapons

	//I had some issues, but this fixed them
	virtual ~Character(){}; //virtual destructor


};
