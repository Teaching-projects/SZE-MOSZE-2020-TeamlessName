#include <gtest/gtest.h>
#include <string>
#include <map>
#include <fstream>
#include "../JSON.h"
#include "../Exceptions.h"
#include "../Monster.h"
#include "../Hero.h"

//testing with all data in the string
TEST(ParserTest, TestString)
{
	std::string input = "{\n\t\"name\"\t   :  \"isName\",\n\t\"hp\":150,\n\t\"dmg\"   \t\t :\t200,\n\t\"SomethingSpecial\" : 22.45\n}";
	std::map<std::string, std::variant<std::string, int, double>> expected;
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("name", "isName"));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("hp", 150));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("dmg", 200));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("SomethingSpecial", 22.45));
	std::map<std::string, std::variant<std::string, int, double>> testMap = JSON::parseFromString(input);

	ASSERT_EQ(expected, testMap);
}

//Testing with file name as string
TEST(ParserTest, TestFileName)
{
	std::string input = "unit_Test1.json";
	std::map<std::string, std::variant<std::string, int, double>> expected;
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("name", "Rick"));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("hp", 70));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("dmg", 30));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("mana", 14.25));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("SpecialAttribute", "NeedsAStringForIt"));
	std::map<std::string, std::variant<std::string, int, double>> testMap = JSON::parseFromFile(input);

	ASSERT_EQ(expected, testMap);
}

//Testing with fstream
TEST(ParserTest, TestIstream)
{
	std::string fname = "unit_Test1.json";
	std::map<std::string, std::variant<std::string, int, double>> expected;
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("name", "Rick"));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("hp", 70));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("dmg", 30));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("mana", 14.25));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("SpecialAttribute", "NeedsAStringForIt"));

	std::ifstream input(fname);

	std::map<std::string, std::variant<std::string, int, double>> testMap = JSON::parseFromIstream(input);

	input.close();

	ASSERT_EQ(expected, testMap);
}

//Missing colon
TEST(ParserTest, TestMissingColon)
{
									//No ':' between key and value
	std::string input = "{\n\t\"name\"\t     \"isName\",\n\t\"hp\":150,\n\t\"dmg\"   \t\t :\t200,\n\t\"SomethingSpecial\" : 22.45\n}";
	std::map<std::string, std::variant<std::string, int, double>> expected;
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("name", "isName"));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("hp", 150));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("dmg", 200));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("SomethingSpecial", 22.45));
	
	ASSERT_THROW(JSON::parseFromString(input), InputFormatException);
}

//Missing Quote mark
TEST(ParserTest, TestMissingQuoteMark)
{
														//no quotemark closing for hp
	std::string input = "{\n\t\"name\"\t:  \"isName\",\n\t\"hp:150,\n\t\"dmg\"   \t\t :\t200,\n\t\"SomethingSpecial\" : 22.45\n}";
	std::map<std::string, std::variant<std::string, int, double>> expected;
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("name", "isName"));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("hp", 150));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("dmg", 200));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("SomethingSpecial", 22.45));

	ASSERT_THROW(JSON::parseFromString(input), InputFormatException);
}
//Content in one line of the file
TEST(ParserTest, TestInOneLine)
{
	std::string input = "unit_Test2.json";
	std::map<std::string, std::variant<std::string, int, double>> expected;
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("name", "Blood Raven"));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("health_points", 113));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("damage", 8));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("attack_cooldown", 1.2));
	expected.insert(std::pair<std::string, std::variant<std::string, int, double>>("race", "undead"));

	std::map<std::string, std::variant<std::string, int, double>> testMap = JSON::parseFromFile(input);
	ASSERT_EQ(expected, testMap);
}
//Missing file
TEST(ParserTest, TestMissingFile)
{
	std::string fname = "../../Nonexistent_unit_Test1.json";
	ASSERT_THROW(JSON::parseFromFile(fname), NoFileException);
}

//********************Monster tests**************************

TEST(MonsterTest, TestAlive)
{
	Monster tMonster ("NAlive", -10, 25, 1.2);

	ASSERT_EQ(tMonster.isAlive(), false);
}

TEST(MonsterTest, TestgotHit)
{
	Monster Attacker ("Att", 10, 10, 1.0);
	Monster Defender ("Def", 1, 1, 0.2);

	Defender.gotHit(Attacker);

	ASSERT_EQ(Defender.getHealthPoints(), 0);
}

TEST(MonsterTest, TestcauseDamage)
{
	Monster Attacker ("Att", 1, 1, 0.2);
	Monster Defender ("Def", 10, 10, 1.0);

	Attacker.causeDamage(&Defender);

	ASSERT_EQ(Defender.getHealthPoints(), 9);
}

TEST(MonsterTest, TestfightTilDeath)
{
	Monster Attacker ("Att", 5, 1, 0.2);
	Monster Defender ("Def", 10, 2, 1.0);

	Attacker.fightTilDeath(Defender);

	ASSERT_EQ(Attacker.getHealthPoints(), 0);
}

TEST(MonsterTest, TestshowStats)
{
	Monster tMonster("MyName", 10, 100, 5.5);
	std::string output =  tMonster.getName() + ": HP:" + std::to_string(tMonster.getHealthPoints()) + " DMG: " + std::to_string(tMonster.getDMG());

	ASSERT_EQ(tMonster.showStats(), output);
}

TEST(MonsterTest, TestParse)
{
	Monster tMonster = Monster::parse("unit_Test3.json");
	ASSERT_TRUE(tMonster.showStats().find("lore") == std::string::npos);
}


//*******************Hero tests********************

TEST(HeroTest, TestZeroDamage)
{
	Hero tHero("Hero", 100, 0, 5.2, 1000, 10, 1, 0.4);
	Monster tMonster("MyName", 10, 100, 5.5);

	tHero.causeDamage(&tMonster);

	ASSERT_EQ(tHero.getXP(), 0);
}
//Hero.damage >> monster.hp
TEST(HeroTest, TestGreatDamage)
{
	Hero tHero("Hero", 100, 250, 5.2, 1000, 10, 1, 0.4);
	Monster tMonster("MyName", 10, 100, 5.5);

	tHero.causeDamage(&tMonster);

	ASSERT_EQ(tHero.getXP(), 10);
}

TEST(HeroTest, TestLevelUp)
{
	Hero tHero("Hero", 100, 250, 5.2, 2, 10, 1, 0.4);
	Monster tMonster("MyName", 10, 100, 5.5);

	tHero.causeDamage(&tMonster);

	ASSERT_EQ(tHero.getLevel(), 6);
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}