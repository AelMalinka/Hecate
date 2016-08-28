/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development->com>'
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Modifier.hh"
#include "Stat.hh"
#include "Skill.hh"

#include <iostream>

using namespace Entropy::Hecate;
using namespace testing;
using namespace std;

namespace {
	ENTROPY_HECATE_DEFINE_STAT(TestStat);
	ENTROPY_HECATE_DEFINE_SKILL(TestSkill, TestStat);

	TEST(Modifier, Instantiation) {
		TestStat v = 10;
		auto number = make_modifier(10, "This is a static modifier");
		auto skill = make_modifier(v, "This is a reference modifier");
		auto negative_number = make_modifier(10, "this is a static negative modifier", negative);
		auto negative_skill = make_modifier(v, "this is a reference negative modifier", negative);
	}

	TEST(Modifier, Copy) {
		TestStat v = 10;
		auto first = make_modifier(10, "modifier");
		auto second = first;
		auto skill_first = make_modifier(v, "stat modifier");
		auto skill_second = skill_first;

		EXPECT_EQ(first->Value(), second->Value());
		EXPECT_EQ(first->Value(), 10);
		EXPECT_EQ(second->Value(), 10);

		EXPECT_EQ(skill_first->Value(), skill_second->Value());
		EXPECT_EQ(skill_first->Value(), 10);
		EXPECT_EQ(skill_second->Value(), 10);

		v.Value() = 15;

		EXPECT_EQ(skill_first->Value(), skill_second->Value());
		EXPECT_EQ(skill_first->Value(), 15);
		EXPECT_EQ(skill_second->Value(), 15);

		// 2016-08-27 AMR NOTE: this changes all copies
		second->setValue(15);
		EXPECT_EQ(first->Value(), second->Value());

		auto third = first->Copy();
		EXPECT_EQ(first->Value(), third->Value());

		third->setValue(10);
		EXPECT_EQ(third->Value(), 10);
		EXPECT_NE(third->Value(), first->Value());
	}

	TEST(Modifier, Negative) {
		TestStat v = 10;
		auto number = make_modifier(10, "number");
		auto skill = make_modifier(v, "skill");
		auto negative_number = make_modifier(10, "negative number", negative);
		auto negative_skill = make_modifier(v, "negative skill", negative);

		EXPECT_FALSE(number->Negative());
		EXPECT_FALSE(skill->Negative());
		EXPECT_TRUE(negative_number->Negative());
		EXPECT_TRUE(negative_skill->Negative());

		EXPECT_EQ(number->Value(), negative_number->Value());
		EXPECT_EQ(skill->Value(), negative_skill->Value());
	}

	TEST(Modifier, Static) {
		auto modifier = make_modifier(10, "This is a static modifier");

		EXPECT_EQ(modifier->Value(), 10);
		EXPECT_EQ(modifier->Reason(), "This is a static modifier"s);
	}

	TEST(Modifier, Reference) {
		TestStat v = 10;
		auto modifier = make_modifier(v, "This is a reference modifier");

		EXPECT_EQ(modifier->Value(), 10);
		EXPECT_EQ(modifier->Value(), v.Value());

		v.Value() = 15;

		EXPECT_EQ(modifier->Value(), 15);
		EXPECT_EQ(modifier->Value(), v.Value());
	}

	TEST(Modifier, Skill) {
		TestStat v = 10;
		TestSkill k(15, v);

		auto modifier = make_modifier(k, "skill");

		EXPECT_EQ(modifier->Value(), 25);

		k.setValue(5);
		EXPECT_EQ(modifier->Value(), 15);

		v.Value() = 5;
		EXPECT_EQ(modifier->Value(), 10);
	}

	TEST(Modifier, Output) {
		TestStat stat = 10;

		auto test = make_modifier(stat, "TestStat");
		auto night = make_modifier(10, "Night", negative);
		auto negtest = make_modifier(stat, "Opposing TestStat", negative);

		stringstream out;

		out << test << endl << night << endl << negtest << endl;

		stat = 15;

		out << test << endl << night << endl << negtest << endl;

		EXPECT_EQ(out.str(), "TestStat: 10\nNight: -10\nOpposing TestStat: -10\nTestStat: 15\nNight: -10\nOpposing TestStat: -15\n");
	}
}
