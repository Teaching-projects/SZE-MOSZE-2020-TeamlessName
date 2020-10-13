#include "Player.h"
#include "Exceptions.h"
#include <math.h>
#include <algorithm>
#include <fstream>

int Player::XPgap = 100;

Player::Player(const std::string & nm, int hp, int dmg) : BaseUnit(nm, hp, dmg), XP(0)
{
}

void Player::levelUp()
{
	while (XP >= XPgap)
	{
		maxHP = std::lround(maxHP * 1.1);
		DMG = std::lround(DMG * 1.1);
		HP = maxHP;
		Lvl++;
		XP = XP - XPgap;
	}

	
}

Player Player::parsePlayer(const std::string &file_name)
{
	BaseUnit Unit = BaseUnit::parseUnit(file_name);
	return Player(Unit.getName(), Unit.getHP(), Unit.getDMG());

}

void Player::causeDamage(BaseUnit* enemy)
{
	XP += std::min(DMG, enemy->getHP());
	enemy->gotHit(*this);
	levelUp();
}
std::string Player::showStats() const {

	return Name + ": HP:" + std::to_string(HP) + " DMG: " + std::to_string(DMG) 
		+ " EXP: " + std::to_string(XP) + " LVL: " + std::to_string(Lvl);
}
