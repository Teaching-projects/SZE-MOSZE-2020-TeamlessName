#pragma once
#include "Monster.h"

class Hero : public Monster
{
private:
	
	int XPgap; //The amount of xp that is needed for a level-up
	int HPbonus;
	int DMGbonus;
	float CDMultiplier;
	
	int XP; //The amount of XP that is not used yet for level-up
	int Lvl = 1;


	void levelUp();
public:
	Hero(const std::string& nm, int hp, int dmg,float as, int xpgap, int hpbonus, int dmgbonus, float cdMulti);
	static Hero parse(const std::string&);
	void causeDamage(Monster*) override;
	int getLevel() const { return Lvl; }
	int getXP() const { return XP; }
	std::string showStats() const override;
};

