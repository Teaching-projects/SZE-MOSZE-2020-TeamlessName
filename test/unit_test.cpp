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
	std::map<std::string, std::variant<std::string, int, double, JSON::list>> expected;
	std::variant<std::string, int, double, JSON::list> value;
	value = "isName";
	expected["name"] = value;
	value = 150;
	expected["hp"] = value;
	value = 200;
	expected["dmg"] = value;
	value = 22.45;
	expected["SomethingSpecial"] = value;
	std::map<std::string, std::variant<std::string, int, double, JSON::list>> testMap = JSON::parseFromString(input);

	ASSERT_EQ(expected, testMap);
}

//Testing with file name as string
TEST(ParserTest, TestFileName)
{
	std::string input = "unit_Test1.json";
	std::map<std::string, std::variant<std::string, int, double, JSON::list>> expected;
	std::variant<std::string, int, double, JSON::list> value;
	value = "Rick";
	expected["name"]= value;
	value = 70;
	expected["hp"]= value;
	value = 30;
	expected["dmg"]= value;
	value = 14.25;
	expected["mana"]= value;
	value ="NeedsAStringForIt";
	expected["SpecialAttribute"]= value;
	std::map<std::string, std::variant<std::string, int, double, JSON::list>> testMap = JSON::parseFromFile(input);

	ASSERT_EQ(expected, testMap);
}

//Testing with fstream
TEST(ParserTest, TestIstream)
{
	std::string fname = "unit_Test1.json";
	std::map<std::string, std::variant<std::string, int, double, JSON::list>> expected;
	std::variant<std::string, int, double, JSON::list> value;
	value = "Rick";
	expected["name"]= value;
	value = 70;
	expected["hp"]= value;
	value = 30;
	expected["dmg"]= value;
	value = 14.25;
	expected["mana"]= value;
	value = "NeedsAStringForIt";
	expected["SpecialAttribute"]= value;

	std::ifstream input(fname);

	std::map<std::string, std::variant<std::string, int, double, JSON::list>> testMap = JSON::parseFromIstream(input);

	input.close();

	ASSERT_EQ(expected, testMap);
}

//Missing colon
TEST(ParserTest, TestMissingColon)
{
									//No ':' between key and value
	std::string input = "{\n\t\"name\"\t     \"isName\",\n\t\"hp\":150,\n\t\"dmg\"   \t\t :\t200,\n\t\"SomethingSpecial\" : 22.45\n}";
	std::map<std::string, std::variant<std::string, int, double, JSON::list>> expected;
	std::variant<std::string, int, double, JSON::list> value;
	value = "isName";
	expected["name"]= value;
	value = 150;
	expected["hp"]= value;
	value = 200;
	expected["dmg"]= value;
	value = 22.45;
	expected["SomethingSpecial"]= value;
	
	ASSERT_THROW(JSON::parseFromString(input), InputFormatException);
}

//Missing Quote mark
TEST(ParserTest, TestMissingQuoteMark)
{
														//no quotemark closing for hp
	std::string input = "{\n\t\"name\"\t:  \"isName\",\n\t\"hp:150,\n\t\"dmg\"   \t\t :\t200,\n\t\"SomethingSpecial\" : 22.45\n}";
	std::map<std::string, std::variant<std::string, int, double, JSON::list>> expected;
	std::variant<std::string, int, double, JSON::list> value;
	value = "isName";
	expected["name"]= value;
	value = 150;
	expected["hp"]= value;
	value = 200;
	expected["dmg"]= value;
	value = 22.45;
	expected["SomethingSpecial"]= value;

	ASSERT_THROW(JSON::parseFromString(input), InputFormatException);
}
//Content in one line of the file
TEST(ParserTest, TestInOneLine)
{
	std::string input = "unit_Test2.json";
	std::map<std::string, std::variant<std::string, int, double, JSON::list>> expected;
	std::variant<std::string, int, double, JSON::list> value;
	value = "Blood Raven";
	expected["name"]= value;
	value = 113;
	expected["health_points"]= value;
	value = 8;
	expected["damage"]= value;
	value = 1.2;
	expected["attack_cooldown"]= value;
	value = 4;
	expected["defense"] = value;
	value = "undead";
	expected["race"]= value;

	std::map<std::string, std::variant<std::string, int, double, JSON::list>> testMap = JSON::parseFromFile(input);
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
	Monster tMonster ("NAlive", -10, 25, 0, 1.2, 0);

	ASSERT_EQ(tMonster.isAlive(), false);
}

