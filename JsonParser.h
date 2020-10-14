#pragma once
#include <string>
#include <map>
#include <istream>

class JsonParser
{
public:

	static std::map<std::string, std::string> parseJson(std::istream& instream); //istream input
	static std::map<std::string, std::string> parseJson(std::string& fname); //filename input
	static std::map<std::string, std::string> parseString(std::string& data); //string input
};
