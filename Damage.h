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
    /**
     * \brief Addition operator.
     * 
     * \param other const Damage&
     * \return Sum of the two Damages in a struct. (Physical+Pyhsical, Magical+Magical)
     */
    Damage operator+(const Damage& other)
    {
        Damage nDamage (physical + other.physical, magical + other.magical);
        return nDamage;
    }

    /**
     * \brief Plus-equals operator
     * \param other const Damage&
     * \return Sum of the two Damages in a struct. (Physical+Pyhsical, Magical+Magical)
     */
    Damage& operator+=(const Damage& other)
    {
        physical += other.physical;
        magical += other.magical;

        return *this;
    }
    /**
     * \brief Multiply-equals operator
     * \param multipiler int
     * \return Product of the Damages in a struct. (Physical*multiplier, Magical*multiplier)
     */
    Damage& operator*=(int multiplier)
    {
        physical *= multiplier;
        magical *= multiplier;

        return *this;
    }

};