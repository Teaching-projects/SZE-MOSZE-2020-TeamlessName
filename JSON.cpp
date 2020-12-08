#include "JSON.h"
#include "Exceptions.h"

#include <sstream>
#include <fstream>


enum vartypes {string, integer, doubl, ls}; ///< enumerate to seperate different datatypes of keys's values

using MAP = std::map<std::string, std::variant<std::string, int, double, JSON::list>>;

MAP JSON::parseFromIstream(std::istream & instream)
{
	MAP content;
	std::string line;
	int vartype;
	std::list <std::variant<std::string, int, double >>  listvalues;

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
			size_t pos1 = value.find_first_not_of(" \t\v");
			if (value[0] == '\"')
			{
				value = value.substr(1);
				value = value.substr(0, value.find_first_of("\""));
				vartype = string;
				line = line.substr(line.find(value) + value.size());
				line = line.substr(line.find_first_of("\n,") + 1);
			}
			else if (pos1 != std::string::npos && value[pos1] == '[')
			{
				vartype = ls;
				value = value.substr(1);
				do
				{
					if (value == "")
					{
						std::getline(instream, value);
						continue;
					}

					pos1 = value.find_first_not_of(" \t\v");
					if (pos1 != std::string::npos && value[pos1] == '\"')
					{
						value = value.substr(pos1 + 1);
						pos1 = value.find("\"");
						listvalues.push_back(value.substr(0, pos1));
					}
					value = value.substr(pos1);
					pos1 = value.find_first_not_of(" \t\v\"");
					if (pos1 != std::string::npos && value[value.find_first_not_of(" \t\v\"")] == ']') break;
					std::getline(instream, value);
				} while (pos1 == std::string::npos || value[value.find_first_not_of(" \t\v")] != ']');
				line = "";
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
				line = line.substr(line.find(value) + value.size());
				line = line.substr(line.find_first_of("\n,") + 1);
			}

			if (line.find_first_not_of(" ,\n\t\"") == std::string::npos || line[line.find_first_not_of(",\n\t\" ")] == '}')
			{
				line = "";
			}
			std::variant<std::string, int, double, list> mapvalue;
			if (vartype == string)
			{
				mapvalue = value;
			}
			else if (vartype == integer)
			{
				mapvalue = std::stoi(value);
			}
			else if (vartype == doubl)
			{
				mapvalue = std::stod(value);
			}
			else if (vartype == ls)
			{
				mapvalue = list(listvalues);
			}
			content[key] = mapvalue;
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

MAP JSON::parseFromString(const std::string & data)
{
	std::stringstream sstream;
	sstream << data;

	return parseFromIstream(sstream);
}
