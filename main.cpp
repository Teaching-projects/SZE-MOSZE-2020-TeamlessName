#include <iostream>
#include "BaseUnit.h"

#include <fstream>

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
	catch (const std::string& file_name )
	{
		std::cout << "Unable to open file " << file_name<< std::endl;
        return 2; //No such file
    }
	catch (const std::exception& e)
	{
		std::cout << "Invalid file syntax" << std::endl;
		return 3; //stoi exception
	}
	catch (int)
	{
		std::cout << "Invalid file contents" << std::endl;
		return 4; //No name, hp or dmg
	}
	
	return 0;
}
