/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Stat.hh"

using namespace std;
using namespace testing;
using namespace Entropy::Hecate;

namespace {
	struct Strength_tag{}; using Strength = Stat<Strength_tag, Linear<1>>;
	struct Dexterity_tag{}; using Dexterity = Stat<Dexterity_tag, Linear<1>>;
	struct Constitution_tag{}; using Constitution = Stat<Constitution_tag, Linear<1>>;
	struct Intelligence_tag{}; using Intelligence = Stat<Intelligence_tag, Linear<1>>;
	struct Wisdom_tag{}; using Wisdom = Stat<Wisdom_tag, Linear<1>>;
	struct Charisma_tag{}; using Charisma = Stat<Charisma_tag, Linear<1>>;

	TEST(Stat, Create) {
		Strength st = 0;
		Dexterity dx = 0;
		Intelligence iq = 0;
		Constitution ht = 0;
		Wisdom ws = 0;
		Charisma ch = 0;
	}

	TEST(Stat, Value) {
		Strength st = 0;
		EXPECT_EQ(st.Value(), 0);

		st.Raw() = 10;
		EXPECT_EQ(st.Value(), 10);

		st.Raw() = -10;
		EXPECT_EQ(st.Value(), -10);
		EXPECT_NE(st.Value(), 65526);
	}

	TEST(Stat, Cost) {
		Strength st = 5;
		EXPECT_EQ(st.Cost(), 5);

		st.Raw() = 10;
		EXPECT_EQ(st.Cost(), 10);

		struct temp_tag {};
		Stat<temp_tag, Linear<5>> stat = 5;

		EXPECT_EQ(stat.Cost(), 25);

		stat.Raw() = 10;
		EXPECT_EQ(stat.Cost(), 50);
	}
}
