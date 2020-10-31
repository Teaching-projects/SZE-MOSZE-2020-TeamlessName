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
class JSON
{
	std::map<std::string, std::variant<std::string, int, double>> content;
public:

	JSON()
	{

	}


	JSON(std::map<std::string, std::variant<std::string, int, double>> cont) : content(cont)
	{

	}

	/**
	* \brief Parsing from an istream
	*
	* \param istream with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::variant<std::string, int, double>> parseFromIstream(std::istream& instream); //istream input


	/**
	* \brief Parsing from a file
	*
	* \param string JSON textfile's name
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::variant<std::string, int, double>> parseFromFile(const std::string& fname); //filename input

	/**
	* \brief Parsing from a string
	*
	* \param string with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::variant<std::string, int, double>> parseFromString(std::string& data); //string input


	JSON operator= (std::map<std::string, std::variant<std::string, int, double>> other)
	{
		JSON json(other);
		return json;
	}


	template<typename T>
	T get(const std::string& key)
	{
		T returner = std::get<T>(content.at(key));
		return returner;

	}


	int count(const std::string& key)
	{
		if (content.count(key)) return 1;

		return 0;
	}
	


	class ParseException : std::exception
	{
		public:

		ParseException()
		{
			
		}

	};
};
