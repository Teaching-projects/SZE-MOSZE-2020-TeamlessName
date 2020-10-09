#include "BaseUnit.h"
#include "Exceptions.h"
#include "JsonParser.h"
#include <map>
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
	}


	if (nm == "" || hp == -1 || dm == -1)
	{
		throw(InvalidContentOfFileException(file_name, nm, hp, dm)); // missing contents 
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
