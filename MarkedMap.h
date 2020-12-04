#pragma once

#include <string>
#include <fstream>
#include <list>
#include <vector>
#include "Map.h"
/**
 * \class MarkedMap
 *
 * \brief MarkedMap class for loading and handling a map from a text file. Inherited from Map class
 *
 */
class MarkedMap : public Map
{
public:
    MarkedMap(){}; ///< Default (empty) constructor of MarkedMap class
    /**
    * \brief MarkedMap constructor for load the map from a text file
    *
    * \param An existing (map) text file
    *
    */
    MarkedMap(std::string fname);
    /**
    * \brief Search the Hero coordinate on the map
    *
    * \return A single pair of integer coordinate of the Hero
    */
    std::pair<int,int> getHeroPosition() const;
    /**
    * \brief Search and collect the monsters/mobs coordinates on the map
    *
    * \return A vector that stores pairs of monsters (integers) coordinates
    */
    std::vector<std::pair<int,int>> getMonsterPositions(char c) const;

};
