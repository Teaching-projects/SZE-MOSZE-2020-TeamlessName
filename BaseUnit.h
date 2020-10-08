#pragma once

#include<string>

// Base of all unit types, specialized units may derive from this
class BaseUnit
{
private:
	int HP; //health ponits (current or max, may change during developement, according to the task)
	const int DMG; //damage, the amount this unit hits with
	const std::string Name;
	float AS; //attackspeed, seconds per attack

public:
	BaseUnit(const std::string& nm, int hp, int dmg, float as);

	void gotHit(const BaseUnit&);
	std::string showStats() const;

	static BaseUnit parseUnit(const std::string&);

	const int getHP() const { return HP; }
	const int getDMG() const { return DMG; }
	const float getAS() const { return AS; }
	const std::string& getName() const { return Name; }
	bool isDead() const;

};
