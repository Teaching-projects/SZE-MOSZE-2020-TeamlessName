#pragma once
#include <string>
#include <map>
#include <istream>
#include <exception>
#include <variant>
#include <list>

/**
 * \class JSON
 *
 * \brief JSON class
 *
 */

class JSON
{
public:

	class list
	{
		std::list<std::variant<std::string, int, double>> List;
	public:
		explicit list(const std::list<std::variant<std::string, int, double>>& ls) : List(ls)
		{

		}

		auto begin()
		{
			return List.begin();
		}

		auto end()
		{
			return List.end();
		}

		friend bool operator==(const list& lh, const list& rh)
		{
			return lh.List == rh.List;
		}
	};


private:
	std::map<std::string, std::variant<std::string, int, double, JSON::list>> content; ///< This stores key-value pairs picking from JSON files
public:

	JSON() ///< Default constructor of JSON
	{

	}


	explicit JSON(const std::map<std::string, std::variant<std::string, int, double, JSON::list>>& cont) : content(cont) ///< Another constructor of JSON that takes MAP content as parameter
	{

	}

	/**
	* \brief Parsing from an istream
	*
	* \param instream istream with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::variant<std::string, int, double, JSON::list>> parseFromIstream(std::istream& instream); //istream input


	/**
	* \brief Parsing from a file
	*
	* \param fname string: JSON textfile's name
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::variant<std::string, int, double, JSON::list>> parseFromFile(const std::string& fname); //filename input

	/**
	* \brief Parsing from a string
	*
	* \param data string with JSON-like content
	*
	* \return Map of key-value pairs
	*/
	static std::map<std::string, std::variant<std::string, int, double, JSON::list>> parseFromString(std::string& data); //string input

    /**
	* \brief Equal operator of JSON that takes content (contructor) as parameter
	*
	* \param content content
	*
	* \return JSON object
	*/
	JSON operator= (const std::map<std::string, std::variant<std::string, int, double, JSON::list>>& other)
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
