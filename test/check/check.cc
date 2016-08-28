/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Check.hh"

using namespace Entropy::Hecate;
using namespace testing;
using namespace std;

namespace {
	TEST(Check, Instantiation) {
		Check c({
			make_modifier(10, "first"),
			make_modifier(5, "second", negative)
		});
	}

	TEST(Check, RollResult) {
		Check c({
			make_modifier(10, "first"),
			make_modifier(5, "second", negative)
		});

		auto res = c();

		EXPECT_LT(res.Value(), 100 - res.Luck());
		EXPECT_GT(res.Value(), res.Luck() - 101);

		EXPECT_EQ(res.size(), 2);
	}

	TEST(Check, Roll) {
		Check c({});

		for(int x = 0; x < 1000; x++) {
			auto res = c();

			EXPECT_LT(res.Value(), 100 - res.Luck());
			EXPECT_GT(res.Value(), res.Luck() - 101);
		}
	}

	TEST(Check, TempModifiers) {
		Check c({
			make_modifier(10, "first"),
			make_modifier(5, "second", negative)
		});

		auto result = c();
		auto extra = c(make_modifier(20, "first extra"), make_modifier(15, "second extra", negative));

		EXPECT_EQ(result.size(), 2);
		EXPECT_EQ(extra.size(), 4);
	}

	TEST(Check, Luck) {
		unsigned short luck = 5;
		Check c(luck, {});

		auto result = c();

		luck = 10;
		auto diffluck = c();

		EXPECT_EQ(result.Luck(), 5);
		EXPECT_EQ(diffluck.Luck(), 10);
	}
}
