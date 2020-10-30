#include "Hero.h"
#include "Exceptions.h"
#include "JSON.h"
#include <math.h>
#include <algorithm>
#include <fstream>
#include <map>




Hero::Hero(const std::string & nm, int hp, int dmg,double cd, int xpgap, int hpbonus, int dmgbonus, double cdMulti) 
		: Monster(nm, hp, dmg, cd), XPgap(xpgap), HPbonus(hpbonus), DMGbonus(dmgbonus), CDMultiplier(cdMulti), XP(0)
{
}

void Hero::levelUp()
{
	while (XP >= XPgap)
	{
		maxHP = std::lround(maxHP + HPbonus);
		DMG = std::lround(DMG + DMGbonus);
		HP = maxHP;
		CD = CD * CDMultiplier;
		Lvl++;
		XP = XP - XPgap;
	}


}

Hero Hero::parse(const std::string &file_nam)
{
	std::string file_name = "./units/" + file_nam;
	std::fstream infile(file_name);

	if (!infile.is_open())
	{
		std::cout << file_name;
		throw(NoFileException(file_name)); //File does not exist
		//throw(JSON::ParseException());
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
		//throw(JSON::ParseException());
	}

	infile.close();

	std::string nm = "";
	int hp = -1;
	int dm = -1;
	double cd = -1.0;
	int xp = -1;
	int hpb = -1;
	int dmb = -1;
	double cdm = -0.1;


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
			throw(InterpretException(file_name, "hp"));  //replace invalid_argument exception with own
			//throw(JSON::ParseException());
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
			throw(InterpretException(file_name, "dmg"));  //replace invalid_argument exception with own
			//throw(JSON::ParseException());
		}


				//try to convert attackspeed
		try
		{
			cd = std::stod(attributes["base_attack_cooldown"]);
		}
		catch (const std::invalid_argument&)
		{
			throw(InterpretException(file_name, "base_attack_cooldown"));  //replace invalid_argument exception with own
			//throw(JSON::ParseException());
		}

		try
		{
			xp = std::stoi(attributes["experience_per_level"]);
		}
		catch (const std::invalid_argument&)
		{
			throw(InterpretException(file_name, "experience_per_level"));  //replace invalid_argument exception with own
			//throw(JSON::ParseException());
		}

		try
		{
			hpb = std::stoi(attributes["health_point_bonus_per_level"]);
		}
		catch (const std::invalid_argument&)
		{
			throw(InterpretException(file_name, "health_point_bonus_per_level"));  //replace invalid_argument exception with own
			//throw(JSON::ParseException());
		}

		try
		{
			dmb = std::stoi(attributes["damage_bonus_per_level"]);
		}
		catch (const std::invalid_argument&)
		{
			throw(InterpretException(file_name, "damage_bonus_per_level"));  //replace invalid_argument exception with own
			//throw(JSON::ParseException());
		}

		try
		{
			cdm = std::stod(attributes["cooldown_multiplier_per_level"]);
		}
		catch (const std::invalid_argument&)
		{
			throw(InterpretException(file_name, "cooldown_multiplier_per_level"));  //replace invalid_argument exception with own
			//throw(JSON::ParseException());
		}

	}




	if (nm == "" || hp == -1 || dm == -1 || cd == -1.0)
	{
		throw(InvalidContentOfFileException(file_name, nm, hp, dm, cd)); //Invalid or missing contents
		//throw(JSON::ParseException());
	}

	return Hero(nm, hp, dm, cd, xp, hpb, dmb, cdm);

}

void Hero::causeDamage(Monster* enemy)
{
	XP += std::min(DMG, enemy->getHealthPoints());
	enemy->gotHit(*this);
	levelUp();
}
std::string Hero::showStats() const {

	return Name + ": HP:" + std::to_string(HP) + " DMG: " + std::to_string(DMG)
		+ " EXP: " + std::to_string(XP) + " LVL: " + std::to_string(Lvl);
}
