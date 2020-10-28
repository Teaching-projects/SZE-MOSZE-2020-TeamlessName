#include "Hero.h"
#include "Exceptions.h"
#include <math.h>
#include <algorithm>
#include <fstream>

int Hero::XPgap = 100;

Hero::Hero(const std::string & nm, int hp, int dmg,float as) : Monster(nm, hp, dmg, as), XP(0)
{
}

void Hero::levelUp()
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

Hero Hero::parse(const std::string &file_name)
{
	Monster Unit = Monster::parse(file_name);
	return Hero(Unit.getName(), Unit.getHealthPoints(), Unit.getDMG(),Unit.getAS());

}

void Hero::causeDamage(Monster* enemy)
{
	XP += std::min(DMG, enemy->getHealthPoints());
	enemy->gotHit(*this);
	levelUp();
}
std::string Hero::showStats() const {

	return Name + ": HP:" + std::to_string(HP) + " DMG: " + std::to_string(DMG)
		+ " EXP: " + std::to_string(XP) + " LVL: " + std::to_string(Lvl);
}
