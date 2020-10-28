#pragma once
#include "Monster.h"

class Hero : public Monster
{
private:
	int XP; //The amount of XP that is not used yet for level-up
	static int XPgap; //The amount of xp that is needed for a level-up
	int Lvl = 1;
	void levelUp();
public:
	Hero(const std::string& nm, int hp, int dmg,float as);
	static Hero parse(const std::string&);
	void causeDamage(Monster*) override;
	int getLevel() const { return Lvl; }
	int getXP() const { return XP; }
	std::string showStats() const override;
};

