#pragma once
#include <exception>
#include <string>

//Cannot open file
class NoFileException : public std::exception
{
	std::string FileName;

public:
	NoFileException(const std::string& fname) : FileName {fname}
	{

	}

	const std::string& getFileName() const { return FileName; }
};

//Missing or unindentified parameters
class InvalidContentOfFileException : public std::exception
{
	std::string message;

public:
	InvalidContentOfFileException(const std::string&fname, const std::string& name, int hp, int dmg)
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
	}

	const std::string& getMessage() const
	{
		return message;
	}
};
//Used to replace of the invalid_argument exception thrown by std::stoi()
class StoiException : public std::exception
{
	std::string message;
public:
	StoiException(const std::string& fname, const std::string& type)
	{
		message = "In file <" + fname + "> the value associated with <" + type + "> parameter cannot be converted to int";
	}

	const std::string& getMessage() const
	{
		return message;
	}
};