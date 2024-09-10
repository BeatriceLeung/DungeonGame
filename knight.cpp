#include "knight.h"
#include <iostream>
#include <iomanip>
using namespace std;

Knight::Knight(string na)
 : Character(na, 120, 0, 8){ //character param constructor
	//default stats -- can only give name
	armor = 1;
	wepName = "none";
	wepAtk = 0;
}
void Knight::print(){
	cout << "Knight " << name << endl;
	printHelper(); //call Character's print
	//unique to Knight
	cout << setw(16) << "Weapon:" << wepName << endl
			<< setw(16) << "(W) Attack:" << wepAtk << endl
			<< setw(16) << "Armor:" << armor << endl;
	cout << endl;
}
int Knight::getAttack(){
	//random number from 10~20 + weapon attack
	return (rand()%11) + 10 + wepAtk;
}
void Knight::reduceHP(int dmg){
	int dmgTaken = dmg - armor;
	if(dmgTaken >0){ //armor unable to block completely
		HP -= dmgTaken; //then take the resulting damage
		if(isDead()){
			HP =0;
		}
	}else{ //no damage taken
		dmgTaken = 0;
	}
	cout << name << " received " << dmgTaken << " damage!" << endl;
}
int Knight::increaseXP(int pts){
	//add pts to experience pts
	int levelUp=0;
	XP += pts;
	//check level up (may occur multiple times at once)
	while(XP >= ptsLeft){
		//increase pts to next level
		ptsLeft += 15;
		//increase stats
		maxHP += 15;
		armor++;
		//recover 1/10 of missing hp
		HP += (maxHP - HP) /10;
		levelUp++;
	}
	return levelUp;
}
bool Knight::canEquip(){
	return true;
}
//"equip" the weapon by updating this knight's stats
void Knight::equipWep(string wName, int wAtk){
	wepAtk = wAtk;
	wepName = wName;
}
