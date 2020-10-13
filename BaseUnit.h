#pragma once

#include<string>

// Base of all unit types, specialized units may derive from this
class BaseUnit
{
protected:
	int maxHP; //maximum health points
	int HP; //current health ponits 
	int DMG; //damage, the amount this unit hits with
	const std::string Name;

public:
	BaseUnit(const std::string& nm, int hp, int dmg);

	int gotHit(const BaseUnit&);
	virtual std::string showStats() const;
	virtual void causeDamage(BaseUnit*);
	static BaseUnit parseUnit(const std::string&);
	const int getHP() const { return HP; }
	const int getDMG() const { return DMG; }
	const std::string& getName() const { return Name; }
	bool isDead() const;

};
