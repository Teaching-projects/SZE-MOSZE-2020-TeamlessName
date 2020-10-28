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
		throw(NoFileException(file_name)); //File does not exist
	}
	std::map<std::string, std::string> attributes;
	try
	{
		attributes = JSON::parseFromIstream(infile);
	}
	catch (const InputFormatException& format) //catch primitive exception
	{
		infile.close();
		throw(FileFormatException(file_name, format.what())); //throw a more meaningful exception, storing place of error
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

	if (attributes.find("hp") != attributes.end())
	{
		try
		{
			hp = std::stoi(attributes["hp"]);


		}
		catch (const std::invalid_argument&)
		{
			throw(InterpretException(file_name, "hp"));  //replace invalid_argument exception with own
		}
	}

	if (attributes.find("dmg") != attributes.end())
	{
		try
		{
			dm = std::stoi(attributes["dmg"]);

		}
		catch (const std::invalid_argument&)
		{
			throw(InterpretException(file_name, "dmg"));  //replace invalid_argument exception with own
		}


				//try to convert attackspeed
		try
		{
			as = std::stof(attributes["attackspeed"]);
		}
		catch (const std::invalid_argument&)
		{
			throw(InterpretException(file_name, "attackspeed"));  //replace invalid_argument exception with own
		}

	}




	if (nm == "" || hp == -1 || dm == -1 || as == -1.0)
	{
		throw(InvalidContentOfFileException(file_name, nm, hp, dm, as)); //Invalid or missing contents
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

	enemy.gotHit(*this);
	gotHit(enemy);
	float timer = 0.0;

	while (isAlive() && enemy.isAlive())
	{
		timer += fasterUnitCD;
		if (sUnit->getAS() < timer)
		{
			fUnit->gotHit(*sUnit);
			if (fUnit->isAlive())
			{
				sUnit->gotHit(*fUnit);
				timer -= sUnit->getAS();
			}
		}
		else if (sUnit->getAS() > timer)
		{
			sUnit->gotHit(*fUnit);
		}
		else //sUnit.getAS == timer
		{
			enemy.gotHit(*this);
			if (enemy.isAlive())
			{
				gotHit(enemy);
			}
			timer = 0.0;
		}
		timer += fasterUnitCD;
	}
}
