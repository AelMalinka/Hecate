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

	ENTROPY_HECATE_DEFINE_CHARACTER(St, Dx, Iq, Ht);

	class Character :
		public BaseCharacter
	{
		public:
			template<typename ...sl>
			Character(const sl & ...);
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

		at.setValue(5);
		df.setValue(10);

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

	template<typename ...sl>
	Character::Character(const sl & ...s)
		: BaseCharacter(s...)
	{}
}
