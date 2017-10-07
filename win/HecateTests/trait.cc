/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
using namespace Entropy::Hecate;

namespace Tests
{
	class TimeChange :
		public Event
	{
		public:
			enum when_t
			{
				Dawn,
				Day,
				Dusk,
				Night
			};
		public:
			TimeChange(when_t);
			when_t When() const;
		private:
			when_t _when;
	};

	struct St_tag {}; using St = Stat<St_tag, Linear<2>>;
	struct Dx_tag {}; using Dx = Stat<Dx_tag, Linear<2>>;
	struct Iq_tag {}; using Iq = Stat<Iq_tag, Linear<2>>;
	struct Ht_tag {}; using Ht = Stat<Ht_tag, Linear<2>>;

	struct Attack_tag {}; using Attack = Skill<Attack_tag, Linear<1>, St, St, Dx>;
	struct Defense_tag {}; using Defense = Skill<Defense_tag, Linear<1>, Dx, Dx, Ht>;
	struct Research_tag {}; using Research = Skill<Research_tag, Linear<1>, Iq>;
	struct Experiment_tag {}; using Experiment = Skill<Experiment_tag, Linear<1>, Research, Iq>;

	using BaseCharacter = Character<tuple<St, Dx, Iq, Ht>>;

	class TraitCharacter :
		public BaseCharacter
	{
		public:
			template<typename ...sl>
			TraitCharacter(const sl & ...);
			St &Strength();
	};

	TEST_CLASS(Events) {
		TEST_METHOD(Create) {
			Event ev(10);
			TimeChange night(TimeChange::Night);
			TimeChange day(TimeChange::Day);

			Assert::IsTrue(night.When() == TimeChange::Night);
			Assert::IsTrue(day.When() == TimeChange::Day);

			Assert::AreEqual(ev.Id(), 10u);
			Assert::AreEqual(night.Id(), day.Id());

			Assert::AreNotEqual(ev.Id(), night.Id());
		}
	};

	TEST_CLASS(Traits) {
		TEST_METHOD(Create) {
			Trait<BaseCharacter> first("MyTrait", 20, [](auto &, auto &) {});

			Assert::AreEqual(first.Name(), "MyTrait"s);
			Assert::AreEqual(first.Cost(), 20);
		}

		TEST_METHOD(Add) {
			TraitCharacter test(5, 10, 15, 20);

			Trait<BaseCharacter> trait("MyTrait", 20, [](auto &, auto &) {});
			Assert::AreEqual(test.Cost(), 100);

			test.Add(trait);
			Assert::AreEqual(test.Cost(), 120);
		}

		TEST_METHOD(Call) {
			Event ev(11);
			TraitCharacter test(5, 10, 15, 20);
			Assert::AreEqual(test.Strength().Value(), 5);
			Assert::AreEqual(test.Cost(), 100);

			test(ev);
			Assert::AreEqual(test.Strength().Value(), 5);
			Assert::AreEqual(test.Cost(), 100);

			test.Add(Trait<BaseCharacter>("My Trait", 20, [](auto &ev, auto &ch) {
				if (ev.Id() == 11)
					get<St>(ch.Stats()).Raw() += 1;
			}));
			Assert::AreEqual(test.Strength().Value(), 5);
			Assert::AreEqual(test.Cost(), 120);

			test(ev);
			Assert::AreEqual(test.Strength().Value(), 6);
			Assert::AreEqual(test.Cost(), 122);
		}
	};

	TimeChange::TimeChange(when_t when)
		: Event(1024), _when(when)
	{}

	TimeChange::when_t TimeChange::When() const
	{
		return _when;
	}

	template<typename ...sl>
	TraitCharacter::TraitCharacter(const sl & ...s)
		: BaseCharacter(s...)
	{}

	St &TraitCharacter::Strength()
	{
		St st;
		return get(st);
	}
}