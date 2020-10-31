#pragma once
#include <string>
#include <map>
#include <istream>
#include <exception>


/**
 * \class JSON
 *
 * \brief JSON class
 *
 */
class JSON
{
	std::map<std::string, std::string> content;
public:

	JSON()
	{

	}


	JSON(std::map<std::string, std::string> cont) : content(cont)
	{

	}

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
	static std::map<std::string, std::string> parseFromFile(const std::string& fname); //filename input

	/**
	* \brief Parsing from a string
	*
	* \param string with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::string> parseFromString(std::string& data); //string input


	JSON operator= (std::map<std::string, std::string>& other)
	{
		JSON json(other);
		return json;
	}


	template<typename T>
	T get(const std::string& key)
	{
		return content.at(key);

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
