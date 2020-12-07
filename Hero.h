#pragma once
#include "Monster.h"
/**
 * \class Hero
 *
 * \brief Hero class inherited from Monster
 *
 */
class Hero : public Monster
{
private:

	int XPgap; ///< The amount of xp that is needed for a level-up
	const int HPbonus; ///< The amount of Health Points Bonus of the Hero
	const int PDMGbonus; ///< The amount of Physical Damage Bonus of the Hero
	const int MDMGbonus; ///< The amount of Magical Damage Bonus of the Hero
	const double CDMultiplier; ///< The amount of Health Points Bonus of the Hero
	const int DFbonus;

	int XP; ///< The amount of XP that is not used yet for level-up
	int Lvl = 1; ///< The amount of level of Hero


	void levelUp(); ///< Decide if needed to level-up. If it is, modify stats.
	
public:
	Hero(const std::string& nm, int hp, int pdmg, int mdmg, double cd, int df, int xpgap, int hpbonus, int dmgbonus,
		int mdamagebonus ,double cdMulti, int dfbonus); ///< This constructor set the attributes of Hero

	Hero(const Hero&); ///< Copy constructor of Hero

	void operator=(const Hero&);

	/**
    * \brief Hero parsing from a file
    *
    * \param Hero JSON textfile (string)
    *
    * \return Hero object
    */
	static Hero parse(const std::string&);
	/**
    * \brief Deals damage to enemy unit
    *
    * \param Enemy Unit (pointer)
    */
	void causeDamage(Monster*) override;
	int getLevel() const { return Lvl; } ///< Getter of Hero's level
	int getXP() const { return XP; } ///< Getter of Hero's XP
	const int getDF() const { return DF; }
	const int getDFbonus() const { return DFbonus;}
	std::string showStats() const override; ///< Method to print Hero's attributes
	/**
    * \brief Getter of Hero's max Health Point
    *
    * \return Hero's max Health Point
    */
	int getMaxHealthPoints() const
	{
		return maxHP;
	}
	/**
    * \brief Getter of Hero's damage
    *
    * \return Hero's damage
    */
	/*int getDamage() const
	{
		return DMG;
	}*/
	/**
    * \brief Getter of Hero's Attack Cooldown
    *
    * \return Hero's Attack Cooldown
    */
	double getAttackCoolDown() const
	{
		return CD;
	}
};

