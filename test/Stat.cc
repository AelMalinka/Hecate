/*	Michael Thomas (malinka) <AelMalinka@gmail.com>
	2012-12-14
*/

#include "Stat.hh"
#include "gtest/gtest.h"
#include <tuple>
#include <boost/concept_check.hpp>

using namespace std;
using namespace Entropy::Hecate;
using namespace testing;

namespace {
	struct StatTest : public TestWithParam<tuple<short, short, string>> {};

	TEST_P(StatTest, Equal) {
		EXPECT_EQ(
			Stat<>(get<2>(GetParam()), get<0>(GetParam())),
			get<0>(GetParam())
		);
	}

	TEST_P(StatTest, NotEqual) {
		EXPECT_NE(
			Stat<>(get<2>(GetParam()), get<0>(GetParam())),
			get<1>(GetParam())
		);
	}

	TEST_P(StatTest, Add) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Stat<> p1(get<2>(GetParam()), a), p2(get<2>(GetParam()), b);
		EXPECT_EQ((p1 + p2), (a + b));
	}

	TEST_P(StatTest, Subtract) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Stat<> p1(get<2>(GetParam()), a), p2(get<2>(GetParam()), b);
		EXPECT_EQ((p1 - p2), (a - b));
	}

	TEST_P(StatTest, Multiply) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Stat<> p1(get<2>(GetParam()), a), p2(get<2>(GetParam()), b);
		EXPECT_EQ((p1 * p2), (a * b));
	}

	TEST_P(StatTest, Divide) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Stat<> p1(get<2>(GetParam()), a), p2(get<2>(GetParam()), b);
		EXPECT_EQ((p1 / p2), (a / b));
	}

	TEST_P(StatTest, Modulus) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Stat<> p1(get<2>(GetParam()), a), p2(get<2>(GetParam()), b);
		EXPECT_EQ((p1 % p2), (a % b));
	}

	TEST_P(StatTest, Construct) {
		Stat<> a(get<2>(GetParam()));
		EXPECT_EQ(a, get<2>(GetParam()));
	}

	TEST_P(StatTest, Assign) {
		Stat<> a;
		a = get<2>(GetParam());
		EXPECT_EQ(a, get<2>(GetParam()));
	}

	tuple<short, short, string> const values[] = {
		make_tuple(0, 1, "Strength"),
		make_tuple(100, 42, "Dexterity"),
		make_tuple(50, 25, "Constitution"),
		make_tuple(6, 7, "Wisdom"),
		make_tuple(42, -7, "Charisma"),
		make_tuple(-42, -6, "iq")
	};

	INSTANTIATE_TEST_CASE_P(Default, StatTest, ValuesIn(values));
}
