#include "Monster.h"
#include "Exceptions.h"
#include "JSON.h"
#include <fstream>



Monster::Monster(const std::string & nm, int hp, int dmg, double cd, int df) 
		: Name{ nm }, maxHP(hp), HP{ hp }, DMG{ dmg }, CD{ cd }, DF{df}

{
}
//decreasing the HP of the suffering unit
void Monster::gotHit(const Monster& other)
{
	if (other.getDMG() >= HP) HP = 0;
	else HP = HP - other.getDMG();
}
//Show current HP and DMG
std::string Monster::showStats() const
{
	return Name + ": HP:" + std::to_string(HP) + " DMG: " + std::to_string(DMG);
}

void Monster::causeDamage(Monster* enemy)
{
	enemy->gotHit(*this);
}

Monster Monster::parse(const std::string & file_nam)
{
	std::string file_name = "./units/" + file_nam;
	std::fstream infile(file_name);

	if (!infile.is_open())
	{
		throw(JSON::ParseException());
	}

	std::string nm = "";
	int hp = -1;
	int dm = -1;
	double cd = -1.0;
	int df = -1;


	try
	{
		JSON attributes = JSON::parseFromIstream(infile);
		nm = attributes.get<std::string>("name");
		hp = attributes.get<int>("health_points");
		dm = attributes.get<int>("damage");
		cd = attributes.get<double>("attack_cooldown");
		df = attributes.get<int>("defense");
	}
	catch (const std::out_of_range&)
	{
		infile.close();
		throw(JSON::ParseException());
	}
	catch (const InputFormatException&)
	{
		infile.close();
		throw(JSON::ParseException());
	}
	catch (const std::bad_variant_access&)
	{
		infile.close();
		throw(JSON::ParseException());
	}
	infile.close();

	return Monster(nm, hp, dm, cd, df);
}
//returns with true if the unit has 0 HP
bool Monster::isAlive() const
{
	if (HP > 0)
	{
		return true;
	}
	return false;
}
void Monster::fightTilDeath(Monster& enemy)
{
	Monster* fUnit;
	Monster* sUnit;
	double fasterUnitCD;

	if (getCD() < enemy.getCD())
	{
		fasterUnitCD = getCD();
		fUnit = this;
		sUnit = &enemy;
	}
	else
	{
		fasterUnitCD = enemy.getCD();
		fUnit = &enemy;
		sUnit = this;
	}

	causeDamage(&enemy);
	enemy.causeDamage(this);
	double timer = 0.0;

	while (isAlive() && enemy.isAlive())
	{
		timer += fasterUnitCD;
		if (sUnit->getCD() < timer)
		{
			sUnit->causeDamage(fUnit);
			if (fUnit->isAlive())
			{
				fUnit->causeDamage(sUnit);
				timer -= sUnit->getCD();
			}
		}
		else if (sUnit->getCD() > timer)
		{
			fUnit->causeDamage(sUnit);
		}
		else
		{
			causeDamage(&enemy);
			if (enemy.isAlive())
			{
				enemy.causeDamage(this);
			}
			timer = 0.0;
		}
		timer += fasterUnitCD;
	}
}
