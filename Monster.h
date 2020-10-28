/**
 * \class Monster
 *
 * \brief Monster class
 *
 * \author kalmar-adam
 *
 */
#pragma once
#include<string>
// Base(Monster) of all unit types, specialized units may derive from this
class Monster
{
protected:
    const std::string Name; ///< Name of unit
    int maxHP; ///< Maximum Health ponits of unit
    int HP; ///< Health ponits of unit
    int DMG; ///< Damage of unit, the amount this unit hits with
    float AS; ///< Attackspeed of unit, seconds per attack


public:
    Monster(const std::string& nm, int hp, int dmg, float as); ///< This constructor set the attributes of unit
    /**
    * \brief Shows stats of Unit
    *
    * \return String
    */
    virtual std::string showStats() const;
    /**
    * \brief Deals damage to enemy unit
    *
    * \param Enemy Unit (pointer)
    */
    virtual void causeDamage(Monster*);
    /**
    * \brief Unit parsing from a file
    *
    * \param unit JSON textfile (string)
    *
    * \return Unit object
    */
    static Monster parse(const std::string& /** [in] The (string)filename param*/);
    const int getHealthPoints() const { return HP; } ///< Const Getter of Unit's health points
    const int getDMG() const { return DMG; } ///< Const Getter of Unit's damage
    const float getAS() const { return AS; } ///< Const Getter of Unit's attackspeed
    const std::string& getName() const { return Name; } ///< Const Getter of Unit's name
    /**
    * \brief Unit attacks other unit. This method do the full combat between the 2 units
    *
    * \param Enemy unit (pointer)
    */
    void fightTilDeath(Monster&);
    /**
    * \brief If unit is dead
    *
    * \return If unit health point is zero
    */
    bool isAlive() const;
    /**
    * \brief Unit getting hit by enemy unit
    *
    * \param Enemy unit
    */
    void gotHit(const Monster&);
};
