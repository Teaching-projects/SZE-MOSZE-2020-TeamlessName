#include "BaseUnit.h"

BaseUnit::BaseUnit(const std::string& nm, int hp, int dmg) : Name{ nm }, HP{hp}, DMG{dmg}
{
}

//decreasing the HP of the suffering unit, return with false if it dies
bool BaseUnit::gotHit(int dam)
{
	HP = HP - dam;
	if (HP <= 0)
	{
		HP = 0;
		return false;
	}
		
	return true;
}

//Show current HP and DMG
std::string BaseUnit::showStats() const
{
	return Name + ": HP:" + std::to_string(HP) + " DMG: " + std::to_string(DMG);
}
