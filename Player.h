#pragma once
#include "BaseUnit.h"

class Player : public BaseUnit
{
private:
	int XP; //The amount of XP that is not used yet for level-up
	static int XPgap; //The amount of xp that is needed for a level-up
	int Lvl = 1;
	void levelUp();
public:
	Player(const std::string& nm, int hp, int dmg);
	static Player parsePlayer(const std::string&);
	void causeDamage(BaseUnit*) override;
	int getLvl() const { return Lvl; }
	int getXP() const { return XP; }
	std::string showStats() const override;
};

