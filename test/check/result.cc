/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Check.hh"
#include "Stat.hh"
#include "Skill.hh"

using namespace Entropy::Hecate;
using namespace testing;
using namespace std;

namespace {
	ENTROPY_HECATE_DEFINE_STAT(stat);
	ENTROPY_HECATE_DEFINE_SKILL(skill, stat);

	TEST(Result, Values) {
		Check::Result empty(10, 5, {});

		EXPECT_EQ(empty.Value(), 10);

		stat v = 10;
		list<shared_ptr<Modifier>> l;

		l.push_back(make_modifier(10, "value"));
		l.push_back(make_modifier(v, "stat"));
		l.push_back(make_modifier(v, "stat negative", negative));

		Check::Result result(5, 5, l);

		EXPECT_EQ(result.Value(), 5);
	}

	TEST(Result, Luck) {
		Check::Result res1(10, 5, {});
		Check::Result res2(10, 10, {});

		EXPECT_EQ(res1.Luck(), 5);
		EXPECT_EQ(res2.Luck(), 10);
	}

	TEST(Result, Iterate) {
		Check::Result empty(10, 5, {});
		list<shared_ptr<Modifier>> empty_list;

		for(auto &i : empty) {
			empty_list.push_back(i.modifier);
		}

		EXPECT_EQ(empty_list.size(), 0);

		stat s = 10;
		skill k(5, s);
		Check::Result result(5, 5, {
			make_modifier(10, "value"),
			make_modifier(s, "stat"),
			make_modifier(k, "skill"),
			make_modifier(k, "negative skill", negative)
		});
		list<shared_ptr<Modifier>> result_list;

		for(auto &i : result) {
			result_list.push_back(i.modifier);
		}

		EXPECT_EQ(result_list.size(), 4);
	}

	TEST(Result, Reference) {
		auto t = make_modifier(5, "value");
		Check::Result res(10, 5, {t});

		EXPECT_EQ(res.begin()->modifier->Value(), 5);
		EXPECT_EQ(res.begin()->current, 5);

		t->setValue(10);
		EXPECT_EQ(res.begin()->modifier->Value(), 10);
		EXPECT_EQ(res.begin()->current, 5);
	}
}
