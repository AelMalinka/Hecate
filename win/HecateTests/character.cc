/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
	namespace Hecate = Entropy::Hecate;

	using Hecate::Check;
	using Hecate::Linear;
	using Hecate::Modifier;
	using Hecate::negative;

	struct St_tag {}; using St = Hecate::Stat<St_tag, Linear<2>>;
	struct Dx_tag {}; using Dx = Hecate::Stat<Dx_tag, Linear<2>>;
	struct Iq_tag {}; using Iq = Hecate::Stat<Iq_tag, Linear<2>>;
	struct Ht_tag {}; using Ht = Hecate::Stat<Ht_tag, Linear<2>>;

	struct Attack_tag {}; using Attack = Hecate::Skill<Attack_tag, Linear<1>, St, St, Dx>;
	struct Defense_tag {}; using Defense = Hecate::Skill<Defense_tag, Linear<1>, Dx, Dx, Ht>;
	struct Research_tag {}; using Research = Hecate::Skill<Research_tag, Linear<1>, Iq>;
	struct Experiment_tag {}; using Experiment = Hecate::Skill<Experiment_tag, Linear<1>, Research, Iq>;

	struct Health_tag {}; using Health = Hecate::Resource<Health_tag, Linear<10>, Linear<1>, Ht>;

	using BaseCharacter = Hecate::Character<tuple<St, Dx, Iq, Ht>>;

	class MyCharacter :
		public BaseCharacter
	{
		public:
			template<typename ...sl>
			MyCharacter(const sl & ...);
			Check attack();
	};

	TEST_CLASS(Stat) {
		TEST_METHOD(Create) {
			St st = 0;
			Dx dx = 0;
			Iq iq = 0;
			Ht ht = 0;
		}

		TEST_METHOD(Value) {
			St st = 0;
			Assert::AreEqual(st.Value(), 0);

			st.Raw() = 10;
			Assert::AreEqual(st.Value(), 10);

			st.Raw() = -10;
			Assert::AreEqual(st.Value(), -10);
			Assert::AreNotEqual(st.Value(), 65526);
		}

		TEST_METHOD(Cost) {
			St st = 5;
			Assert::AreEqual(st.Cost(), 10);

			st.Raw() = 10;
			Assert::AreEqual(st.Cost(), 20);

			struct temp_tag {};
			Hecate::Stat<temp_tag, Linear<5>> stat = 5;
			Assert::AreEqual(stat.Cost(), 25);

			stat.Raw() = 10;
			Assert::AreEqual(stat.Cost(), 50);
		}

		TEST_METHOD(Modifiers) {
			St st = 5;
			Assert::AreEqual(st.Value(), 5);
			Assert::AreEqual(st.Cost(), 10);

			st.Add(Modifier(5));
			Assert::AreEqual(st.Value(), 10);
			Assert::AreEqual(st.Cost(), 10);

			st.Raw() = 10;
			Assert::AreEqual(st.Value(), 15);
			Assert::AreEqual(st.Cost(), 20);
		}
	};

	TEST_CLASS(Skill) {
		TEST_METHOD(Create) {
			St st = 0;
			Dx dx = 0;
			Iq iq = 0;
			Ht ht = 0;

			Attack at(0, st, st, dx);
			Defense df(0, dx, dx, ht);
			Research rs(0, iq);
			Experiment ex(0, rs, iq);
		}

		TEST_METHOD(Value) {
			St st = 10;
			Dx dx = 15;
			Iq iq = 20;
			Ht ht = 5;

			Attack at(10, st, st, dx);
			Defense df(5, dx, dx, ht);
			Research rs(10, iq);
			Experiment ex(10, rs, iq);

			Assert::AreEqual(at.Value(), 21);
			Assert::AreEqual(df.Value(), 16);
			Assert::AreEqual(rs.Value(), 30);
			Assert::AreEqual(ex.Value(), 35);
		}

		TEST_METHOD(Cost) {
			St st = 10;
			Dx dx = 15;

			Attack at(5, st, st, dx);

			Assert::AreEqual(at.Cost(), 5);
			Assert::AreEqual(st.Cost(), 20);
			Assert::AreEqual(dx.Cost(), 30);

			struct temp_tag {};
			Hecate::Skill<temp_tag, Linear<10>, St, Dx> temp(5, st, dx);
			Assert::AreEqual(temp.Cost(), 50);

			temp.Raw() = 10;
			Assert::AreEqual(temp.Cost(), 100);
		}

		TEST_METHOD(Modifiers) {
			St st = 10;
			Dx dx = 15;

			Attack at(5, st, st, dx);
			Assert::AreEqual(at.Cost(), 5);
			Assert::AreEqual(st.Cost(), 20);
			Assert::AreEqual(dx.Cost(), 30);
			Assert::AreEqual(at.Value(), 16);

			at.Add(Modifier(10));
			Assert::AreEqual(at.Cost(), 5);
			Assert::AreEqual(st.Cost(), 20);
			Assert::AreEqual(dx.Cost(), 30);
			Assert::AreEqual(at.Value(), 26);

			at.Raw() = 10;
			Assert::AreEqual(at.Cost(), 10);
			Assert::AreEqual(st.Cost(), 20);
			Assert::AreEqual(dx.Cost(), 30);
			Assert::AreEqual(at.Value(), 31);
		}

		TEST_METHOD(Reference) {
			St st = 10;
			Dx dx = 15;
			Iq iq = 20;
			Ht ht = 5;

			Attack at(10, st, st, dx);
			Defense df(5, dx, dx, ht);
			Research rs(10, iq);
			Experiment ex(10, rs, iq);

			Assert::AreEqual(at.Value(), 21);
			Assert::AreEqual(df.Value(), 16);
			Assert::AreEqual(rs.Value(), 30);
			Assert::AreEqual(ex.Value(), 35);

			st.Raw() = 11;
			dx.Raw() = 16;
			ht.Raw() = 6;
			iq.Raw() = 25;
			rs.Raw() = 8;

			Assert::AreEqual(at.Value(), 22);
			Assert::AreEqual(df.Value(), 17);
			Assert::AreEqual(rs.Value(), 33);
			Assert::AreEqual(ex.Value(), 39);
		}

		TEST_METHOD(Copy) {
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

			Assert::AreEqual(at.Value(), at2.Value());
			Assert::AreEqual(df.Value(), df2.Value());
			Assert::AreEqual(rs.Value(), rs2.Value());
			Assert::AreEqual(ex.Value(), ex2.Value());
		}

		TEST_METHOD(StatList) {
			tuple<St, Dx, Iq, Ht> stats(10, 15, 20, 5);

			Attack at(stats);
			Defense df(stats);
			Research rs(stats);
			auto t = tuple_cat(stats, make_tuple(at, df, rs));
			Experiment ex(t);

			Assert::AreEqual(at.Value(), 11);
			Assert::AreEqual(df.Value(), 11);
			Assert::AreEqual(rs.Value(), 20);
			Assert::AreEqual(ex.Value(), 20);
		}
	};

	TEST_CLASS(Resource) {
		TEST_METHOD(Create) {
			Ht ht = 10;

			Health hp(0, ht);

			Assert::AreEqual(hp.Current(), 100);
			Assert::AreEqual(hp.Max(), 100);
			Assert::AreEqual(hp.Value(), 100);
			Assert::AreEqual(hp.Raw(), 0);
			Assert::AreEqual(hp.Cost(), 0);

			hp.Current() = 0;
			Assert::AreEqual(hp.Current(), 0);
			Assert::AreEqual(hp.Max(), 100);
			Assert::AreEqual(hp.Value(), 100);
			Assert::AreEqual(hp.Raw(), 0);
			Assert::AreEqual(hp.Cost(), 0);
		}
	};

	TEST_CLASS(Character) {
		TEST_METHOD(Create) {
			MyCharacter test1;
			MyCharacter test2(10, 10, 10, 10);
		}

		TEST_METHOD(getStat) {
			MyCharacter test(5, 10, 15, 20);

			St st;
			Dx dx;
			Iq iq;
			Ht ht;

			Assert::AreEqual(test.get(st).Value(), 5);
			Assert::AreEqual(test.get(dx).Value(), 10);
			Assert::AreEqual(test.get(iq).Value(), 15);
			Assert::AreEqual(test.get(ht).Value(), 20);

			Assert::AreEqual(st.Value(), 5);
			Assert::AreEqual(dx.Value(), 10);
			Assert::AreEqual(iq.Value(), 15);
			Assert::AreEqual(ht.Value(), 20);
		}

		TEST_METHOD(getSkill) {
			MyCharacter test(5, 10, 15, 20);

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

			Assert::AreEqual(at.Value(), at2.Value());
			Assert::AreEqual(df.Value(), df2.Value());
			Assert::AreEqual(rs.Value(), rs2.Value());
			Assert::AreEqual(ex.Value(), ex2.Value());
		}

		TEST_METHOD(getDefaultSkill) {
			MyCharacter test(5, 10, 15, 20);

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

			Assert::AreEqual(a.Value(), 11);
			Assert::AreEqual(d.Value(), 23);
			Assert::AreEqual(r.Value(), 15);

			Assert::AreEqual(a.Value(), at.Value());
			Assert::AreEqual(d.Value(), df.Value());
			Assert::AreEqual(r.Value(), rs.Value());
		}

		TEST_METHOD(Check) {
			using Hecate::Check;

			MyCharacter test(5, 10, 15, 20);
			Check att = test.attack();

			auto res = att();
			Assert::AreEqual(res.size(), 1u);

			auto night = att(Modifier(10, negative));
			Assert::AreEqual(night.size(), 2u);
		}
	};

	template<typename ...sl>
	MyCharacter::MyCharacter(const sl & ...s)
		: BaseCharacter(s...)
	{}

	Check MyCharacter::attack()
	{
		Attack at(Stats());

		return _check(Modifier(get(at)));
	}
}