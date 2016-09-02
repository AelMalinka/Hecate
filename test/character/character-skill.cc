/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Skill.hh"

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

	TEST(Skill, Create) {
		St st = 0;
		Dx dx = 0;
		Iq iq = 0;
		Ht ht = 0;

		Attack at(0, st, st, dx);
		Defense df(0, dx, dx, ht);
		Research rs(0, iq);
		Experiment ex(0, rs, iq);
	}

	TEST(Skill, Value) {
		St st = 10;
		Dx dx = 15;
		Iq iq = 20;
		Ht ht = 5;

		Attack at(10, st, st, dx);
		Defense df(5, dx, dx, ht);
		Research rs(10, iq);
		Experiment ex(10, rs, iq);

		EXPECT_EQ(at.Value(), 21);
		EXPECT_EQ(df.Value(), 16);
		EXPECT_EQ(rs.Value(), 30);
		EXPECT_EQ(ex.Value(), 35);
	}

	TEST(Skill, Reference) {
		St st = 10;
		Dx dx = 15;
		Iq iq = 20;
		Ht ht = 5;

		Attack at(10, st, st, dx);
		Defense df(5, dx, dx, ht);
		Research rs(10, iq);
		Experiment ex(10, rs, iq);

		EXPECT_EQ(at.Value(), 21);
		EXPECT_EQ(df.Value(), 16);
		EXPECT_EQ(rs.Value(), 30);
		EXPECT_EQ(ex.Value(), 35);

		st.Raw() = 11;
		dx.Raw() = 16;
		ht.Raw() = 6;
		iq.Raw() = 25;
		rs.Raw() = 8;

		EXPECT_EQ(at.Value(), 22);
		EXPECT_EQ(df.Value(), 17);
		EXPECT_EQ(rs.Value(), 33);
		EXPECT_EQ(ex.Value(), 39);
	}

	TEST(Skill, Copy) {
		St st = 10;
		Dx dx = 15;
		Iq iq = 20;
		Ht ht = 5;

		Attack at(10, st, st, dx);
		Defense df(5, dx, dx, ht);
		Research rs(10, iq);
		Experiment ex(10, rs, iq);

		Attack at2 = at;
		Defense df2 = df;
		Research rs2 = rs;
		Experiment ex2 = ex;

		EXPECT_EQ(at.Value(), at2.Value());
		EXPECT_EQ(df.Value(), df2.Value());
		EXPECT_EQ(rs.Value(), rs2.Value());
		EXPECT_EQ(ex.Value(), ex2.Value());
	}

	TEST(Skill, StatList) {
		tuple<St, Dx, Iq, Ht> stats(10, 15, 20, 5);

		Attack at(stats);
		Defense df(stats);
		Research rs(stats);
		auto t = tuple_cat(stats, make_tuple(at, df, rs));
		Experiment ex(t);

		EXPECT_EQ(at.Value(), 11);
		EXPECT_EQ(df.Value(), 11);
		EXPECT_EQ(rs.Value(), 20);
		EXPECT_EQ(ex.Value(), 20);
	}
}
