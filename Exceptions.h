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
	NoFileException(const std::string& fname) : FileName {fname}
	{

	}
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
    /**
     * \brief Constructor of NoFileException (Cannot open file). Collect attributes, that could not be loaded
     *
     * \param const string filename and name, health points, damage and attackspeed
     */
	InvalidContentOfFileException(const std::string&fname, const std::string& name, int hp, int dmg, float as)
	{
		message = "In file <" + fname + "> the following unit parameters are not present or unreadable:\n";

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
			message += "dmg";
		}
		if (as == -1.0)
		{
			message += "attackspeed";
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
//Used to replace of the invalid_argument exception thrown by std::stoi(), or when string in units file was formatted incorrectly
class InterpretException : public std::exception
{
	std::string message; ///< Message that shown up upon error
public:
    /**
     * \brief Constructor of InterpretException. It checks if an attribute's value could not be interpreted properly
     *
     * \param const string filename and const string type
     */
	InterpretException(const std::string& fname, const std::string& type)
	{
		message = "In file <" + fname + "> the value associated with <" + type + "> parameter cannot be interpreted properly";
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
