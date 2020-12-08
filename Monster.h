#pragma once
#include<string>
#include "Damage.h"

/**
 * \class Monster
 *
 * \brief Monster class
 *
 */
class Monster
{
protected:
    const std::string Name; ///< Name of unit
    int maxHP; ///< Maximum Health ponits of unit
    int HP; ///< Health ponits of unit
    Damage DMG; ///< Combined physical and magical damage
    double CD; ///< Attackspeed of unit, seconds per attack
    int DF; ///< Defense

public:
    Monster(const std::string& nm, int hp, int pdmg, int mdmg, double cd, int df); ///< This constructor set the attributes of Monster
    Monster(const Monster&); ///< Copy constructor of Monster
    Monster() ///< Empty constructor of Monster
    {
    }
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
    * \brief Monster parsing from a file
    *
    * \param Monster JSON textfile (string)
    *
    * \return Monster object
    */
    static Monster parse(const std::string& /** [in] The (string)filename param*/);
    const int getHealthPoints() const { return HP; } ///< Const Getter of Unit's health points
    const int getPhysicalDMG() const { return DMG.physical; } ///< Const Getter of Unit's physical damage
    const int getMagicalDMG() const { return DMG.magical; } ///< Const Getter of Unit's magical damage
    const double getCD() const { return CD; } ///< Const Getter of Unit's attackspeed
    const std::string& getName() const { return Name; } ///< Const Getter of Unit's name
    const int getDefense() const {return DF;} ///< Const Getter of defense
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

    /**
     * \brief Less-than operator, used to differentiate monsters in a map
    */
    bool operator<(const Monster& other) const
    {
        return this < &other;
    }

};
