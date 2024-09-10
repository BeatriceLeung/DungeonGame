#include "novice.h"
#include <iostream>
#include <iomanip>
using namespace std;

Novice::Novice(string na)
 : Character(na, 80, 0, 10){ //character param constructor
	//default stats -- can only give name
	luck = 1;
}
void Novice::print(){
	cout << "Novice " << name << endl;
	//call Character's print for basic stats
	printHelper();
	//unique to Novice
	cout << setw(16) << "Luck:" << luck << endl;
	cout << endl;
}
int Novice::getAttack(){
	//random number from 1~10 + luck
	return (rand()%10) + 1 + luck;
}
void Novice::reduceHP(int dmg){
	HP -= dmg;
	if(isDead()){ //HP <= 0
		HP =0;
	}
	cout << name << " received " << dmg << " damage!" << endl;
}
//increases stats and
//returns number of times leveled up
int Novice::increaseXP(int pts){
	int levelUp=0;
	//add pts to experience pts
	XP += pts;
	//check level up (may occur multiple times at once)
	while(XP >= ptsLeft){
		//increase pts to next level
		ptsLeft += 10;
		//increase stats
		maxHP += 10;
		luck += 3 + (rand()%3); //3~5
		//recover 1/10 of missing hp
		HP += (maxHP - HP) /10;
		levelUp++;
	}
	return levelUp;
}

int Novice::getLuck(){
	return luck;
}

