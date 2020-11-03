#pragma once
#include <string>
#include <map>
#include <istream>
#include <exception>
#include <variant>

/**
 * \class JSON
 *
 * \brief JSON class
 *
 */
using MAP = std::map<std::string, std::variant<std::string, int, double>>;

class JSON
{
	MAP content; ///< This stores key-value pairs picking from JSON files
public:

	JSON() ///< Default constructor of JSON
	{

	}


	JSON(MAP cont) : content(cont) ///< Another constructor of JSON that takes MAP content as parameter
	{

	}

	/**
	* \brief Parsing from an istream
	*
	* \param istream with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static MAP parseFromIstream(std::istream& instream); //istream input


	/**
	* \brief Parsing from a file
	*
	* \param string JSON textfile's name
	*
	* \return Map of key-value pairs
	*/
	static MAP parseFromFile(const std::string& fname); //filename input

	/**
	* \brief Parsing from a string
	*
	* \param string with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static MAP parseFromString(std::string& data); //string input

    /**
	* \brief Equal operator of JSON that takes content (contructor) as parameter
	*
	* \param MAP content
	*
	* \return JSON object
	*/
	JSON operator= (MAP other)
	{
		JSON json(other);
		return json;
	}


	template<typename T> ///< Template/Type definiton to help mining key-value pairs

	/**
	* \brief Get key-pair
	*
	* \param string key of key-value pair
	*
	* \return Defined type T (key-value pair)
	*/
	T get(const std::string& key)
	{
		T returner = std::get<T>(content.at(key));
		return returner;

	}

    /**
	* \brief Check if exist the key or not
	*
	* \param string key
	*
	* \return integer 1 or 0, depending on existing the key or not
	*/
	int count(const std::string& key)
	{
		if (content.count(key)) return 1;

		return 0;
	}


    /**
     * \class ParseException
     *
     * \brief ParseException class inherited from std::exception
     *
     */
	class ParseException : std::exception
	{
		public:

		ParseException() ///< Default constructor of ParseException
		{

		}

	};
};
