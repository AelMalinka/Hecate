/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Stat.hh"

using namespace std;
using namespace testing;
using namespace Entropy::Hecate;

namespace {
	ENTROPY_HECATE_DEFINE_STAT(Strength);
	ENTROPY_HECATE_DEFINE_STAT(Dexterity);
	ENTROPY_HECATE_DEFINE_STAT(Constitution);
	ENTROPY_HECATE_DEFINE_STAT(Intelligence);
	ENTROPY_HECATE_DEFINE_STAT(Wisdom);
	ENTROPY_HECATE_DEFINE_STAT(Charisma);

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
		EXPECT_NE(st.Value(), -10);
		EXPECT_EQ(st.Value(), 65526);
	}
}
