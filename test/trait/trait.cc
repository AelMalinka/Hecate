/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Character.hh"

using namespace Entropy::Hecate;
using namespace testing;
using namespace std;

namespace {
	ENTROPY_HECATE_DEFINE_STAT(St, 2);
	ENTROPY_HECATE_DEFINE_STAT(Dx, 2);
	ENTROPY_HECATE_DEFINE_STAT(Iq, 2);
	ENTROPY_HECATE_DEFINE_STAT(Ht, 2);

	ENTROPY_HECATE_DEFINE_SKILL(Attack, 1, St, St, Dx);
	ENTROPY_HECATE_DEFINE_SKILL(Defense, 1, Dx, Dx, Ht);
	ENTROPY_HECATE_DEFINE_SKILL(Research, 1, Iq);
	ENTROPY_HECATE_DEFINE_SKILL(Experiment, 1, Research, Iq);

	ENTROPY_HECATE_DEFINE_CHARACTER(St, Dx, Iq, Ht);

	class Character :
		public BaseCharacter
	{
		public:
			template<typename ...sl>
			Character(const sl & ...);
			ENTROPY_HECATE_STAT_ACCESSOR(Strength, St);
			ENTROPY_HECATE_STAT_ACCESSOR(Dexterity, Dx);
			ENTROPY_HECATE_STAT_ACCESSOR(Intelligence, Iq);
			ENTROPY_HECATE_STAT_ACCESSOR(Health, Ht);
	};

	TEST(Trait, Create) {
		Trait<BaseCharacter> first("MyTrait", 20, [](auto &, auto &) {});

		EXPECT_EQ(first.Name(), "MyTrait"s);
		EXPECT_EQ(first.Cost(), 20);
	}

	TEST(Trait, Add) {
		Character test(5, 10, 15, 20);

		Trait<BaseCharacter> trait("MyTrait", 20, [](auto &, auto &) {});
		EXPECT_EQ(test.Cost(), 100);

		test.Add(trait);
		EXPECT_EQ(test.Cost(), 120);
	}

	TEST(Trait, Call) {
		Event ev(11);
		Character test(5, 10, 15, 20);
		EXPECT_EQ(test.Strength().Value(), 5);
		EXPECT_EQ(test.Cost(), 100);

		test(ev);
		EXPECT_EQ(test.Strength().Value(), 5);
		EXPECT_EQ(test.Cost(), 100);

		test.Add(Trait<BaseCharacter>("My Trait", 20, [](auto &ev, auto &ch) {
			if(ev.Id() == 11)
				get<St>(ch.Stats()).Raw() += 1;
		}));
		EXPECT_EQ(test.Strength().Value(), 5);
		EXPECT_EQ(test.Cost(), 120);

		test(ev);
		EXPECT_EQ(test.Strength().Value(), 6);
		EXPECT_EQ(test.Cost(), 122);
	}

	template<typename ...sl>
	Character::Character(const sl & ...s)
		: BaseCharacter(s...)
	{}
}
