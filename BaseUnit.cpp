#include "BaseUnit.h"
#include "Exceptions.h"
#include <fstream>


BaseUnit::BaseUnit(const std::string& nm, int hp, int dmg, float as) : Name{ nm }, HP{hp}, DMG{dmg}, AS{as}
{
}

//decreasing the HP of the suffering unit
void BaseUnit::gotHit(const BaseUnit& other)
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
BaseUnit BaseUnit::parseUnit(const std::string& file_name)
{
	std::fstream infile(file_name);

	if (!infile.is_open())
	{
		throw(NoFileException(file_name)); //File does not exist
	}

	std::string line;
	std::string nm = "";
	int hp = -1;
	int dm = -1;
	float as = -1.0;

	//loop to identify unit attributes
	while (!infile.eof())
	{
		std::getline(infile, line);

		size_t posFront;
		size_t posBack;

		//find name
		if (nm == "")
		{
			std::string snm;
			posFront = line.find("\"name\"");
			posBack = line.find(",");

			if (posFront != std::string::npos && posBack != std::string::npos)
			{
				posFront = line.find(":");
				if (posFront == std::string::npos)
				{
					throw InterpretException(file_name, "name");
				}

				snm = line.substr(posFront, posBack);
				posFront = snm.find("\"");
				if (posFront == std::string::npos)
				{
					throw InterpretException(file_name, "name");
				}
				snm = snm.substr(posFront+1);

				posBack = snm.find("\"");
				if (posBack == std::string::npos)
				{
					throw InterpretException(file_name, "name");
				}
				nm = snm.substr(0, posBack);

				continue;
			}
		}
		//find hp
		if (hp == -1)
		{
			posFront = line.find("\"hp\"");
			if (posFront != std::string::npos)
			{
				posFront = line.find(":");
				posBack = line.find(",");

				if (posFront == std::string::npos || posBack == std::string::npos)
				{
					throw(InterpretException(file_name, "hp"));
				}


				std::string shp = line.substr(posFront+1, posBack);
				shp.pop_back();

				//try to convert hp
				try
				{
					hp = std::stoi(shp);
				}
				catch (const std::invalid_argument&)
				{
					throw(InterpretException(file_name, "hp"));  //replace invalid_argument exception with own
				}

				continue;
			}

		}
		//find dmg
		if (dm == -1)
		{
			posFront = line.find("\"dmg\"");

			if (posFront != std::string::npos)
			{
				posFront = line.find(":");
				std::string sdm = line.substr(posFront+1);


				//try to convert dmg
				try
				{
					dm = std::stoi(sdm);
				}
				catch (const std::invalid_argument&)
				{
					throw(InterpretException(file_name, "dmg"));  //replace invalid_argument exception with own
				}

				continue;
			}
		}
		//find attackspeed
		if (as == -1.0)
		{
			posFront = line.find("\"attackspeed\"");

			if (posFront != std::string::npos)
			{
				posFront = line.find(":");
				std::string sattackspeed = line.substr(posFront+1);


				//try to convert attackspeed
				try
				{
					as = std::stof(sattackspeed);
				}
				catch (const std::invalid_argument&)
				{
					throw(InterpretException(file_name, "attackspeed"));  //replace invalid_argument exception with own
				}

				continue;
			}
		}

	}

	infile.close();

	if (nm == "" || hp == -1 || dm == -1 || as == -1.0)
	{
		throw(InvalidContentOfFileException(file_name, nm, hp, dm, as)); //Invalid or missing contents
	}

	return BaseUnit(nm,hp,dm, as);
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
void BaseUnit::Attack(BaseUnit &enemy)
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
