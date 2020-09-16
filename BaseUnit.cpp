#include "BaseUnit.h"

BaseUnit::BaseUnit(const std::string& nm, int hp, int dmg) : Name{ nm }, HP{hp}, DMG{dmg}
{
}

//decreasing the HP of the suffering unit
void BaseUnit::gotHit(BaseUnit& other)
{
	HP = HP - other.getDMG();
	if (HP <= 0)
	{
		HP = 0;
	}
}

//Show current HP and DMG
std::string BaseUnit::showStats() const
{
	return Name + ": HP:" + std::to_string(HP) + " DMG: " + std::to_string(DMG);
}
//returns with true if the unit has 0 HP
bool BaseUnit::isDead() const
{
	if (HP == 0)
	{
		return true;
	}
	return false;
}
