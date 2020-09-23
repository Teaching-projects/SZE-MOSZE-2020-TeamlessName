#include "BaseUnit.h"
#include "Exceptions.h"
#include <fstream>
#include <iostream>


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
		throw(NoFileException(file_name)); //File does not exist
	}

	std::string line;
	std::string nm = "";
	int hp = -1;
	int dm = -1;

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
				snm = snm.substr(posFront+1, snm.size());

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

				const std::string WHITESPACES = " \t\v";
				

				while (true)
				{
					if (WHITESPACES.find(shp[0]) != std::string::npos)
					{
						shp.erase(shp.begin());
					}
					else
					{
						break;
					}
				}
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
				std::string sdm = line.substr(posFront+1, line.size());

				const std::string WHITESPACES = " \t\v";


				while (true)
				{
					if (WHITESPACES.find(sdm[0]) != std::string::npos)
					{
						sdm.erase(sdm.begin());
					}
					else
					{
						break;
					}
				}
				
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

	}

	infile.close();

	if (nm == "" || hp == -1 || dm == -1)
	{
		throw(InvalidContentOfFileException(file_name, nm, hp, dm)); //Invalid or missing contents 
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
