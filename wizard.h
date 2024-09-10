#pragma once
#include "character.h"
#include <vector>

using namespace std;

class Wizard : public Character{
protected:
	int mAtk;
public:
	Wizard(string);
	void print();
	int getAttack();
	void reduceHP(int);
	int increaseXP(int);

	int action(vector<Character*>&);
};
