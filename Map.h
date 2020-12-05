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
 std::vector<std::string> vmap; ///< This vector store the map (characters from the text file)
public:
        enum type {Free, Wall}; ///< Enum "list" that is used by get() getter to identificate Free space or Wall.
        /**
        * \brief Map empty constructor 
        */
        Map(){}
        /**
        * \brief Map constructor for load the map from a text file
        *
        * \param An existing (map) text file
        *
        */
        Map(std::string fname);
        /**
        * \brief Getter of the map element (vmap) that takes 2 coord points as parameter.
        *
        * \param Coord x as unsigned int, Coord y as unsigned int
        *
        * \return Index (integer) of (enum) type
        */
        Map::type get(unsigned int x, unsigned int y) const;


        /**
         * \brief Getter of the height of the map
         * \return height of the map
        */ 
        int getHeight() const {return vmap.size();}
        /**
         * \brief Getter of the width of the map
         * \return width of the map
        */ 
        int getWidth() const {return vmap[0].size();}
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
