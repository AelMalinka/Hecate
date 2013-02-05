/*	Copyright 2012 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "StatPrototype.hh"
#include "gtest/gtest.h"

using namespace std;
using namespace Entropy::Hecate;
using namespace ::testing;

namespace {
	struct StatPrototypeTest : public TestWithParam<string> {
		protected:
			virtual void TearDown() {
				StatPrototype::clear();
			}
	};

	TEST_P(StatPrototypeTest, Use) {
		StatPrototype a(StatPrototype::create(GetParam()));
		StatPrototype b(GetParam());
		EXPECT_EQ(a, b);
	}

	TEST_P(StatPrototypeTest, UseBad) {
		try {
			StatPrototype a(GetParam());
			ADD_FAILURE();
		} catch(InvalidStatPrototype) {
			SUCCEED();
		}
	}

	TEST_P(StatPrototypeTest, Cast) {
		StatPrototype a = StatPrototype::create(GetParam());
		string b = (string)(a);
		EXPECT_EQ(a.Value(), b);
	}

	const string values[] = {
		"Strength",
		"Dexterity",
		"Constitution",
		"st",
		"ST",
		"who the fuckits?"
	};

	INSTANTIATE_TEST_CASE_P(Default, StatPrototypeTest, ValuesIn(values));
}
