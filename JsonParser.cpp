#include "JsonParser.h"
#include "Exceptions.h"


std::map<std::string, std::string> JsonParser::parseJson(std::istream & instream)
{
	std::map<std::string, std::string> content;
	std::string line;

	while (std::getline(instream, line))
	{
		size_t position;
		size_t colonPos;
		position = line.find("\"");
		if (position == std::string::npos)	continue;
		colonPos = line.find(":");
		if (colonPos == std::string::npos) throw InputFormatException(":");

		//getting the key
		std::string key = line.substr(position + 1);
		position = key.find("\"");
		if(position > key.find(":")) throw InputFormatException("\"");
		if (position == std::string::npos)	 throw InputFormatException("\"");
		key = key.substr(0, position);

		//getting the value
		std::string value = line.substr(colonPos + 1);
		value = value.substr(value.find_first_not_of(" \t\v\""));
		position = value.find_last_not_of(" \t\v,\"");
		value = value.substr(0, position + 1);

		content.insert(std::pair<std::string, std::string>(key, value));

	}
	

	return content;
}
