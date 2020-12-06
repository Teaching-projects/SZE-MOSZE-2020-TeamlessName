#pragma once


/**
 * \struct Damage
 * 
 * \brief Contains the physical and the magical aspect of damage
 * 
 */
struct Damage
{
    int physical; ///< Physical part of damage
    int magical; ///< Magical part of damage


    /**
     * \brief Damage constructor
     * 
     * \param phys -> physical
     * \param mag -> magical
     */
    Damage(int phys, int mag) : physical(phys), magical(mag)
    {

    }
    Damage() ///< Default Empty constructor of Damage
    {

    }

    Damage operator+(const Damage& other)
    {
        Damage nDamage (physical + other.physical, magical + other.magical);
        return nDamage;
    }

    Damage& operator+=(const Damage& other)
    {
        physical += other.physical;
        magical += other.magical;

        return *this;
    }

    Damage& operator*=(int multiplier)
    {
        physical *= multiplier;
        magical *= multiplier;

        return *this;
    }

};