TEST(MonsterTest, TestgotHit)
{
	Monster Attacker ("Att", 10, 10, 0, 1.0, 0);
	Monster Defender ("Def", 1, 1, 0, 0.2, 0);

	Defender.gotHit(Attacker);

	ASSERT_EQ(Defender.getHealthPoints(), 0);
}

TEST(MonsterTest, TestcauseDamage)
{
	Monster Attacker ("Att", 1, 1, 0, 0.2, 0);
	Monster Defender ("Def", 10, 10, 0, 1.0, 0);

	Attacker.causeDamage(&Defender);

	ASSERT_EQ(Defender.getHealthPoints(), 9);
}

TEST(MonsterTest, TestfightTilDeath)
{
	Monster Attacker ("Att", 5, 1, 0, 0.2, 0);
	Monster Defender ("Def", 10, 2, 0, 1.0, 0);

	Attacker.fightTilDeath(Defender);

	ASSERT_EQ(Attacker.getHealthPoints(), 0);
}

TEST(MonsterTest, TestshowStats)
{
	Monster tMonster("MyName", 10, 100, 0, 5.5, 0);
	std::string output =  tMonster.getName() + ": HP:" + std::to_string(tMonster.getHealthPoints()) + " DMG: " + std::to_string(tMonster.getPhysicalDMG());

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
	Hero tHero("Hero", 100, 0, 0, 5.2, 0, 1000, 10, 1, 0, 0.4, 0, 0, 0);
	Monster tMonster("MyName", 10, 100, 0, 5.5, 0);

	tHero.causeDamage(&tMonster);

	ASSERT_EQ(tHero.getXP(), 0);
}
//Hero.damage > monster.hp
TEST(HeroTest, TestGreatDamage)
{
	Hero tHero("Hero", 100, 250, 0, 5.2, 0, 1000, 10, 1, 0, 0.4, 0, 0, 0);
	Monster tMonster("MyName", 10, 100, 0, 5.5, 0);

	tHero.causeDamage(&tMonster);

	ASSERT_EQ(tHero.getXP(), 10);
}

TEST(HeroTest, TestLevelUp)
{
	Hero tHero("Hero", 100, 250, 0, 5.2, 0, 2, 10, 1, 0, 0.4, 0, 0, 0);
	Monster tMonster("MyName", 10, 100, 0, 5.5, 0);

	tHero.causeDamage(&tMonster);

	ASSERT_EQ(tHero.getLevel(), 6);
}

TEST(HeroTest, TestDefense)
{
	Hero tHero("Hero", 100, 5, 0, 1.0, 0, 10, 0, 0, 0, 1.0, 0, 0, 0);
	Monster tMonster("Monster", 10, 1, 1, 1.0, 4);
	tHero.causeDamage(&tMonster);

	ASSERT_EQ(tMonster.getHealthPoints(), 9);
}

TEST(HeroTest, TestMagicDamage)
{
	Hero tHero("Hero", 100, 0, 5, 1.0, 0, 10, 0, 0, 0, 1.0, 0, 0, 0);
	Monster tMonster("Monster", 10, 1, 1, 1.0, 100);
	tHero.causeDamage(&tMonster);

	ASSERT_EQ(tMonster.getHealthPoints(), 5);
}


int main(int argc, char** argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}