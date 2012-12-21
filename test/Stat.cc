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
	struct StatTest : public TestWithParam<tuple<unsigned short, unsigned short, string>> {};

	TEST_P(StatTest, Add) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<> p1(get<2>(GetParam()), a), p2(get<2>(GetParam()), b);
		EXPECT_EQ((p1 + p2), (a + b));
	}

	TEST_P(StatTest, Subtract) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<> p1(get<2>(GetParam()), a), p2(get<2>(GetParam()), b);
		EXPECT_EQ((p1 - p2), (a - b));
	}

	TEST_P(StatTest, Multiply) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<> p1(get<2>(GetParam()), a), p2(get<2>(GetParam()), b);
		EXPECT_EQ((p1 * p2), (a * b));
	}

	TEST_P(StatTest, Divide) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<> p1(get<2>(GetParam()), a), p2(get<2>(GetParam()), b);
		EXPECT_EQ((p1 / p2), (a / b));
	}

	TEST_P(StatTest, Modulus) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<> p1(get<2>(GetParam()), a), p2(get<2>(GetParam()), b);
		EXPECT_EQ((p1 % p2), (a % b));
	}

	TEST_P(StatTest, Construct) {
		Stat<> a(get<2>(GetParam()));
		EXPECT_EQ(a, get<2>(GetParam()));
		Stat<> b(get<2>(GetParam()), get<0>(GetParam()));
		EXPECT_EQ(b, get<0>(GetParam()));
		EXPECT_EQ(b, get<2>(GetParam()));
	}

	TEST_P(StatTest, Assign) {
		Stat<> a(get<2>(GetParam()));
		a = get<0>(GetParam());
		EXPECT_EQ(a, get<0>(GetParam()));
		EXPECT_EQ(a, get<2>(GetParam()));
	}

	TEST_P(StatTest, Get) {
		Stat<> a(get<2>(GetParam()));
		a = get<0>(GetParam());
	}

	tuple<unsigned short, unsigned short, string> const values[] = {
		make_tuple(0, 1, "Strength"),
		make_tuple(100, 42, "Dexterity"),
		make_tuple(50, 25, "Constitution"),
		make_tuple(6, 7, "Wisdom"),
		make_tuple(42, -7, "Charisma"),
		make_tuple(-42, -6, "iq")
	};

	INSTANTIATE_TEST_CASE_P(Default, StatTest, ValuesIn(values));
}
