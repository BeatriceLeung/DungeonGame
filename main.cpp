/*
11/24/21
CS-116
HW 10 - Game lab
Create class Character and derived classes Novice, Knight,
and Wizard. With a vector of base class pointers, develop
a simple game.
 */
#include "character.h"
#include "novice.h"
#include "knight.h"
#include "wizard.h"

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cmath>
#include <vector>
using namespace std;

void testClasses();
void testCreateCharAndCreateMap();

void createChar(vector<Character*>&);
char* createMap(int&, int&, char);
int getPartyLuck(vector<Character*>);
int getPartyAveAttack(vector<Character*>);

void displayStats(vector<Character*>);
bool checkTravel(char[], int, int, char, char, bool&);
bool menu(vector<Character*>&, char[], int, int, char);
void printMap(const char[], int, int);
bool encounter(vector<Character*>&);
void createMonster(vector<Character*>, string&, int&);
bool allActed(vector<Character*>);
void setAllNotActed(vector<Character*>&);
void wepDrop(vector<Character*>&, string, int);


int main(){
	srand(time(0));
	cout << left;

	vector<Character*> party;
	char* map = nullptr;
	int height =0, width =0; //map dimensions
	bool gameClear;
//
//	party.push_back(new Novice("Bob"));
//	party.push_back(new Knight("Joe"));
//	party.push_back(new Wizard("Carl"));
//  testClasses();
//	testCreateCharAndCreateMap();
//	cout << encounter(party);

	createChar(party);
	map = createMap(height, width, '*');

	gameClear = menu(party, map, height, width, '*');

	if(gameClear){
		cout << "GAME CLEAR" << endl;
	}else{
		cout << "GAME OVER" << endl;
	}
//	delete the Character* s
	for(int i=0; i<party.size(); i++){
		cout << "bye " << party[i]->getName() << endl;
		delete party[i];
	}
//	delete the int array
	delete [] map;

	cout << endl <<  "Coded by Beatrice Leung" << endl;
	return 0;
}
//create characters and add them to the party
void createChar(vector<Character*>& party){
	int opt;
	string name;
	cout << "0     Novice" << endl << "1     Knight" << endl
			<< "2     Wizard" << endl;
	cout << "Choose a character type(#): ";
	cin >> opt;

	while(opt != 9){ //not quit
		cout << "Character's name(spaces are ok): ";
		cin.ignore();
		getline(cin, name);
		//create and add the appropriate type of character to the vector
		switch(opt){
		case 0:
			party.push_back(new Novice(name)); break;
		case 1:
			party.push_back(new Knight(name)); break;
		case 2:
			party.push_back(new Wizard(name)); break;
		}
		cout << "Add another character or 9 to finish(#): ";
		cin >> opt;
	}
	//all characters have been added
}
//prompt for a map size and return a char array to represent it
char* createMap(int& h, int& w, char partyMark){
	char dummy;
	//determine map size
	cout << "Map dimensions? (heightxwidth)" << endl
			<< "(ex: 3x3 7x10 4x15) : ";
	cin >> h >> dummy >> w;
	char* map = new char[h*w]; //simulate a 2D array
	//mark all as O
	for(int i=0; i< h*w; i++)
		map[i] = 'O';
	map[0] = partyMark; //start position
	map[h*w -1] = '-'; //goal
	return map;
}
//calculate the total luck of the party (Novice's luck stat)
int getPartyLuck(vector<Character*> party){
	int luck=0;
	//add up luck of all members
	for(int i=0; i<party.size(); i++)
		luck+=party[i]->getLuck();
	return luck;
}
//return the average attack of the party
int getPartyAveAttack(vector<Character*> party){
	int attack=0;
		//add up attack of all members
		for(int i=0; i<party.size(); i++)
			attack+=party[i]->getAttack();
		return ceil (1.0 * attack / party.size());
}
//print all character stats
void displayStats(vector<Character*> party){
	for(int i=0; i<party.size(); i++)
		party[i]->print();
}
//return false if next position is invalid (i.e. a "wall")
//make the move and return true otherwise
//passed means if have previously traveled to the next position
bool checkTravel(char map[], int h, int w, char move, char partyMark, bool& passed){
	int pos;
	int nextPos;
	int size = h * w;
	passed = false;
	//first find the party's position in the array
	for(int i=0; i<size; i++){
		if(map[i] == partyMark)
			pos = i; //party position
	}
	//determine if move is valid. if so, make the move.
	//if not, do nothing and return false
	switch(toupper(move)){
	case 'L': //left
		if(pos%w ==0) //if on far left of map
			return false; //can't go left, out of bounds
		//will move to:
		nextPos = pos-1;
		break;
	case 'R': //right
		if((pos+1)%w ==0) //far right of map
			return false;
		//move
		nextPos = pos+1;
		break;
	case 'U': //up
		if(pos < w) //very top of map
			return false;
		nextPos = pos-w;
		break;
	case 'D': //down
		if(pos >= w * (h-1)) //very bottoms
			return false;
		nextPos = pos+w;
		break;
	}
	if(map[nextPos]=='X')
		passed = true;
	//actually make the move
	map[nextPos] = partyMark;
	map[pos] = 'X'; //mark previous position as passed through
	return true; //move was successful
}
//will loop until either entire party is dead or goal has been reached
//true if goal, false if all dead
bool menu(vector<Character*>& party, char map[], int h, int w, char partyMark){
	char move;
	bool revisit, stillAlive = true;
	printMap(map, h, w);
	//prompt for move or display party stats
	cout << setw(5) << "R/L" << "move right/left" << endl
			<< setw(5) << "U/D" << "move up/down" << endl
			<< setw(5) << "S" << "show stats" << endl
			<< setw(5) << "Q" << "quit the game" << endl;
	while(map[h*w -1] == '-' && stillAlive){ //while not at goal and still alive
		cout << "Enter a letter (R/L/U/D/S/Q): ";
		cin >> move;
		move = toupper(move);
		cout << endl;
		if(move == 'S') //show stats
			displayStats(party);
		else if(move == 'Q'){ //quit
			return false; //exit the function, game not cleared
		}else if(move=='R'||move=='L'||move=='U'||move=='D'){
			//check if the move is valid (and make it, if it is)
			if(!checkTravel(map, h, w, move, partyMark, revisit)){
				cout << "Invalid spot" << endl;
			}else if(!revisit && rand()%2 ==0){ //new path
				//50% chance of monster
				//will not occur on already passed paths
				stillAlive = encounter(party);
			}
			//after some move, whether new path/retrek old path
			printMap(map, h, w);
		}else{ //no valid option given
			cout << "Invalid option" << endl;
			cin.clear();
			cin.ignore(100,'\n');
		}
	}
	return stillAlive; //will be false if quit game or all characters dead
}

