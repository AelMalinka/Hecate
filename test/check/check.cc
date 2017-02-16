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
	struct stat_tag{}; using stat = Stat<stat_tag, Linear<2>>;
	struct skill_tag{}; using skill = Skill<skill_tag, Linear<1>, stat>;

	TEST(Check, Instantiate) {
		PercentType luck = 10;
		stat s = 20;
		stat o = 10;
		
		Check empty;
		Check with_luck(luck);
		Check modifiers({
			Modifier(-10),
			Modifier(s),
			Modifier(o, negative)
		});
		Check modifiers_luck(luck, {
			Modifier(-10),
			Modifier(s),
			Modifier(o, negative)
		});
	}

	TEST(Check, Roll) {
		Check empty;

		for(auto x = 0; x < 10000; x++) {
			auto res = empty();

			EXPECT_LT(res.Value(), 100 - ENTROPY_HECATE_DEFAULT_LUCK);
			EXPECT_GE(res.Value(), ENTROPY_HECATE_DEFAULT_LUCK - 100);
		}

		stat st = 10;
		skill sk(0, st);

		Check modifiers({
			Modifier(st),
			Modifier(sk),
			Modifier(-10)
		});

		for(auto x = 0; x < 10000; x++) {
			auto res = modifiers();

			EXPECT_LT(res.Value(), 100 - ENTROPY_HECATE_DEFAULT_LUCK);
			EXPECT_GE(res.Value(), ENTROPY_HECATE_DEFAULT_LUCK - 100);
		}
	}

	TEST(Check, CheckModifier) {
		stat s1 = 10;
		stat s2 = 15;
		skill first_skill(10, s1);
		skill second_skill(0, s2);

		Check first({
			Modifier(first_skill)
		});

		Check second({
			Modifier(second_skill),
			Modifier(first, negative)
		});

		auto res = second();

		EXPECT_EQ(res.size(), 2);

		auto iter = res.begin();
		iter++;
		EXPECT_LT(iter->modifier.Value(), 100 - ENTROPY_HECATE_DEFAULT_LUCK);
		EXPECT_GE(iter->modifier.Value(), ENTROPY_HECATE_DEFAULT_LUCK - 100);
	}

	TEST(Check, Callback) {
		Check first({
			Modifier(10)
		});

		bool ran = false;
		first.Add([&](auto) {
			ran = true;
		});

		EXPECT_FALSE(ran);
		first();
		EXPECT_TRUE(ran);
	}

	TEST(Check, onWrappers) {
		Check first;
		auto successes = 0;
		auto failures = 0;
		auto criticals = 0;

		first.Add(onSuccess([&successes](auto) {
			++successes;
		}));
		first.Add(onFailure([&failures](auto) {
			++failures;
		}));
		first.Add(onCritical([&criticals](auto) {
			++criticals;
		}));

		EXPECT_EQ(successes, 0);
		EXPECT_EQ(failures, 0);
		EXPECT_EQ(criticals, 0);

		for(auto x = 0; x < 10000; x++) {
			first();
		}

		EXPECT_GT(successes, 0);
		EXPECT_GT(failures, 0);
		EXPECT_GT(criticals, 0);
	}

	TEST(Result, isSuccess) {
		Check::Result first(-5, 10, 50, 5, {});
		Check::Result second(10, 10, 10, 5, {});

		EXPECT_FALSE(first.isSuccess());
		EXPECT_TRUE(second.isSuccess());
		EXPECT_FALSE(first);
		EXPECT_TRUE(second);
	}

	TEST(Result, isCritical) {
		Check::Result first(-5, 10, 96, 5, {});
		Check::Result second(-5, 10, 50, 5, {});
		Check::Result third(10, 10, 4, 5, {});
		Check::Result fourth(5, 10, 5, 5, {});

		EXPECT_TRUE(first.isCritical());
		EXPECT_FALSE(second.isCritical());
		EXPECT_TRUE(third.isCritical());
		EXPECT_FALSE(fourth.isCritical());
	}

	TEST(Result, Values) {
		Check::Result empty(10, 10, 10, 5, {});

		EXPECT_EQ(empty.Value(), 10);
		EXPECT_EQ(empty.Chance(), 10);
		EXPECT_EQ(empty.Luck(), 5);

		stat v = 10;
		ModifierList l;

		l.Add(Modifier(10));
		l.Add(Modifier(v));
		l.Add(Modifier(v, negative));

		Check::Result result(5, 5, 5, 5, l);

		EXPECT_EQ(result.Value(), 5);
		EXPECT_EQ(result.Chance(), 5);
		EXPECT_EQ(result.Luck(), 5);
	}

	TEST(Result, Luck) {
		Check::Result res1(10, 10, 10, 5, {});
		Check::Result res2(10, 10, 10, 10, {});

		EXPECT_EQ(res1.Luck(), 5);
		EXPECT_EQ(res2.Luck(), 10);
	}

	TEST(Result, Iterate) {
		Check::Result empty(10, 10, 10, 5, {});
		vector<Modifier> empty_list;

		for(auto &&i : empty) {
			empty_list.push_back(i.modifier);
		}

		EXPECT_EQ(empty_list.size(), 0);

		stat s = 10;
		skill k(5, s);
		Check::Result result(5, 5, 5, 5, ModifierList({
			Modifier(10),
			Modifier(s),
			Modifier(k),
			Modifier(k, negative)
		}));
		vector<Modifier> result_list;

		for(auto &i : result) {
			result_list.push_back(i.modifier);
		}

		EXPECT_EQ(result_list.size(), 4);
	}

	TEST(Result, Reference) {
		Modifier t(5);
		Check::Result res(10, 10, 10, 5, {t});

		EXPECT_EQ(res.begin()->modifier.Value(), 5);
		EXPECT_EQ(res.begin()->current, 5);

		t.Raw() = 10;
		EXPECT_EQ(res.begin()->modifier.Value(), 10);
		EXPECT_EQ(res.begin()->current, 5);
	}
}
