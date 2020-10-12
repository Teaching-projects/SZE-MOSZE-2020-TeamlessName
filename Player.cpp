#include "Player.h"
#include "Exceptions.h"
#include <math.h>
#include <fstream>

int Player::XPgap = 100;

Player::Player(const std::string & nm, int hp, int dmg) : BaseUnit(nm, hp, dmg), XP(0)
{
}

void Player::levelUp()
{
	while (XP >= XPgap)
	{
		maxHP = std::lround(HP * 1.1);
		DMG = std::lround(DMG * 1.1);
		HP = maxHP;

		XP = XP - XPgap;
	}

	
}

Player Player::parsePlayer(const std::string &file_name)
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
				snm = snm.substr(posFront + 1);

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


				std::string shp = line.substr(posFront + 1, posBack);
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
				std::string sdm = line.substr(posFront + 1);


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

	return Player(nm, hp, dm);
}

void Player::causeDamage(int caused)
{
	XP += caused;
	levelUp();
}
