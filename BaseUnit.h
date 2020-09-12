#pragma once

#include<string>

// Base of all unit types, specialized units may derive from this
class BaseUnit
{
private:
	int HP; //health ponits (current or max, may change during developement, according to the task)
	int DMG; //damage, the amount this unit hits with
	std::string Name;

public:
	BaseUnit(std::string nm, int hp, int dmg);

	bool gotHit(int dam);
	std::string ShowStats(); 

	int getHP() { return HP; }
	int getDMG() { return DMG; }
	std::string getName() { return Name; }

};