//returns true if party still has alive characters, false otherwise
bool encounter(vector<Character*>& party){
	int mHP, maxmHP, mAtk;
	string mName;
	int charaAtk, charaTurn;
	//create the monster
	createMonster(party, mName, mHP);
	maxmHP = mHP;

	cout << "ENCOUNTER" << endl << mName << ", HP: " << mHP << endl;

	//start the actual fight
	//random character attacked first
	charaTurn = rand() % party.size();

	while(mHP>0){ //while enemy still alive
		//Enemy attacks first
		mAtk = maxmHP / 3;
		//character takes damage
		party[charaTurn]->reduceHP(mAtk);

		//print their resulting HP
		party[charaTurn]->printHPandMax();
		cout << endl << endl;
		if(party[charaTurn]->isDead()){ //if that killed them
			cout << party[charaTurn]->getName()<<" was unable to survive it." << endl;
			//delete that character
			delete party[charaTurn];
			//move the others to fill the gap
			for(int i = charaTurn; i<party.size()-1; i++){
				party[i] = party[i+1];
			}
			party.pop_back(); //remove the extra at the end
			//further check if all members are dead
			if(party.size()==0)
				return false;
		}
		//now user's turn to attack
		//first reset hasActed if all characters have gone in this encounter
		if(allActed(party)){
			setAllNotActed(party);
		}
		//display the available characters that have not acted yet
		for(int i=0; i<party.size(); i++){
			if(!party[i]->getActed()){
				cout << setw(5) << i << setw(16) << party[i]->getName();
				party[i]->printHPandMax();
				cout << endl;
			}
		}
		cout << "Select a character to act(#): ";
		cin >> charaTurn;
		//validate- valid index, character that has not acted yet
		while(!(charaTurn>=0 && charaTurn < party.size())|| !cin || party[charaTurn]->getActed()){
			cout << "Invalid option: ";
			cin.clear();
			cin.ignore(100, '\n');
			cin >> charaTurn;
		}
		//have this character do their action
		charaAtk = party[charaTurn]->action(party);
		if(charaAtk !=0){ //an actual attack, not wizard's unique heal action
			mHP -= charaAtk;
			cout <<"The " <<mName << " received " << charaAtk << " damage! ";
			if(mHP>0) //if monster is still alive
				cout << "HP: " << mHP << " / " << maxmHP << endl << endl;
		}
	}
	//enemy is dead
	cout << "The " << mName << " has been defeated." << endl << endl;
	//50% chance a weapon drops
	if(rand()%2 ==0)
		wepDrop(party, mName, maxmHP);

	cout <<"Battle results: " << endl;
	//add xp and display levels gained
	int levels;
	for(int i=0; i<party.size(); i++){
		levels = party[i]->increaseXP(maxmHP/(party.size()+1)); //monster maxHP / (party size + 1)
		//character to defeat monster gets extra XP
		if(i==charaTurn)
			levels += party[i]->increaseXP(maxmHP/(party.size()+1));
		//print resulting XP and levels gained
		cout << setw(16) << party[i]->getName() << "lvl +" << setw(5)
				<< levels << "XP: " << party[i]->getXP() << endl;
	}

	//prepare for future fights
	setAllNotActed(party);
	return true;
}
//true if all characters have acted this turn, false otherwise
bool allActed(vector<Character*> party){
	for(int i=0; i<party.size(); i++){
		if(!party[i]->getActed()) //if even one character hasn't acted
			return false;
	}
	return true; //all characters have acted
}
void setAllNotActed(vector<Character*>& party){
	for(int i=0; i<party.size();i++)
		party[i]->setActed(false);
}
//create a monster
//monster stats depend on party's average attack, scaled by some random factor
//luck decreases chances of stronger monsters
void createMonster(vector<Character*> party, string& mName, int& mHPAtk){
	string mNames[] = {"Orc","Orge","Wraith","Slime","Imp"};
	double scale;

	int luckDecrease=0;
	if(getPartyLuck(party)>0){
		// y = x / (x+10)
		//horizontal asymptote, concave down increasing
		//less obvious effects as luck increases
		//capped at 50
		luckDecrease = ceil(50 * getPartyLuck(party)/(getPartyLuck(party)+5.0));
		luckDecrease = rand() % luckDecrease;
	}
	int num = rand() %100 - luckDecrease; // 0~99 - 0~50(depending on luck)
	//determine monster stats
	if(num<20){
		mName="Weak ";
		scale = 1;
	}else if(num<50){
		mName="Normal ";
		scale = 2;
	}else if(num<70){
		mName="Strong ";
		scale = rand()%2 + 3; //3~4
	}else if(num < 95){
		mName = "Powerful ";
		scale = rand()%3 + 4; //5~7
	}else{
		mName = "Catastrophic ";
		scale = 9;
	}
	//finish monster stats
	mName += mNames[rand()%5];
	mHPAtk = round(getPartyAveAttack(party) * scale);
}
//chance for a weapon to drop after fight finished
void wepDrop(vector<Character*>& party, string mName, int maxmHP){
	int count=0;
	//first check if there are any knights to equip the weapon
	for(int i=0; i<party.size(); i++){
		if(party[i]->canEquip())
			count++;
	}
	if(count==0) //no knights in the party, so don't bother
		return;

	string name;
	int num;
	int atk;
	char opt;
	int intOpt;
	//determine weapons stats
	num = rand()%50;

	if(num<25){ //0~24 50%
		atk = ceil(maxmHP/3);
		name = "Poor ";
	}else if(num<42){ //25~41 34%
		atk = ceil(maxmHP/2);
		name = "Fair ";
	}else if(num<49){ // 42~48 14%
		atk = maxmHP;
		name = "Excellent ";
	}else{ //49 2%
		atk = maxmHP*1.5;
		name = "Legendary ";
	}
	name = name + mName + "'s Sword";

	cout << "The " << mName << " dropped a " << name << ", "
			<< "weapon attack: " << atk << endl;
	cout << "Equip it? (the previous weapon will be discarded) (Y/N): ";
	cin >> opt;
	if(toupper(opt) == 'N')
		return; //do nothing
	//yes, then
	//display the characters who can equip weapons (i.e. knights)
	for(int i=0; i<party.size();i++){
		if(party[i]->canEquip())
			cout << setw(5) << i << party[i]->getName() << endl;
	}
	cout << "Choose a character to equip it(#): ";
	cin >> intOpt;
	//equip the weapon
	party[intOpt]->equipWep(name, atk);

}

