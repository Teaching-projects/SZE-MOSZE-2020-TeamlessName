#include <iostream>
#include "BaseUnit.h"

//Everything happens here for now
int main(int argc, char *argv[])
{
	if (argc < 7){
		std::cout << "Incorrect starting arguments.\nYou should start like this.:\nPROGRAM.EXE CHARACTER1 HP DMG CHARACTER2 HP DMG" << std::endl;
		std::cin.get();
		return 1;
	}
	/*BaseUnit Unit1("Kenobi", 100, 20);
	BaseUnit Unit2("Maul", 50, 30);*/
	BaseUnit Unit1(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
	BaseUnit Unit2(argv[4], std::stoi(argv[5]), std::stoi(argv[6]));

	BaseUnit* attacker = &Unit2;
	BaseUnit* defender = &Unit1;
	BaseUnit* tmp;

	//fighting loop, just for showcase, must be redesigned later for actual in-game use
	do
	{
		tmp = attacker;
		attacker = defender;
		defender = tmp;

		std::cout << Unit1.getName() << " HP:" << Unit1.getHP() << " DMG:" << Unit1.getDMG() << std::endl;
		std::cout << Unit2.getName() << " HP:" << Unit2.getHP() << " DMG:" << Unit2.getDMG() << std::endl << std::endl;

		std::cin.get();

		std::cout << attacker->getName() << " -> " << defender->getName() << std::endl;

	} while (defender->gotHit(attacker->getDMG()));

	

	std::cout << Unit1.getName() << " HP:" << Unit1.getHP() << " DMG:" << Unit1.getDMG() << std::endl;
	std::cout << Unit2.getName() << " HP:" << Unit2.getHP() << " DMG:" << Unit2.getDMG() << std::endl;

	std::cout << defender->getName() << " died, " << attacker->getName() << " wins";

	std::cin.get();
}