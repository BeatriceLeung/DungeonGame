#pragma once
#include "character.h"

class Novice : public Character{
protected:
	int luck;
public:
	Novice(string);
	void print();
	int getAttack();
	void reduceHP(int);
	int increaseXP(int);

	int getLuck();

};
