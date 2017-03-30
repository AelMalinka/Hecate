/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Character.hh"

using namespace std;
using namespace testing;
using namespace Entropy::Hecate;

namespace {
	struct St_tag{}; using St = Stat<St_tag, Linear<2>>;
	struct Dx_tag{}; using Dx = Stat<Dx_tag, Linear<2>>;
	struct Iq_tag{}; using Iq = Stat<Iq_tag, Linear<2>>;
	struct Ht_tag{}; using Ht = Stat<Ht_tag, Linear<2>>;

	struct Attack_tag{}; using Attack = Skill<Attack_tag, Linear<1>, St, St, Dx>;
	struct Defense_tag{}; using Defense = Skill<Defense_tag, Linear<1>, Dx, Dx, Ht>;
	struct Research_tag{}; using Research = Skill<Research_tag, Linear<1>, Iq>;
	struct Experiment_tag{}; using Experiment = Skill<Experiment_tag, Linear<1>, Research, Iq>;

	using BaseCharacter = Character<tuple<St, Dx, Iq, Ht>>;

	class Character :
		public BaseCharacter
	{
		public:
			template<typename ...sl>
			Character(const sl & ...);
			Check attack();
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

	TEST(Character, getSkill) {
		Character test(5, 10, 15, 20);

		Attack at(test.Stats());
		Defense df(test.Stats());
		Research rs(test.Stats());

		auto t = tuple_cat(test.Stats(), make_tuple(rs));
		Experiment ex(t);

		test.set(at);
		test.set(df);
		test.set(rs);
		test.set(ex);

		auto at2 = test.get(at);
		auto df2 = test.get(df);
		auto rs2 = test.get(rs);
		auto ex2 = test.get(ex);

		EXPECT_EQ(at.Value(), at2.Value());
		EXPECT_EQ(df.Value(), df2.Value());
		EXPECT_EQ(rs.Value(), rs2.Value());
		EXPECT_EQ(ex.Value(), ex2.Value());
	}

	TEST(Character, getDefaultSkill) {
		Character test(5, 10, 15, 20);

		Attack at(test.Stats());
		Defense df(test.Stats());
		Research rs(test.Stats());

		at.Raw() = 5;
		df.Raw() = 10;

		test.set(at);
		test.set(df);

		auto a = test.get(at);
		auto d = test.get(df);
		auto r = test.get(rs);

		EXPECT_EQ(a.Value(), 11);
		EXPECT_EQ(d.Value(), 23);
		EXPECT_EQ(r.Value(), 15);

		EXPECT_EQ(a.Value(), at.Value());
		EXPECT_EQ(d.Value(), df.Value());
		EXPECT_EQ(r.Value(), rs.Value());
	}

	TEST(Character, Check) {
		Character test(5, 10, 15, 20);
		Check att = test.attack();

		auto res = att();
		EXPECT_EQ(res.size(), 1ul);

		auto night = att(Modifier(10, negative));
		EXPECT_EQ(night.size(), 2ul);
	}

	template<typename ...sl>
	Character::Character(const sl & ...s)
		: BaseCharacter(s...)
	{}

	Check Character::attack()
	{
		Attack at(Stats());

		return _check(Modifier(get(at)));
	}
}
