#include <iostream>
#include "JSON.h"
#include "Monster.h"
#include "Exceptions.h"
#include "Hero.h"


enum ReturnCodes {OK, Cmdline, NoFileExc, InterpretExc, ContentExc, FileFormatExc };


//Everything happens here for now
int main(int argc, char* argv[])
{
	if (argc != 3) {
		std::cout << "Incorrect starting arguments.\nYou should start like this:\nPROGRAM.EXE UNITFILE1 UNITFILE2" << std::endl;
		return Cmdline; //Error in cmdline args
	}

	try
	{

		Hero Unit1 = Hero::parse(argv[1]);
		Monster Unit2 = Monster::parse(argv[2]);

		Monster* attacker = &Unit1;
		Monster* defender = &Unit2;



			attacker->fightTilDeath(*defender);
		if (attacker->getHealthPoints() == 0)
		{
			std::cout << defender->getName() << " wins. Remaining HP:" << defender->getHealthPoints() << std::endl;
		}
		else if (defender->getHealthPoints() == 0)
		{
			std::cout << attacker->getName() << " wins. Remaining HP:" << attacker->getHealthPoints() << std::endl;
		}

	}
	catch (const NoFileException& noFile)
	{
		std::cout << "Unable to open file " << noFile.what() << std::endl;
        return NoFileExc; //No such file
    }
	catch (const InterpretException& interExc)
	{
		std::cout << interExc.what() << std::endl;
		return InterpretExc; //Invalid variable type
	}
	catch (const InvalidContentOfFileException& invContents)
	{
		std::cout << invContents.what() << std::endl;
		return ContentExc; //No name, hp, dmg, or as
	}
	catch (const FileFormatException& fileForm)
	{
		std::cout << fileForm.what() << std::endl;
		return FileFormatExc; //Invalid file formatting
	}

	return OK;
}
