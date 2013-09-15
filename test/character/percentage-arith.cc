/*	Copyright 2012 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "Percentage.hh"
#include "gtest/gtest.h"
#include <tuple>

using namespace std;
using namespace Entropy::Hecate;
using namespace testing;

namespace {
	struct PercentageTest : public TestWithParam<unsigned short> {};
	struct PercentageDefualtTest : public TestWithParam<tuple<unsigned short, unsigned short>> {};
	struct PercentageUnsignedShortTest : public TestWithParam<tuple<unsigned short, unsigned short>> {};
	struct PercentageShortTest : public TestWithParam<tuple<short, short>> {};

	TEST_P(PercentageTest, Equal) {
		Percentage<> a;
		Percentage<> b(GetParam());
		a = GetParam();
		EXPECT_EQ(a, b);
	}

	TEST_P(PercentageTest, NotEqual) {
		Percentage<> a(GetParam());
		Percentage<> b(GetParam() + 1);
		EXPECT_NE(a, b);
	}

	TEST_P(PercentageDefualtTest, Equal) {
		EXPECT_EQ(
			Percentage<>(get<0>(GetParam())),
			get<0>(GetParam())
		);
	}

	TEST_P(PercentageDefualtTest, NotEqual) {
		EXPECT_NE(
			Percentage<>(get<0>(GetParam())),
			get<1>(GetParam())
		);
	}

	TEST_P(PercentageUnsignedShortTest, Equal) {
		EXPECT_EQ(
			Percentage<>(get<0>(GetParam())),
			get<0>(GetParam())
		);
	}

	TEST_P(PercentageUnsignedShortTest, NotEqual) {
		EXPECT_NE(
			Percentage<>(get<0>(GetParam())),
			get<1>(GetParam())
		);
	}

	TEST_P(PercentageDefualtTest, Add) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage<> p1(a), p2(b);
		EXPECT_EQ((p1 + p2), (a + b));
	}

	TEST_P(PercentageDefualtTest, Subtract) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage<> p1(a), p2(b);
		EXPECT_EQ((p1 - p2), (a - b));
	}

	TEST_P(PercentageDefualtTest, Multiply) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage<> p1(a), p2(b);
		EXPECT_EQ((p1 * p2), (a * b));
	}

	TEST_P(PercentageDefualtTest, Divide) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage<> p1(a), p2(b);
		EXPECT_EQ((p1 / p2), (a / b));
	}

	TEST_P(PercentageDefualtTest, Modulus) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage<> p1(a), p2(b);
		EXPECT_EQ((p1 % p2), (a % b));
	}

	TEST_P(PercentageUnsignedShortTest, Add) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage<unsigned short> p1(a);
		EXPECT_EQ((p1 + b), (a + b));
	}

	TEST_P(PercentageUnsignedShortTest, Subtract) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage<unsigned short> p1(a);
		EXPECT_EQ((p1 - b), (a - b));
	}

	TEST_P(PercentageUnsignedShortTest, Multiply) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage<unsigned short> p1(a);
		EXPECT_EQ((p1 * b), (a * b));
	}

	TEST_P(PercentageUnsignedShortTest, Divide) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage<unsigned short> p1(a);
		EXPECT_EQ((p1 / b), (a / b));
	}

	TEST_P(PercentageUnsignedShortTest, Modulus) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Percentage<unsigned short> p1(a);
		EXPECT_EQ((p1 % b), (a % b));
	}

	TEST_P(PercentageShortTest, Add) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Percentage<short> p1(a);
		EXPECT_EQ((p1 + b), (a + b));
	}

	TEST_P(PercentageShortTest, Subtract) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Percentage<short> p1(a);
		EXPECT_EQ((p1 - b), (a - b));
	}

	TEST_P(PercentageShortTest, Multiply) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Percentage<short> p1(a);
		EXPECT_EQ((p1 * b), (a * b));
	}

	TEST_P(PercentageShortTest, Divide) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Percentage<short> p1(a);
		EXPECT_EQ((p1 / b), (a / b));
	}

	TEST_P(PercentageShortTest, Modulus) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Percentage<short> p1(a);
		EXPECT_EQ((p1 % b), (a % b));
	}

	unsigned short const values_default[] = {
		0,
		1,
		100,
		42,
		50,
		9999,
	};

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

		tuple<short, short> const signed_values[] = {
//		make_tuple(0, 0),	//2012-12-15 AMR TODO: division by zero
//		make_tuple(1, 0),	//2012-12-15 AMR TODO: division by zero
		make_tuple(0, 1),
		make_tuple(100, 42),
		make_tuple(50, 25),
		make_tuple(6, 7),
		make_tuple(42, -7),
		make_tuple(-42, -6)
	};

	INSTANTIATE_TEST_CASE_P(Default, PercentageTest, ValuesIn(values_default));
	INSTANTIATE_TEST_CASE_P(Default, PercentageDefualtTest, ValuesIn(values));
	INSTANTIATE_TEST_CASE_P(Default, PercentageUnsignedShortTest, ValuesIn(values));
	INSTANTIATE_TEST_CASE_P(Default, PercentageShortTest, ValuesIn(signed_values));
}
