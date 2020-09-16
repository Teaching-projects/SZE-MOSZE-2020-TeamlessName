#pragma once

#include<string>

// Base of all unit types, specialized units may derive from this
class BaseUnit
{
private:
	int HP; //health ponits (current or max, may change during developement, according to the task)
	const int DMG; //damage, the amount this unit hits with
	const std::string Name;

	std::string stats;

public:
	BaseUnit(const std::string& nm, int hp, int dmg);

	bool gotHit(int dam);
	const std::string& showStats(); 

	const int getHP() const { return HP; }
	const int getDMG() const { return DMG; }
	const std::string& getName() const { return Name; }

};
