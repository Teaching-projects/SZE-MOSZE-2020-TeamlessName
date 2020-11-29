#pragma once
#include <string>
#include <map>
#include <vector>

/**
 * \class Map
 *
 * \brief Map class for loading and handling a map from a text file
 *
 */
class Map{
private:
 std::vector<std::string> vmap; ///< This data structure store the map
public:
        enum type {Free, Wall}; ///< Enum "list" that is used by get() to identificate Free space or Wall.
        /**
        * \brief Map constructor
        *
        * \param An existing (map) text file
        *
        */
        Map(std::string fname);
        /**
        * \brief Getter of the map element (vmap) that takes 2 coord points as parameter.
        *
        * \param Coord x, Coord y
        *
        * \return Index of (enum) type
        */
        Map::type get(unsigned int x, unsigned int y) const;
    /**
     * \class WrongIndexException
     *
     * \brief WrongIndexException class for handling pass wrong parameter (index) in get() getter
     *
     */
    class WrongIndexException : virtual public std::runtime_error {
        public:
        /**
        * \brief WrongIndexException constructor that inherited from std::runtime_error and throw error upon on wrong index in get() getter.
        *
        * \param Const string error message.
        *
        */
        WrongIndexException(const std::string &error) : std::runtime_error( error) {}
    };
};