//print the map
void printMap(const char map[], int h, int w){
	for(int i=0; i< h; i++){
		for(int j=0; j<w; j++){
			cout << map[(i*w) + j] << " ";
		}
		cout << endl;
	}
}

void testCreateCharAndCreateMap(){
	//seems good
	vector<Character*> party;
	char* map = nullptr;
	int height =0, width =0;

	createChar(party);
	map = createMap(height, width, '*');

	cout << "Height, width: " << height << ", " << width << endl;

	cout << map[0] << " "<< map[height*width -2]<<" " << map[height*width -1] << endl;

	for(int i=0; i<party.size(); i++){
			cout << i << "  "<< party[i]->getName() << " ";
		}

	cout << endl;

	//	delete the Character* s
	for(int i=0; i<party.size(); i++){
		delete party[i];
		cout << "bye ";
	}
	//	delete the int array
	delete [] map;
}

//test the class functions
void testClasses(){
	//seems alright
	vector<Character*> party;

	//switch the order around, function mainly tests the first character (index 0)
	party.push_back(new Knight("Joe"));
	party.push_back(new Novice("Bob"));

	party.push_back(new Wizard("Carl"));

/*

	//test the functions I added: action, getLuck, equipWep

	for(int i=0; i<party.size(); i++){
		party[i]->reduceHP(50);
		party[i]->print();
	}

	for(int i=0; i<party.size(); i++){
		cout << party[i]->getName() << ": "<< endl
				<< party[i]->action(party) << endl
				<< party[i]->getLuck() << endl;
		party[i]->equipWep("smth", 5);
	}


	for(int i=0; i<party.size(); i++){
		party[i]->print();
	}
	//check armor / magic attack in damage reduction
	party[0]->increaseXP(1000);
	party[0]->print();
	party[0]->reduceHP(50);
	party[0]->printHPandMax();
	cout << endl;
	if(party[0]->isDead()){
		cout << "Dead" <<endl;
	}else{
		cout << "Still kicking" << endl;
	}
*/
\
//given functions:
//works for both the pointer and the derived class itself
	cout << "From character class functions: " << endl
			<< "Name: " << party[0]->getName() << endl
			<< "HP: " << party[0]->getHP() << endl
			<< "XP: " <<  party[0]->getXP() << endl << endl;

	cout << "From the derived class: " << endl;
	party[0]->print();
	cout << "Attack: ";
	for(int i=0; i<10; i++)
		cout << party[0]->getAttack() << " ";
	cout << endl;
	cout << "Take 23 damage" << endl;
	party[0]->reduceHP(23);
	cout << "HP is now: " << party[0]->getHP() << endl;

	cout << "Test exp adding and level up" << endl;

	int levelup;
	levelup = party[0]->increaseXP(5);
	party[0]->print();
	cout <<levelup << endl;
	levelup = party[0]->increaseXP(5);
	party[0]->print();
	cout  <<levelup << endl;
	levelup = party[0]->increaseXP(31);
	party[0]->print();
	cout  <<levelup << endl;

	party[0]->heal();
	cout << "After healing, HP is now: " << party[0]->getHP() << endl;
	cout << "Which should match with: ";
	party[0]->printHPandMax();

	cout << endl << "Attack: ";
	for(int i=0; i<10; i++)
		cout << party[0]->getAttack() << " ";
	cout << endl;


	for(int i=0; i<party.size(); i++){
		delete party[i];
		cout << "bye ";
	}

}
