#pragma once
#include <string>
#include <map>
#include <istream>
#include <exception>

#include <iostream>


/**
 * \class BaseUnit
 *
 * \brief BaseUnit class
 *
 */
class JSON
{
public:
	/**
	* \brief Parsing from an istream
	*
	* \param istream with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::string> parseFromIstream(std::istream& instream); //istream input


	/**
	* \brief Parsing from a file
	*
	* \param string JSON textfile's name
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::string> parseFromFile(std::string& fname); //filename input

	/**
	* \brief Parsing from a string
	*
	* \param string with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::string> parseFromString(std::string& data); //string input


	class ParseException : std::exception
	{
		public:

		ParseException()
		{
			
		}

	};
};
