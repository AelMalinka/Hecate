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
		Check c = {
			make_modifier(10, "first"),
			make_modifier(5, "second", negative)
		};
	}

	TEST(Check, RollResult) {
		Check c = {
			make_modifier(10, "first"),
			make_modifier(5, "second", negative)
		};

		auto res = c();

		EXPECT_LT(res.Value(), 95);
		EXPECT_GT(res.Value(), -95);

		list<shared_ptr<Modifier>> l;
		for(auto &i : res) {
			l.push_back(i.modifier);
		}

		EXPECT_EQ(l.size(), 2);
	}

	TEST(Check, Roll) {
		Check c{};

		for(int x = 0; x < 1000; x++) {
			auto res = c();

			EXPECT_LT(res.Value(), 95);
			EXPECT_GT(res.Value(), -95);
		}
	}
}
