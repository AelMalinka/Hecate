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

	TEST(Check, Instantiate) {
		Percent luck = 10;
		stat s = 20;
		stat o = 10;
		
		Check empty;
		Check with_luck(luck);
		Check modifiers({
			Modifier(-10, "night"),
			Modifier(s, "stat"),
			Modifier(o, "other stat", negative)
		});
		Check modifiers_luck(luck, {
			Modifier(-10, "night"),
			Modifier(s, "stat"),
			Modifier(o, "other stat", negative)
		});
	}

	TEST(Check, Roll) {
		Check empty;

		for(auto x = 0; x < 10000; x++) {
			auto res = empty();

			EXPECT_LT(res.Value(), 100 - ENTROPY_HECATE_DEFAULT_LUCK);
			EXPECT_GE(res.Value(), -100 + ENTROPY_HECATE_DEFAULT_LUCK);
		}
	}

	TEST(Result, Values) {
		Check::Result empty(10, 5, {});

		EXPECT_EQ(empty.Value(), 10);

		stat v = 10;
		list<shared_ptr<Modifier>> l;

		l.push_back(make_shared<Modifier>(10, "value"));
		l.push_back(make_shared<Modifier>(v, "stat"));
		l.push_back(make_shared<Modifier>(v, "stat negative", negative));

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
			make_shared<Modifier>(10, "value"),
			make_shared<Modifier>(s, "stat"),
			make_shared<Modifier>(k, "skill"),
			make_shared<Modifier>(k, "negative skill", negative)
		});
		list<shared_ptr<Modifier>> result_list;

		for(auto &i : result) {
			result_list.push_back(i.modifier);
		}

		EXPECT_EQ(result_list.size(), 4);
	}

	TEST(Result, Reference) {
		auto t = make_shared<Modifier>(5, "value");
		Check::Result res(10, 5, {t});

		EXPECT_EQ(res.begin()->modifier->Value(), 5);
		EXPECT_EQ(res.begin()->current, 5);

		t->Raw() = 10;
		EXPECT_EQ(res.begin()->modifier->Value(), 10);
		EXPECT_EQ(res.begin()->current, 5);
	}
}
