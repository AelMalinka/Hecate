/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Character.hh"

using namespace Entropy::Hecate;
using namespace testing;
using namespace std;

namespace {
	struct St_tag{}; using St = Stat<St_tag, 2>;
	struct Dx_tag{}; using Dx = Stat<Dx_tag, 2>;
	struct Iq_tag{}; using Iq = Stat<Iq_tag, 2>;
	struct Ht_tag{}; using Ht = Stat<Ht_tag, 2>;

	struct Attack_tag{}; using Attack = Skill<Attack_tag, 1, St, St, Dx>;
	struct Defense_tag{}; using Defense = Skill<Defense_tag, 1, Dx, Dx, Ht>;
	struct Research_tag{}; using Research = Skill<Research_tag, 1, Iq>;
	struct Experiment_tag{}; using Experiment = Skill<Experiment_tag, 1, Research, Iq>;

	using BaseCharacter = Character<tuple<St, Dx, Iq, Ht>>;

	class Character :
		public BaseCharacter
	{
		public:
			template<typename ...sl>
			Character(const sl & ...);
			St &Strength();
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

	St &Character::Strength()
	{
		St st;
		return get(st);
	}
}
