#include "JSON.h"
#include "Exceptions.h"

#include <sstream>
#include <fstream>

enum vartypes {string, integer, doubl}; ///< enumerate to seperate different datatypes of keys's values

MAP JSON::parseFromIstream(std::istream & instream)
{
	MAP content;
	std::string line;
	int vartype;

	while (std::getline(instream, line))
	{
		size_t position;
		size_t colonPos;
		if (line == "}" || line == "{") continue;
		while (line != "")
		{
			position = line.find("\"");
			colonPos = line.find(":");
			if (colonPos == std::string::npos) throw InputFormatException(":");

			//getting the key
			std::string key = line.substr(position + 1);
			position = key.find("\"");
			if (position > key.find(":")) throw InputFormatException("\"");
			if (position == std::string::npos)	 throw InputFormatException("\"");
			key = key.substr(0, position);

			//getting the value
			std::string value = line.substr(colonPos + 1);
			value = value.substr(value.find_first_not_of(" \t\v"));
			if (value[0] == '\"')
			{
				value = value.substr(1);
				value = value.substr(0, value.find_first_of("\""));
				vartype = string;
			}
			else
			{
				value = value.substr(0,value.find_first_of(","));
				if (value.find('.') != std::string::npos)
				{
					vartype = doubl;
				}
				else
				{
					vartype = integer;
				}
			}

			line = line.substr(line.find(value)+value.size());
			line = line.substr(line.find_first_of("\n,")+1);

			if (line.find_first_not_of(" ,\n\t\"") == std::string::npos || line[line.find_first_not_of(",\n\t\" ")] == '}')
			{
				line = "";
			}
			std::variant<std::string, int, double> mapvalue = value;
			if (vartype == integer)
			{
				mapvalue = std::stoi(value);
			}
			else if (vartype == doubl)
			{
				mapvalue = std::stod(value);
			}
			content.insert(std::pair<std::string, std::variant<std::string, int, double>>(key, mapvalue));
		}

	}

	return content;
}

MAP JSON::parseFromFile(const std::string & fname)
{
	std::ifstream infile(fname);
	if (!infile.is_open())
	{
		throw(NoFileException(fname)); //File does not exist
	}

	MAP content;
	content = parseFromIstream(infile);
	infile.close();

	return content;
}

MAP JSON::parseFromString(std::string & data)
{
	std::stringstream sstream;
	sstream << data;

	return parseFromIstream(sstream);
}
