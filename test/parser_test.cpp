#include <gtest/gtest.h>
#include <string>
#include <map>
#include <fstream>
#include "../JSON.h"
#include "../Exceptions.h"

//testing with all data in the string
TEST(ParserTest, TestString)
{
	std::string input = "{\n\t\"name\"\t   :  \"isName\",\n\t\"hp\":150,\n\t\"dmg\"   \t\t :\t200,\n\t\"SomethingSpecial\" : 22.45\n}";
	std::map<std::string, std::string> expected;
	expected.insert(std::pair<std::string, std::string>("name", "isName"));
	expected.insert(std::pair<std::string, std::string>("hp", "150"));
	expected.insert(std::pair<std::string, std::string>("dmg", "200"));
	expected.insert(std::pair<std::string, std::string>("SomethingSpecial", "22.45"));
	std::map<std::string, std::string> testMap = JSON::parseFromString(input);

	ASSERT_EQ(expected, testMap);
}

//Testing with file name as string
TEST(ParserTest, TestFileName)
{
	std::string input = "unit_Test1.json";
	std::map<std::string, std::string> expected;
	expected.insert(std::pair<std::string, std::string>("name", "Rick"));
	expected.insert(std::pair<std::string, std::string>("hp", "70"));
	expected.insert(std::pair<std::string, std::string>("dmg", "30"));
	expected.insert(std::pair<std::string, std::string>("mana", "14.25"));
	expected.insert(std::pair<std::string, std::string>("SpecialAttribute", "NeedsAStringForIt"));
	std::map<std::string, std::string> testMap = JSON::parseFromFile(input);

	ASSERT_EQ(expected, testMap);
}

//Testing with fstream
TEST(ParserTest, TestIstream)
{
	std::string fname = "unit_Test1.json";
	std::map<std::string, std::string> expected;
	expected.insert(std::pair<std::string, std::string>("name", "Rick"));
	expected.insert(std::pair<std::string, std::string>("hp", "70"));
	expected.insert(std::pair<std::string, std::string>("dmg", "30"));
	expected.insert(std::pair<std::string, std::string>("mana", "14.25"));
	expected.insert(std::pair<std::string, std::string>("SpecialAttribute", "NeedsAStringForIt"));

	std::ifstream input(fname);

	std::map<std::string, std::string> testMap = JSON::parseFromIstream(input);

	input.close();

	ASSERT_EQ(expected, testMap);
}

//Missing colon
TEST(ParserTest, TestMissingColon)
{
									//No ':' between key and value
	std::string input = "{\n\t\"name\"\t     \"isName\",\n\t\"hp\":150,\n\t\"dmg\"   \t\t :\t200,\n\t\"SomethingSpecial\" : 22.45\n}";
	std::map<std::string, std::string> expected;
	expected.insert(std::pair<std::string, std::string>("name", "isName"));
	expected.insert(std::pair<std::string, std::string>("hp", "150"));
	expected.insert(std::pair<std::string, std::string>("dmg", "200"));
	expected.insert(std::pair<std::string, std::string>("SomethingSpecial", "22.45"));
	
	ASSERT_THROW(JSON::parseFromString(input), InputFormatException);
}

//Missing Quote mark
TEST(ParserTest, TestMissingQuoteMark)
{
														//no quotemark closing for hp
	std::string input = "{\n\t\"name\"\t:  \"isName\",\n\t\"hp:150,\n\t\"dmg\"   \t\t :\t200,\n\t\"SomethingSpecial\" : 22.45\n}";
	std::map<std::string, std::string> expected;
	expected.insert(std::pair<std::string, std::string>("name", "isName"));
	expected.insert(std::pair<std::string, std::string>("hp", "150"));
	expected.insert(std::pair<std::string, std::string>("dmg", "200"));
	expected.insert(std::pair<std::string, std::string>("SomethingSpecial", "22.45"));

	ASSERT_THROW(JSON::parseFromString(input), InputFormatException);
}

//Missing file
TEST(ParserTest, TestMissingFile)
{
	std::string fname = "../../Nonexistent_unit_Test1.json";
	ASSERT_THROW(JSON::parseFromFile(fname), NoFileException);
}



int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}