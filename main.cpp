#include <iostream>
#include "BaseUnit.h"
#include "Exceptions.h"


//Everything happens here for now
int main(int argc, char *argv[])
{
	if (argc != 3){
		std::cout << "Incorrect starting arguments.\nYou should start like this:\nPROGRAM.EXE UNITFILE1 UNITFILE2" << std::endl;
		return 1; //Error in cmdline args
	}
    
    try
    {

		BaseUnit Unit1 = BaseUnit::parseUnit(argv[1]);
		BaseUnit Unit2 = BaseUnit::parseUnit(argv[2]);

		BaseUnit* attacker = &Unit1;
		BaseUnit* defender = &Unit2;

		//Fighting loop, might end up in a separate class later
		while (true)
		{
			defender->gotHit(*attacker);
			if (defender->isDead())
			{
				break;
			}
				

			BaseUnit* tmp = attacker;
			attacker = defender;
			defender = tmp;
		}
		std::cout << attacker->getName() << " wins. Remaining HP:" << attacker->getHP() << std::endl;
    }
	catch (const NoFileException& noFile )
	{
		std::cout << "Unable to open file " << noFile.what() << std::endl;
        return 2; //No such file
    }
	catch (const InterpretException& interExc)
	{
		std::cout << interExc.what() << std::endl;
		return 3; //Invalid variable type
	}
	catch (const InvalidContentOfFileException& invContents)
	{
		std::cout << invContents.what() << std::endl;
		return 4; //No name, hp or dmg
	}
	catch (const FileFormatException& fileForm)
	{
		std::cout << fileForm.what() << std::endl;
		return 5; //Invalid file formatting
	}

	return 0;
}
