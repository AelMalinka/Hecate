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

	using Entropy::Hecate::PercentType;
	using Entropy::Hecate::Stat;
	using Entropy::Hecate::Skill;
	using Entropy::Hecate::Linear;
	using Entropy::Hecate::Event;

	struct St_tag {}; using St = Stat<St_tag, Linear<2>>;
	struct Dx_tag {}; using Dx = Stat<Dx_tag, Linear<2>>;
	struct Iq_tag {}; using Iq = Stat<Iq_tag, Linear<2>>;
	struct Ht_tag {}; using Ht = Stat<Ht_tag, Linear<2>>;

	struct Attack_tag {}; using Attack = Skill<Attack_tag, Linear<1>, St, St, Dx>;
	struct Defense_tag {}; using Defense = Skill<Defense_tag, Linear<1>, Dx, Dx, Ht>;
	struct Research_tag {}; using Research = Skill<Research_tag, Linear<1>, Iq>;
	struct Experiment_tag {}; using Experiment = Skill<Experiment_tag, Linear<1>, Research, Iq>;

	using BaseCharacter = Hecate::Character<tuple<St, Dx, Iq, Ht>>;

	class TemplateCharacter :
		public BaseCharacter
	{
		public:
			template<typename ...sl>
			TemplateCharacter(const sl & ...);
			St &Strength();
	};

	using Trait = Hecate::Trait<BaseCharacter>;
	using Template = Hecate::Template<BaseCharacter>;
	using TraitHolder = Hecate::TraitHolder<BaseCharacter>;

	template<typename T>
	using SkillHolder = Hecate::SkillHolder<BaseCharacter, T>;

	TEST_CLASS(Templates) {
		TEST_METHOD(Create) {
			St st = 0;
			Dx dx = 0;

			Template empty("empty template"s, {});
			Template stat("skill template"s, {
				make_shared<SkillHolder<Attack>>(Attack(10, st, st, dx))
			});
			Template trait("trait template"s, {
				make_shared<TraitHolder>(Trait("held trait"s, 20, [](auto &, auto &) {}))
			});
			Template many("many template"s, {
				make_shared<SkillHolder<Attack>>(Attack(10, st, st, dx)),
				make_shared<TraitHolder>(Trait("held trait"s, 20, [](auto &, auto &) {}))
			});

			Assert::AreEqual(empty.size(), 0u);
			Assert::AreEqual(stat.size(), 1u);
			Assert::AreEqual(trait.size(), 1u);
			Assert::AreEqual(many.size(), 2u);
		}

		TEST_METHOD(Add) {
			St st = 0;
			Dx dx = 0;

			TemplateCharacter test(0, 0, 0, 0);
			Attack att(test.Stats());

			test.get(att);

			Template many("many template"s, {
				make_shared<SkillHolder<St>>(St(10)),
				make_shared<SkillHolder<Attack>>(Attack(10, st, st, dx)),
				make_shared<TraitHolder>(Trait("rage", 20, [](auto &ev, auto &ch) {
					if (ev.Id() == 11)
						get<St>(ch.Stats()).Raw() += 10;
					else if (ev.Id() == 12)
						get<St>(ch.Stats()).Raw() -= 10;
				}))
			});

			Assert::AreEqual(test.Cost(), 0);
			Assert::AreEqual(many.size(), 3u);

			test.Add(many);
			Assert::AreEqual(test.Strength().Value(), 10);
			Assert::AreEqual(test.get(att).Value(), 16);
			Assert::AreEqual(test.Cost(), 50);

			Event up(11);
			Event down(12);

			test(up);
			Assert::AreEqual(test.Strength().Value(), 20);
			Assert::AreEqual(test.Cost(), 70);

			test(down);
			Assert::AreEqual(test.Strength().Value(), 10);
			Assert::AreEqual(test.Cost(), 50);

			test.Remove(many);
		}
	};

	template<typename ...sl>
	TemplateCharacter::TemplateCharacter(const sl & ...s)
		: BaseCharacter(s...)
	{}

	St &TemplateCharacter::Strength()
	{
		St st;
		return get(st);
	}
}