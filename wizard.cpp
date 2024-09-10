#include "wizard.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;


Wizard::Wizard(string na)
 : Character(na, 100, 0, 5){ //character param constructor
	//default stats -- can only give name
	mAtk = 0;
}
void Wizard::print(){
	cout << "Wizard " << name << endl;
	printHelper(); //call Character's print
	//unique to Wizard
	cout << setw(16) << "(M) Attack:" << mAtk << endl;
	cout << endl;
}
int Wizard::getAttack(){
	//random number from 5~15 + magic attack
	return (rand()%11) + 5 + mAtk;
}
void Wizard::reduceHP(int dmg){
	int dmgTaken= dmg - round(static_cast<double>(mAtk)/dmg);
	if(dmgTaken>0){
		HP -= dmgTaken;
		if(isDead())
			HP =0;
	}else
		dmgTaken = 0;
	cout << name << " received " << dmgTaken << " damage!" << endl;
}
int Wizard::increaseXP(int pts){
	int levelUp=0;
	//add pts to experience pts
	XP += pts;
	//check level up (may occur multiple times at once)
	while(XP >= ptsLeft){
		//increase pts to next level
		ptsLeft += 12;
		//increase stats
		maxHP += 8;
		mAtk += 3;
		//recover 1/10 of missing hp
		HP += (maxHP - HP) /10;
		levelUp++;
	}
	return levelUp;
}

int Wizard::action(vector<Character*>& party){
	hasActed = true;
	int option;
	//wizard can either choose to attack or heal a character
	cout << "1     Attack" << endl
			<<"2     Heal" << endl << "Option(#): ";
	cin >> option;
	if(option==1)
		return getAttack();
	//heal, then
	//display all party members with their current HP
	for(int i=0; i<party.size(); i++){
		cout << setw(5) << i << setw(10) << party[i]->getName();
		party[i]->printHPandMax();
		cout << endl;
	}
	cout << "Select a character to heal(#): ";
	cin >> option;
	//heal the selected member
	party[option]->heal();
	return 0; //did not attack
}
