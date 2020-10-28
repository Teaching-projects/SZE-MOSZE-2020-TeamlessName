#include "JSON.h"
#include "Exceptions.h"

#include <sstream>
#include <fstream>



std::map<std::string, std::string> JSON::parseFromIstream(std::istream & instream)
{
	std::map<std::string, std::string> content;
	std::string line;

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
			}
			else
			{
				value = value.substr(0,value.find_first_of(","));
			}

			line = line.substr(line.find(value)+value.size());
			line = line.substr(line.find_first_of("\n,")+1);

			if (line.find_first_not_of(" ,\n\t\"") == std::string::npos || line[line.find_first_not_of(",\n\t\" ")] == '}')
			{
				line = "";
			}
			content.insert(std::pair<std::string, std::string>(key, value));
		}

	}
	
	return content;
}

std::map<std::string, std::string> JSON::parseFromFile(std::string & fname)
{
	std::ifstream infile(fname);
	if (!infile.is_open())
	{
		throw(NoFileException(fname)); //File does not exist
	}

	std::map<std::string, std::string> content;
	content = parseFromIstream(infile);
	infile.close();

	return content;
}

std::map<std::string, std::string> JSON::parseFromString(std::string & data)
{
	std::stringstream sstream;
	sstream << data;

	return parseFromIstream(sstream);
}
