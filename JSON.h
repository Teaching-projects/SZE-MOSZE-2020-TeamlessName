#pragma once
#include <string>
#include <map>
#include <istream>
#include <exception>

#include <iostream>


/**
 * \class JSON
 *
 * \brief JSON class
 *
 */
class JSON
{
	std::map<std::string, std::string> scenario;


	JSON(std::map<std::string, std::string>& scen) : scenario(scen)
	{

	}



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


	template<typename T>
	T get(const std::string& getFile)
	{
		if(getFile == "hero")
		{
			return scenario["hero"];
		}
		else if (getFile == "monsters")
		{
			return scenario["monsters"];
		}

		return "";

	}
	


	class ParseException : std::exception
	{
		public:

		ParseException()
		{
			
		}

	};
};
