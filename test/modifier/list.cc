/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "ModifierList.hh"
#include "Stat.hh"
#include "Skill.hh"

using namespace Entropy::Hecate;
using namespace testing;
using namespace std;

namespace {
	struct TestStat_tag{}; using TestStat = Stat<TestStat_tag, Linear<2>>;
	struct TestSkill_tag{}; using TestSkill = Skill<TestSkill_tag, Linear<1>, TestStat>;

	ModifierType mytype1;
	ModifierType mytype2(true);

	TEST(ModifierList, Create) {
		TestStat stat(10);
		TestSkill skill(10, stat);

		ModifierList a;
		EXPECT_EQ(a.size(), 0ul);
		EXPECT_EQ(a.Value(), 0);

		ModifierList b({
			Modifier(10),
			Modifier(stat),
			Modifier(skill)
		});
		EXPECT_EQ(b.size(), 1ul);
		EXPECT_EQ(b.Value(), 40);

		ModifierList c({
			Modifier(10, mytype1),
			Modifier(skill, mytype1),
			Modifier(10, mytype2),
			Modifier(10, mytype2),
			Modifier(10, mytype1)
		});
		EXPECT_EQ(c.size(), 2ul);
		EXPECT_EQ(c.Value(), 40);
	}

	TEST(ModifierList, Add) {
		TestStat stat(10);
		TestSkill skill(10, stat);

		ModifierList a;
		EXPECT_EQ(a.size(), 0ul);
		EXPECT_EQ(a.Value(), 0);

		a.Add(Modifier(10));
		EXPECT_EQ(a.size(), 1ul);
		EXPECT_EQ(a.Value(), 10);

		a.Add(Modifier(10));
		EXPECT_EQ(a.size(), 1ul);
		EXPECT_EQ(a.Value(), 20);

		a.Add(Modifier(10, mytype1));
		EXPECT_EQ(a.size(), 2ul);
		EXPECT_EQ(a.Value(), 30);

		a.Add(Modifier(10, mytype1));
		EXPECT_EQ(a.size(), 2ul);
		EXPECT_EQ(a.Value(), 30);

		a.Add(Modifier(10, mytype2));
		EXPECT_EQ(a.size(), 3ul);
		EXPECT_EQ(a.Value(), 40);

		a.Add(Modifier(10, mytype2));
		EXPECT_EQ(a.size(), 3ul);
		EXPECT_EQ(a.Value(), 50);
	}
}
