/**
 * \class BaseUnit
 *
 * \brief BaseUnit class
 *
 * \author kalmar-adam
 *
 */

#pragma once

#include<string>

// Base of all unit types, specialized units may derive from this
class BaseUnit
{
private:
	int HP; ///< Health ponits of unit (current or max, may change during developement, according to the task)
	const int DMG; ///< Damage of unit, the amount this unit hits with
	const std::string Name; ///< Name of unit
	float AS; ///< Attackspeed of unit, seconds per attack

public:
	BaseUnit(const std::string& nm, int hp, int dmg, float as); ///< This constructor set the attributes of unit

    /**
     * \brief Unit attacks other unit. This method do the full combat between the 2 units
     *
     * \param Enemy unit (pointer)
     */
	void Attack(BaseUnit&);

	/**
     * \brief Unit parsing from a file
     *
     * \param unit JSON textfile (string)
     *
     * \return Unit object
     */
	static BaseUnit parseUnit(const std::string& /** [in] The (string)filename param*/);

	const int getHP() const { return HP; } ///< Const Getter of Unit's health points
	const int getDMG() const { return DMG; } ///< Const Getter of Unit's damage
	const float getAS() const { return AS; } ///< Const Getter of Unit's attackspeed
	const std::string& getName() const { return Name; } ///< Const Getter of Unit's name
    /**
     * \brief If unit is dead
     *
     * \return If unit health point is zero
     */
	bool isDead() const;
private:
    /**
     * \brief Unit getting hit by enemy unit
     *
     * \param Enemy unit
     */
    void gotHit(const BaseUnit&);

};
