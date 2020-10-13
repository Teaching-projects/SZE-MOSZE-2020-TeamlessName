#include <iostream>
#include "BaseUnit.h"
#include "Exceptions.h"

#include "Player.h"
//Everything happens here for now
int main(int argc, char *argv[])
{
	if (argc != 3){
		std::cout << "Incorrect starting arguments.\nYou should start like this:\nPROGRAM.EXE UNITFILE1 UNITFILE2" << std::endl;
		return 1; //Error in cmdline args
	}
    
    try
    {

		Player Unit1 = Player::parsePlayer(argv[1]);
		BaseUnit Unit2 = Player::parsePlayer(argv[2]);

		BaseUnit* attacker = &Unit1;
		BaseUnit* defender = &Unit2;

		//Fighting loop, might end up in a separate class later
		while (true)
		{
			attacker->causeDamage(defender);
			if (defender->isDead())
			{
				break;
			}


			BaseUnit* tmp = attacker;
			attacker = defender;
			defender = tmp;
		}
		std::cout << "The Winner: " << attacker->showStats() << std::endl;
    }
	catch (const NoFileException& noFile )
	{
		std::cout << "Unable to open file " << noFile.what() << std::endl;
        return 2; //No such file
    }
	catch (const InterpretException& interExc)
	{
		std::cout << interExc.what() << std::endl;
		return 3; //invalid formatting or variable type
	}
	catch (const InvalidContentOfFileException& invContents)
	{
		std::cout << invContents.what() << std::endl;
		return 4; //No name, hp or dmg
	}

	return 0;
}
