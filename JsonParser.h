#pragma once
#include <string>
#include <map>
#include <istream>


/**
 * \class BaseUnit
 *
 * \brief BaseUnit class
 *
 */
class JsonParser
{
public:
	/**
	* \brief Parsing from an istream
	*
	* \param istream with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::string> parseJson(std::istream& instream); //istream input


	/**
	* \brief Parsing from a file
	*
	* \param string JSON textfile's name
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::string> parseJson(std::string& fname); //filename input

	/**
	* \brief Parsing from a string
	*
	* \param string with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::string> parseString(std::string& data); //string input
};
