#include "Monster.h"
#include "Exceptions.h"
#include "JSON.h"
#include <map>
#include <fstream>



Monster::Monster(const std::string & nm, int hp, int dmg, float as) : Name{ nm }, maxHP(hp), HP{ hp }, DMG{ dmg }, AS{ as }

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

Monster Monster::parse(const std::string & file_name)
{
	std::fstream infile(file_name);

	if (!infile.is_open())
	{
		//throw(NoFileException(file_name)); //File does not exist
		throw(JSON::ParseException());
	}
	std::map<std::string, std::string> attributes;
	try
	{
		attributes = JSON::parseFromIstream(infile);
	}
	catch (const InputFormatException& format) //catch primitive exception
	{
		infile.close();
		//throw(FileFormatException(file_name, format.what())); //throw a more meaningful exception, storing place of error
		throw(JSON::ParseException());
	}

	infile.close();

	std::string nm = "";
	int hp = -1;
	int dm = -1;
	float as = -1.0;

	if (attributes.find("name") != attributes.end())
	{
		nm = attributes["name"];
	}

	if (attributes.find("base_health_points") != attributes.end())
	{
		try
		{
			hp = std::stoi(attributes["base_health_points"]);


		}
		catch (const std::invalid_argument&)
		{
			//throw(InterpretException(file_name, "hp"));  //replace invalid_argument exception with own
			throw(JSON::ParseException());
		}
	}

	if (attributes.find("base_damage") != attributes.end())
	{
		try
		{
			dm = std::stoi(attributes["base_damage"]);

		}
		catch (const std::invalid_argument&)
		{
			//throw(InterpretException(file_name, "dmg"));  //replace invalid_argument exception with own
			throw(JSON::ParseException());
		}


				//try to convert attackspeed
		try
		{
			as = std::stof(attributes["base_attack_cooldown"]);
		}
		catch (const std::invalid_argument&)
		{
			//throw(InterpretException(file_name, "attackspeed"));  //replace invalid_argument exception with own
			throw(JSON::ParseException());
		}

	}




	if (nm == "" || hp == -1 || dm == -1 || as == -1.0)
	{
		//throw(InvalidContentOfFileException(file_name, nm, hp, dm, as)); //Invalid or missing contents
		throw(JSON::ParseException());
	}

	return Monster(nm, hp, dm, as);
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
	float fasterUnitCD;

	if (getAS() < enemy.getAS())
	{
		fasterUnitCD = getAS();
		fUnit = this;
		sUnit = &enemy;
	}
	else
	{
		fasterUnitCD = enemy.getAS();
		fUnit = &enemy;
		sUnit = this;
	}

	causeDamage(&enemy);
	enemy.causeDamage(this);
	float timer = 0.0;

	while (isAlive() && enemy.isAlive())
	{
		timer += fasterUnitCD;
		if (sUnit->getAS() < timer)
		{
			sUnit->causeDamage(fUnit);
			if (fUnit->isAlive())
			{
				fUnit->causeDamage(sUnit);
				timer -= sUnit->getAS();
			}
		}
		else if (sUnit->getAS() > timer)
		{
			fUnit->causeDamage(sUnit);
		}
		else //sUnit.getAS == timer
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
