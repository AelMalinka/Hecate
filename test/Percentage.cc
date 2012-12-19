/*	Michael Thomas (malinka) <AelMalinka@gmail.com>
	2012-12-14
*/

#include "Percentage.hh"
#include "gtest/gtest.h"
#include <tuple>
#include <boost/concept_check.hpp>

using namespace std;
using namespace Entropy::Hecate;
using namespace testing;

namespace {
	struct PercentageTest : public TestWithParam<tuple<unsigned short, unsigned short>> {};
	struct ShortTest : public TestWithParam<tuple<unsigned short, unsigned short>> {};

	TEST_P(PercentageTest, Equal) {
		EXPECT_EQ(
			Percentage(get<0>(GetParam())),
			get<0>(GetParam())
		);
	}

	TEST_P(PercentageTest, NotEqual) {
		EXPECT_NE(
			Percentage(get<0>(GetParam())),
			get<1>(GetParam())
		);
	}

	TEST_P(ShortTest, Equal) {
		EXPECT_EQ(
			Percentage(get<0>(GetParam())),
			get<0>(GetParam())
		);
	}

	TEST_P(ShortTest, NotEqual) {
		EXPECT_NE(
			Percentage(get<0>(GetParam())),
			get<1>(GetParam())
		);
	}

	TEST_P(PercentageTest, Add) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage p1(a), p2(b);
		EXPECT_EQ((p1 + p2), (a + b));
	}

	TEST_P(PercentageTest, Subtract) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage p1(a), p2(b);
		EXPECT_EQ((p1 - p2), (a - b));
	}

	TEST_P(PercentageTest, Multiply) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage p1(a), p2(b);
		EXPECT_EQ((p1 * p2), (a * b));
	}

	TEST_P(PercentageTest, Divide) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage p1(a), p2(b);
		EXPECT_EQ((p1 / p2), (a / b));
	}

	TEST_P(PercentageTest, Modulus) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage p1(a), p2(b);
		EXPECT_EQ((p1 % p2), (a % b));
	}

	TEST_P(ShortTest, Add) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage p1(a);
		EXPECT_EQ((p1 + b), (a + b));
	}

	TEST_P(ShortTest, Subtract) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage p1(a);
		EXPECT_EQ((p1 - b), (a - b));
	}

	TEST_P(ShortTest, Multiply) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage p1(a);
		EXPECT_EQ((p1 * b), (a * b));
	}

	TEST_P(ShortTest, Divide) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage p1(a);
		EXPECT_EQ((p1 / b), (a / b));
	}

	TEST_P(ShortTest, Modulus) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage p1(a);
		EXPECT_EQ((p1 % b), (a % b));
	}

	/* 2012-12-15 AMR NOTE: rules for tuples below for tests to work
		second number can't be zero (Division & Modulus)
		both numbers can't be the same (NotEqual)
	*/
	tuple<unsigned short, unsigned short> const values[] = {
//		make_tuple(0, 0),	//2012-12-15 AMR TODO: division by zero
//		make_tuple(1, 0),	//2012-12-15 AMR TODO: division by zero
		make_tuple(0, 1),
		make_tuple(100, 42),
		make_tuple(50, 25),
		make_tuple(6, 7),
		make_tuple(42, -7),
		make_tuple(-42, -6)
	};

	INSTANTIATE_TEST_CASE_P(Default, PercentageTest, ValuesIn(values));
	INSTANTIATE_TEST_CASE_P(Default, ShortTest, ValuesIn(values));
}
