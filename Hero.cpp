#include "Hero.h"
#include "Exceptions.h"
#include "JSON.h"
#include <math.h>
#include <algorithm>
#include <fstream>

Hero::Hero(const std::string & nm, int hp, int pdmg, int mdmg, double cd, int df, int xpgap, int hpbonus,
		int dmgbonus, int mdmgbonus, double cdMulti, int dfbonus, unsigned int lr, unsigned int lrbonus) 
		: Monster(nm, hp, pdmg, mdmg, cd, df), XPgap(xpgap), HPbonus(hpbonus),
		  PDMGbonus(dmgbonus), MDMGbonus(mdmgbonus), CDMultiplier(cdMulti), DFbonus(dfbonus), XP(0), LightRadius(lr), LightRaiusbonus(lrbonus)
{
}

Hero::Hero(const Hero& other)
		: Hero(other.Name, other.maxHP, other.DMG.physical, other.DMG.magical, other.CD, other.DF,
			   other.XPgap, other.HPbonus, other.PDMGbonus, other.MDMGbonus, other.CDMultiplier,
			   other.DFbonus, other.LightRadius, other.LightRaiusbonus)
{
}

void Hero::levelUp()
{
	while (XP >= XPgap)
	{
		maxHP = std::lround(maxHP + HPbonus);
		DMG += Damage(PDMGbonus, MDMGbonus);
		HP = maxHP;
		CD = CD * CDMultiplier;
		DF += DFbonus;
		Lvl++;
		LightRadius += LightRaiusbonus;
		XP = XP - XPgap;
	}


}

Hero Hero::parse(const std::string &file_nam)
{
	std::string file_name = "./units/" + file_nam;
	std::fstream infile(file_name);

	if (!infile.is_open())
	{
		throw(JSON::ParseException());
	}


	std::string nm = "";
	int hp = -1;
	int pdm = 0;
	int mdm = 0;
	double cd = -1.0;
	int df = -1;
	int xp = -1;
	int hpb = -1;
	int dmb = 0;
	int mdb = 0;
	double cdm = -0.1;
	int dfb = -1;
	int lradius = 0;
	int lradbonus = 1;

	try
	{
		JSON attributes =JSON(JSON::parseFromIstream(infile));
		nm = attributes.get<std::string>("name");
		hp = attributes.get<int>("base_health_points");

		try
		{
			pdm = attributes.get<int>("base_damage");
		}
		catch(const std::out_of_range&)
		{
			pdm = 0;
		}
		try
		{
			mdm = attributes.get<int>("base_magical-damage");
		}
		catch(const std::out_of_range&)
		{
			mdm = 0;
		}

		cd = attributes.get<double>("base_attack_cooldown");
		df = attributes.get<int>("defense");
		xp = attributes.get<int>("experience_per_level");
		hpb = attributes.get<int>("health_point_bonus_per_level");


		try
		{
			dmb = attributes.get<int>("damage_bonus_per_level");
		}
		catch(const std::out_of_range&)
		{
			dmb = 0;
		}
		try
		{
			mdb = attributes.get<int>("magical-damage_bonus_per_level");
		}
		catch(const std::out_of_range&)
		{
			mdb = 0;
		}

		cdm = attributes.get<double>("cooldown_multiplier_per_level");
		dfb = attributes.get<int>("defense_bonus_per_level");
		lradius = attributes.get<int>("light-radius");
		try
		{
			lradbonus = attributes.get<int>("light_radius_bonus_per_level");
		}
		catch(const std::exception& e)
		{
			lradbonus = 1;
		}
		
		
	}
	catch(const std::out_of_range&)
	{
		throw(JSON::ParseException());
	}
	catch (const InputFormatException&)
	{
		infile.close();
		throw(JSON::ParseException());
	}
	catch (const std::invalid_argument&)
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

	return Hero(nm, hp, pdm, mdm, cd, df, xp, hpb, dmb, mdb, cdm, dfb, lradius, lradbonus);

}

void Hero::causeDamage(Monster* enemy)
{
	int tmpHP;
	if(enemy->getHealthPoints() < DMG.magical)
	{
		XP += enemy->getHealthPoints();
		return;
	}
	else
	{
		tmpHP = enemy->getHealthPoints() - DMG.magical;
		XP += DMG.magical;
		if(tmpHP + enemy->getDefense() > DMG.physical)
		{
			XP += DMG.physical;
		}
		else
		{
			XP += tmpHP;
		}
		
	}
	enemy->gotHit(*this);
	levelUp();
}
std::string Hero::showStats() const {

	return Name + ": HP:" + std::to_string(HP) + " DMG: " + std::to_string(DMG.physical)
		+ " EXP: " + std::to_string(XP) + " LVL: " + std::to_string(Lvl);
}
