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
            std::stoi(argv[2]);
            std::stoi(argv[3]);
            std::stoi(argv[5]);
            std::stoi(argv[6]);
        }
        catch (std::exception e)
        {
            std::cout << errormsg << std::endl;
            std::cin.get();
            return 1;
        }
    }

	BaseUnit Unit1(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
	BaseUnit Unit2(argv[4], std::stoi(argv[5]), std::stoi(argv[6]));

	BaseUnit* attacker = &Unit1;
	BaseUnit* defender = &Unit2;
	BaseUnit* tmp;

	std::cout << Unit1.ShowStats() << std::endl;
	std::cout << Unit2.ShowStats();

	//Fighting loop, might end up in a separate class later
	while (true)
	{
		std::cin.clear();
		std::cin.get();
		std::cout << attacker->getName() << " -> " << defender->getName() << std::endl;
		if (!defender->gotHit(attacker->getDMG()))
		{
			break;
		}

		std::cout << Unit1.ShowStats() << std::endl;
		std::cout << Unit2.ShowStats();

		tmp = attacker;
		attacker = defender;
		defender = tmp;
	}
	std::cout << Unit1.ShowStats() << std::endl;
	std::cout << Unit2.ShowStats() << std::endl;
	std::cout << defender->getName() << " died. " << attacker->getName() << " wins.";

	std::cin.get();
}
