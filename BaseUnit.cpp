#include "BaseUnit.h"
#include <fstream>


BaseUnit::BaseUnit(const std::string& nm, int hp, int dmg) : Name{ nm }, HP{hp}, DMG{dmg}
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
		throw(file_name);
	}

	std::string line;
	std::string nm = "";
	int hp = -1;
	int dm = -1;

	//loop to identify unit attributes
	while (!infile.eof())
	{
		std::getline(infile, line);

		size_t pos;

		//find name
		if (nm == "")
		{
			pos = line.find("name");

			if (pos != std::string::npos)
			{
				pos = line.find(":");
				nm = line.substr(pos + 3, line.size());
				nm.pop_back();
				nm.pop_back();

				continue;
			}
		}
		//find hp
		if (hp == -1)
		{
			pos = line.find("hp");
			if (pos != std::string::npos)
			{
				pos = line.find(":");
				std::string shp = line.substr(pos + 2, line.size());
				shp.pop_back();
				hp = std::stoi(shp);

				continue;
			}
			
		}
		//find dmg
		if (dm == -1)
		{
			pos = line.find("dmg");

			if (pos != std::string::npos)
			{
				pos = line.find(":");
				std::string sdm = line.substr(pos + 2, line.size());
				dm = std::stoi(sdm);

				continue;
			}
		}

	}

	infile.close();

	if (nm == "" || hp == -1 || dm == -1)
	{
		throw(4); //Invalid contents 
	}

	return BaseUnit(nm,hp,dm);
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
