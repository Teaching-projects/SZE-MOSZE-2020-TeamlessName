#pragma once

#include<string>

// Base of all unit types, specialized units may derive from this
class BaseUnit
{
private:
	int HP; //health ponits (current or max, may change during developement, according to the task)
	const int DMG; //damage, the amount this unit hits with
	const std::string Name;

public:
	BaseUnit(const std::string& nm, int hp, int dmg);

	void gotHit(BaseUnit&);
	std::string showStats() const; 

	const int getHP() const { return HP; }
	const int getDMG() const { return DMG; }
	const std::string& getName() const { return Name; }
	bool isDead() const;

};
