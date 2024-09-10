#include "character.h"
#include <iostream>
#include <iomanip>
using namespace std;

//no default constructor
Character::Character(string na, int hp, int xp, int pts){
	name = na;
	HP = maxHP = hp;
	XP = xp;
	ptsLeft = pts;
	hasActed = false;
}
void Character::setName(string na){
	name = na;
}
string Character::getName(){
	return name;
}
int Character::getHP(){
	return HP;
}
int Character::getXP(){
	return XP;
}
void Character::printHelper(){
	cout << setw(16) << "HP:" << HP << " / " << maxHP << endl
		<< setw(16) << "XP:" << XP << endl
		<< "Points to "<< endl
		<< setw(16) << "next level:" << ptsLeft-XP << endl;
}
void Character::heal(){
	//full recovery
	HP = maxHP;
}



void Character::setActed(bool ac){
	hasActed = ac;
}
//have they acted yet this turn?
bool Character::getActed(){
	return hasActed;
}

bool Character::isDead(){
	if(HP<=0)
		return true;
	return false;
}

void Character::printHPandMax(){
	cout << "HP: " << HP << " / " << maxHP;
}

//Wizard has a special action to heal or attack
int Character::action(vector<Character*>&){
	hasActed = true;
	return getAttack();
}
//Only novice has a luck stat
int Character::getLuck(){
	return 0;
}
//Only knights can equip weapons
bool Character::canEquip(){
	return false;
	//nothing for unrelated classes
}


