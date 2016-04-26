/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Character.hh"

using namespace std;
using namespace testing;
using namespace Entropy::Hecate;

namespace {
	ENTROPY_HECATE_DEFINE_STAT(St);
	ENTROPY_HECATE_DEFINE_STAT(Dx);
	ENTROPY_HECATE_DEFINE_STAT(Iq);
	ENTROPY_HECATE_DEFINE_STAT(Ht);

	ENTROPY_HECATE_DEFINE_SKILL(Attack, St, St, Dx);
	ENTROPY_HECATE_DEFINE_SKILL(Defense, Dx, Dx, Ht);
	ENTROPY_HECATE_DEFINE_SKILL(Research, Iq);
	ENTROPY_HECATE_DEFINE_SKILL(Experiment, Research, Iq);

	typedef Entropy::Hecate::Character<tuple<St, Dx, Iq, Ht>> BaseCharacter;

	class Character :
		public BaseCharacter
	{
		public:
			template<typename ...Stats>
			Character(const Stats & ...);
	};

	TEST(Character, Create) {
		Character test1;
		Character test2(10, 10, 10, 10);
	}

	TEST(Character, getStat) {
		Character test(5, 10, 15, 20);

		St st;
		Dx dx;
		Iq iq;
		Ht ht;

		EXPECT_EQ(test.get(st).Value(), 5);
		EXPECT_EQ(test.get(dx).Value(), 10);
		EXPECT_EQ(test.get(iq).Value(), 15);
		EXPECT_EQ(test.get(ht).Value(), 20);
	
		EXPECT_EQ(st.Value(), 5);
		EXPECT_EQ(dx.Value(), 10);
		EXPECT_EQ(iq.Value(), 15);
		EXPECT_EQ(ht.Value(), 20);
	}

	template<typename ...Stats>
	Character::Character(const Stats & ...stats)
		: BaseCharacter(stats...)
	{}
}
