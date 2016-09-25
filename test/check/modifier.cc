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
	ENTROPY_HECATE_DEFINE_STAT(TestStat, 2);
	ENTROPY_HECATE_DEFINE_SKILL(TestSkill, 1, TestStat);

	TEST(Modifier, Instantiate) {
		TestStat stat = 10;
		TestSkill skill(10, stat);

		Modifier number(10, "number");
		Modifier negative_number(-10, "negative number");
		Modifier negative_number_positive(-10, "negative number again", negative);
		Modifier negative_number_multiplier(10, "negative number multiplier", negative);
		Modifier stat_modifier(stat, "stat");
		Modifier negative_stat(stat, "negative stat", negative);
		Modifier skill_modifier(skill, "skill");
		Modifier negative_skill(skill, "negative skill", negative);

		EXPECT_EQ(number.Value(), 10);
		EXPECT_EQ(negative_number.Value(), -10);
		EXPECT_EQ(negative_number.Raw(), -10);
		EXPECT_EQ(negative_number_positive.Value(), 10);
		EXPECT_EQ(negative_number_positive.Raw(), -10);
		EXPECT_EQ(negative_number_multiplier.Value(), -10);
		EXPECT_EQ(negative_number_multiplier.Raw(), 10);
		EXPECT_EQ(stat_modifier.Value(), 10);
		EXPECT_EQ(negative_stat.Value(), -10);
		EXPECT_EQ(skill_modifier.Value(), 20);
		EXPECT_EQ(negative_skill.Value(), -20);
	}

	TEST(Modifier, Reference) {
		PercentType perc = 10;
		PercentType mod = -5;
		TestStat stat = 15;
		TestSkill skill(5, stat);

		Modifier reference(perc, "reference");
		Modifier negative_reference(mod, "negative reference");
		Modifier stat_mod(stat, "stat");
		Modifier skill_mod(skill, "skill");
		Modifier number(10, "number");
		Modifier stat_rvalue(TestStat(20), "temporary stat");
		Modifier skill_rvalue(TestSkill(10, stat), "temprorary skill");

		EXPECT_EQ(reference.Value(), perc);
		EXPECT_EQ(negative_reference.Value(), mod);
		EXPECT_EQ(stat_mod.Value(), stat.Value());
		EXPECT_EQ(skill_mod.Value(), skill.Value());

		EXPECT_EQ(number.Value(), 10);
		EXPECT_EQ(stat_rvalue.Value(), 20);
		EXPECT_EQ(skill_rvalue.Value(), 25);

		perc++;
		mod++;
		stat.Raw()++;
		skill.Raw()++;

		EXPECT_EQ(reference.Value(), perc);
		EXPECT_EQ(negative_reference.Value(), mod);
		EXPECT_EQ(stat_mod.Value(), stat.Value());
		EXPECT_EQ(skill_mod.Value(), skill.Value());
	}

	TEST(Modifier, Copy) {
		PercentType perc = 10;
		TestStat stat = 15;
		TestSkill skill(5, stat);

		Modifier reference(perc, "reference");
		Modifier value(10, "value");
		Modifier stat_mod(stat, "stat");
		Modifier skill_mod(skill, "skill");

		{
			Modifier ref_copy(reference);
			Modifier value_copy(value);
			Modifier stat_copy(stat_mod);
			Modifier skill_copy(skill_mod);

			EXPECT_EQ(ref_copy.Value(), perc);
			EXPECT_EQ(value_copy.Value(), 10);
			EXPECT_EQ(stat_copy.Value(), stat.Value());
			EXPECT_EQ(skill_copy.Value(), skill.Value());
		}

		EXPECT_EQ(reference.Value(), perc);
		EXPECT_EQ(value.Value(), 10);
		EXPECT_EQ(stat_mod.Value(), stat.Value());
		EXPECT_EQ(skill_mod.Value(), skill.Value());
	}
}
