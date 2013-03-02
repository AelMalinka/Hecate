/*	Copyright 2012 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "Stat.hh"
#include "gtest/gtest.h"
#include <tuple>

using namespace std;
using namespace Entropy::Hecate;
using namespace testing;

namespace {
	struct default_tag {};
	struct not_default_tag {};

	struct StatTest : public TestWithParam<unsigned short> {};
	struct StatDefualtTest : public TestWithParam<tuple<unsigned short, unsigned short>> {};
	struct StatUnsignedShortTest : public TestWithParam<tuple<unsigned short, unsigned short>> {};
	struct StatShortTest : public TestWithParam<tuple<short, short>> {};

	TEST_P(StatTest, Equal) {
		Stat<default_tag> a;
		Stat<default_tag> b(GetParam());
		a = GetParam();
		EXPECT_EQ(a, b);
	}

	TEST_P(StatTest, NotEqual) {
		Stat<default_tag> a(GetParam());
		Stat<not_default_tag> b(GetParam());
		EXPECT_NE(a, b);
	}

	TEST_P(StatDefualtTest, Equal) {
		EXPECT_EQ(
			Stat<default_tag>(get<0>(GetParam())),
			get<0>(GetParam())
		);
	}

	TEST_P(StatDefualtTest, NotEqual) {
		EXPECT_NE(
			Stat<default_tag>(get<0>(GetParam())),
			get<1>(GetParam())
		);
	}

	TEST_P(StatUnsignedShortTest, Equal) {
		EXPECT_EQ(
			Stat<default_tag>(get<0>(GetParam())),
			get<0>(GetParam())
		);
	}

	TEST_P(StatUnsignedShortTest, NotEqual) {
		EXPECT_NE(
			Stat<default_tag>(get<0>(GetParam())),
			get<1>(GetParam())
		);
	}

	TEST_P(StatDefualtTest, Add) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<default_tag> p1(a), p2(b);
		EXPECT_EQ((p1 + p2), (a + b));
	}

	TEST_P(StatDefualtTest, Subtract) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<default_tag> p1(a), p2(b);
		EXPECT_EQ((p1 - p2), (a - b));
	}

	TEST_P(StatDefualtTest, Multiply) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<default_tag> p1(a), p2(b);
		EXPECT_EQ((p1 * p2), (a * b));
	}

	TEST_P(StatDefualtTest, Divide) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<default_tag> p1(a), p2(b);
		EXPECT_EQ((p1 / p2), (a / b));
	}

	TEST_P(StatDefualtTest, Modulus) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<default_tag> p1(a), p2(b);
		EXPECT_EQ((p1 % p2), (a % b));
	}

	TEST_P(StatUnsignedShortTest, Add) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<default_tag, unsigned short> p1(a);
		EXPECT_EQ((p1 + b), (a + b));
	}

	TEST_P(StatUnsignedShortTest, Subtract) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<default_tag, unsigned short> p1(a);
		EXPECT_EQ((p1 - b), (a - b));
	}

	TEST_P(StatUnsignedShortTest, Multiply) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<default_tag, unsigned short> p1(a);
		EXPECT_EQ((p1 * b), (a * b));
	}

	TEST_P(StatUnsignedShortTest, Divide) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<default_tag, unsigned short> p1(a);
		EXPECT_EQ((p1 / b), (a / b));
	}

	TEST_P(StatUnsignedShortTest, Modulus) {
		unsigned short a = get<0>(GetParam());
		unsigned short b = get<1>(GetParam());
		Stat<default_tag, unsigned short> p1(a);
		EXPECT_EQ((p1 % b), (a % b));
	}

	TEST_P(StatShortTest, Add) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Stat<default_tag, short> p1(a);
		EXPECT_EQ((p1 + b), (a + b));
	}

	TEST_P(StatShortTest, Subtract) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Stat<default_tag, short> p1(a);
		EXPECT_EQ((p1 - b), (a - b));
	}

	TEST_P(StatShortTest, Multiply) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Stat<default_tag, short> p1(a);
		EXPECT_EQ((p1 * b), (a * b));
	}

	TEST_P(StatShortTest, Divide) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Stat<default_tag, short> p1(a);
		EXPECT_EQ((p1 / b), (a / b));
	}

	TEST_P(StatShortTest, Modulus) {
		short a = get<0>(GetParam());
		short b = get<1>(GetParam());
		Stat<default_tag, short> p1(a);
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

	INSTANTIATE_TEST_CASE_P(Default, StatTest, ValuesIn(values_default));
	INSTANTIATE_TEST_CASE_P(Default, StatDefualtTest, ValuesIn(values));
	INSTANTIATE_TEST_CASE_P(Default, StatUnsignedShortTest, ValuesIn(values));
	INSTANTIATE_TEST_CASE_P(Default, StatShortTest, ValuesIn(signed_values));
}
