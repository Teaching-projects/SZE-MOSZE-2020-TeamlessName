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

	const char* what() const throw() override
	{
		return FileName.c_str();
	}
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

	const char* what() const throw() override
	{
		return message.c_str();
	}
};
//Used to replace of the invalid_argument exception thrown by std::stoi()
class InterpretException : public std::exception
{
	std::string message;
public:
	InterpretException(const std::string& fname, const std::string& type)
	{
		message = "In file <" + fname + "> the value associated with <" + type + "> parameter cannot be interpreted properly";
	}

	const char* what() const throw() override
	{
		return message.c_str();
	}
};
//Incorrect JSON style input
class InputFormatException : public std::exception
{
	std::string missing;

public:
	InputFormatException(std::string miss) : missing(miss)
	{

	}

	const char* what() const throw() override
	{
		return missing.c_str();
	}
};
//Incorrect file formatting
class FileFormatException : public std::exception
{
	std::string message;

public:
	FileFormatException(const std::string& fname, const std::string& missing)
	{
		message = "In file <" + fname + "> the formatting is incorrect. A <" + missing + "> was missing";
	}

	const char* what() const throw() override
	{
		return message.c_str();
	}
};