 #pragma once
#include "character.h"
#include <string>
using namespace std;

class Knight : public Character{
protected:
	string wepName;
	int wepAtk;
	int armor;
public:
	Knight(string);
	void print();
	int getAttack();
	void reduceHP(int);
	int increaseXP(int);

	void equipWep(string, int);
	bool canEquip();

};
