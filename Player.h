#pragma once
#include "BaseUnit.h"

class Player : public BaseUnit
{
private:
	int XP; //The amount of XP that is not used yet for level-up
	static int XPgap; //The amount of xp that is needed for a level-up

public:
	Player(const std::string& nm, int hp, int dmg);
	void levelUp();
	static Player parsePlayer(const std::string&);
	void causeDamage(int) override;

};

