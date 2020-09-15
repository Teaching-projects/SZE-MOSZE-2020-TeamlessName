#include <iostream>
#include "BaseUnit.h"

//Everything happens here for now
int main(int argc, char *argv[])
{
    std::string errormsg = "Incorrect starting arguments.\nYou should start like this.:\nPROGRAM.EXE CHARACTER1 HP DMG CHARACTER2 HP DMG";
	if (argc != 7){
		std::cout << errormsg << std::endl;
		std::cin.get();
		return 1;
	}
	else
    {
        try
        {
			BaseUnit Unit1(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
			BaseUnit Unit2(argv[4], std::stoi(argv[5]), std::stoi(argv[6]));

			BaseUnit* attacker = &Unit1;
			BaseUnit* defender = &Unit2;

			//Fighting loop, might end up in a separate class later
			while (true)
			{
				std::cout << Unit1.showStats() << std::endl;
				std::cout << Unit2.showStats();

				std::cin.clear();
				std::cin.get();

				std::cout << attacker->getName() << " -> " << defender->getName() << std::endl;
				if (!defender->gotHit(attacker->getDMG()))
				{
					break;
				}
				

				BaseUnit* tmp = attacker;
				attacker = defender;
				defender = tmp;
			}
			std::cout << Unit1.showStats() << std::endl;
			std::cout << Unit2.showStats() << std::endl;
			std::cout << defender->getName() << " died. " << attacker->getName() << " wins.";
        }
        catch (const std::exception& e)
        {
            std::cout << errormsg << std::endl;
            std::cin.get();
            return 1;
        }
    }

	std::cin.get();
}
