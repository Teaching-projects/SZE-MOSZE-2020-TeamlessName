#include "BaseUnit.h"
#include "Exceptions.h"
#include "JsonParser.h"
#include <map>
#include <fstream>



BaseUnit::BaseUnit(const std::string & nm, int hp, int dmg, float as) : Name{ nm }, maxHP(hp), HP{ hp }, DMG{ dmg }, AS{ as }

{
}
//decreasing the HP of the suffering unit
void BaseUnit::gotHit(const BaseUnit& other)
{
	if (other.getDMG() >= HP) HP = 0;
	else HP = HP - other.getDMG();
}
//Show current HP and DMG
std::string BaseUnit::showStats() const
{
	return Name + ": HP:" + std::to_string(HP) + " DMG: " + std::to_string(DMG);
}

void BaseUnit::causeDamage(BaseUnit* enemy)
{
	enemy->gotHit(*this);
}

BaseUnit BaseUnit::parseUnit(const std::string & file_name)
{
	std::fstream infile(file_name);

	if (!infile.is_open())
	{
		throw(NoFileException(file_name)); //File does not exist
	}
	std::map<std::string, std::string> attributes;
	try
	{
		attributes = JsonParser::parseJson(infile);
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

	return BaseUnit(nm, hp, dm, as);
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
void BaseUnit::Attack(BaseUnit& enemy)
{
	BaseUnit* fUnit;
	BaseUnit* sUnit;
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

	while (!isDead() && !enemy.isDead())
	{
		timer += fasterUnitCD;
		if (sUnit->getAS() < timer)
		{
			fUnit->gotHit(*sUnit);
			if (!fUnit->isDead())
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
			if (!enemy.isDead())
			{
				gotHit(enemy);
			}
			timer = 0.0;
		}
		timer += fasterUnitCD;
	}
}
