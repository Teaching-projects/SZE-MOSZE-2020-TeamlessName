#pragma once
#include <exception>
#include <string>

/**
 * \class NoFileException
 *
 * \brief NoFileException class inherited from std::exception
 *
 * \author kalmar-adam
 *
 */
 //Cannot open file
class NoFileException : public std::exception
{
	std::string FileName; ///< Filename, which may cannot be load

public:
	/**
	* \brief Constructor of NoFileException (Cannot open file)
	*
	* \param const string filename
	*/
	explicit NoFileException(const std::string& fname) : FileName{ fname } {}

	/**
	* \brief Overrided function of NoFileException (std::exception)
	*
	* \return const string filename error message
	*/
	const char* what() const throw() override
	{
		return FileName.c_str();
	}
};


/**
 * \class InvalidContentOfFileException
 *
 * \brief InvalidContentOfFileException class inherited from std::exception
 *
 * \author kalmar-adam
 *
 */
 //Missing or unindentified parameters
class InvalidContentOfFileException : public std::exception
{
	std::string message; ///< Message that shown up upon error

public:

	InvalidContentOfFileException(const std::string & fname, const std::string & name, int hp, int dmg, double as) :
		message("In file <" + fname + "> the following unit parameters are not present or unreadable:\n")
	{
		/**
		 * \brief Constructor of NoFileException (Cannot open file). Collect attributes, that could not be loaded
		 *
		 * \param const string filename and name, health points, damage and attackspeed
		 */


		if (name == "")
		{
			message += "name\n";
		}
		if (hp == -1)
		{
			message += "hp\n";
		}
		if (dmg == -1)
		{
			message += "dmg\n";
		}
		if (as == -1.0)
		{
			message += "attackspeed\n";
		}
	}
	/**
	 * \brief Overrided function of InvalidContentOfFileException (std::exception)
	 *
	 * \return const string error message
	 */
	const char* what() const throw() override
	{
		return message.c_str();
	}
};

/**
* \class InterpretException
*
* \brief InterpretException class inherited from std::exception
*
* \author kalmar-adam
*
*/
//Used to replace of the invalid_argument exception thrown by std::stoi()
class InterpretException : public std::exception
{
	std::string message; ///< Message that shown up upon error
public:
	InterpretException(const std::string & fname, const std::string & type) :
		message("In file <" + fname + "> the value associated with <" + type + "> parameter cannot be interpreted properly")

		/**
		* \brief Constructor of InterpretException. It checks if an attribute's value could not be interpreted properly
		*
		* \param const string filename and const string type
		*/
	{
	}
	/**
	 * \brief Overrided function of InterpretException (std::exception)
	 *
	 * \return const string error message
	 */
	const char* what() const throw() override
	{
		return message.c_str();
	}
};

/**
 * \class InputFormatException
 *
 * \brief InputFormatException class inherited from std::exception
 */

//Incorrect JSON style input
class InputFormatException : public std::exception
{
	std::string missing; ///< Character that is not present in input, though required by syntax

public:
	InputFormatException(const std::string& miss) : missing(miss)
	{

		/**
		* \brief Constructor of InputFormatException. Missing key character in input
		*
		* \param const string missing character
		*/
	}

	/**
	 * \brief Overrided function of InputFormatException (std::exception)
	 *
	 * \return const string missingCharacter
	 */
	const char* what() const throw() override
	{
		return missing.c_str();
	}
};
/**
 * \class FileFormatException
 *
 * \brief FileFormatException class inherited from std::exception
 */
//Incorrect file formatting
class FileFormatException : public std::exception
{
	std::string message;///< Message that shown up upon error

public:
	FileFormatException(const std::string& fname, const std::string& missing):
		message("In file <" + fname + "> the formatting is incorrect. A <" + missing + "> was missing")
	{
		/**
		* \brief Constructor of FileFormatException. Missing key character in specified file input
		*
		* \param const string filename and const string missingCharacter
		*/
	}

	/**
	 * \brief Overrided function of FileFormatException (std::exception)
	 *
	 * \return const string error message
	 */
	const char* what() const throw() override
	{
		return message.c_str();
	}
};