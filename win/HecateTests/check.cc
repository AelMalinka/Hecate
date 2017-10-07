/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
	using Entropy::Hecate::PercentType;
	using Entropy::Hecate::Stat;
	using Entropy::Hecate::Skill;
	using Entropy::Hecate::Linear;
	using Entropy::Hecate::Modifier;
	using Entropy::Hecate::ModifierList;
	using Entropy::Hecate::negative;
	using Entropy::Hecate::onSuccess;
	using Entropy::Hecate::onFailure;
	using Entropy::Hecate::onCritical;

	struct stat_tag {}; using stat = Stat<stat_tag, Linear<2>>;
	struct skill_tag {}; using skill = Skill<skill_tag, Linear<1>, stat>;

	TEST_CLASS(Check) {
		TEST_METHOD(Instantiate) {
			using Entropy::Hecate::Check;

			PercentType luck = 10;
			stat s = 20;
			stat o = 10;

			Check empty;
			Check with_luck(luck);
			Check modifiers(vector<Modifier>({
				Modifier(-10),
				Modifier(s),
				Modifier(o, negative)
			}));
			Check modifiers_luck(luck, {
				Modifier(-10),
				Modifier(s),
				Modifier(o, negative)
			});
		}

		TEST_METHOD(Roll) {
			using Entropy::Hecate::Check;
			Check empty;

			for (auto x = 0; x < 10000; x++) {
				auto res = empty();

				Assert::IsTrue(res.Value() < (100 - ENTROPY_HECATE_DEFAULT_LUCK));
				Assert::IsTrue(res.Value() >= (ENTROPY_HECATE_DEFAULT_LUCK - 100));
			}

			stat st = 10;
			skill sk(0, st);

			Check modifiers({
				Modifier(st),
				Modifier(sk),
				Modifier(-10)
			});

			for (auto x = 0; x < 10000; x++) {
				auto res = modifiers();

				Assert::IsTrue(res.Value() < (100 - ENTROPY_HECATE_DEFAULT_LUCK));
				Assert::IsTrue(res.Value() >= (ENTROPY_HECATE_DEFAULT_LUCK - 100));
			}
		}

		TEST_METHOD(Modifiers) {
			using Entropy::Hecate::Check;

			stat s1 = 10;
			stat s2 = 15;
			skill first_skill(10, s1);
			skill second_skill(0, s2);

			Check first({
				Modifier(first_skill)
			});

			Check second({
				Modifier(second_skill),
				Modifier(first, negative)
			});

			auto res = second();

			Assert::AreEqual(res.size(), 2u);

			auto iter = res.begin();
			iter++;
			Assert::IsTrue(res.Value() < (100 - ENTROPY_HECATE_DEFAULT_LUCK));
			Assert::IsTrue(res.Value() > (ENTROPY_HECATE_DEFAULT_LUCK - 100));
		}

		TEST_METHOD(Callback) {
			using Entropy::Hecate::Check;

			Check first({
				Modifier(10)
			});

			bool ran = false;
			first.Add([&](auto) {
				ran = true;
			});

			Assert::IsFalse(ran);
			first();
			Assert::IsTrue(ran);
		}

		TEST_METHOD(onWrappers) {
			using Entropy::Hecate::Check;

			Check first;
			auto successes = 0;
			auto failures = 0;
			auto criticals = 0;

			first.Add(onSuccess([&successes](auto) {
				++successes;
			}));
			first.Add(onFailure([&failures](auto) {
				++failures;
			}));
			first.Add(onCritical([&criticals](auto) {
				++criticals;
			}));

			Assert::AreEqual(successes, 0);
			Assert::AreEqual(failures, 0);
			Assert::AreEqual(criticals, 0);

			for (auto x = 0; x < 10000; x++) {
				first();
			}

			Assert::IsTrue(successes > 0);
			Assert::IsTrue(failures > 0);
			Assert::IsTrue(criticals > 0);
		}
	};

	TEST_CLASS(Result) {
		TEST_METHOD(isSuccess) {
			using Entropy::Hecate::Check;

			Check::Result first(-5, 10, 50, 5, {});
			Check::Result second(10, 10, 10, 5, {});

			Assert::IsFalse(first.isSuccess());
			Assert::IsTrue(second.isSuccess());
			Assert::IsFalse(first);
			Assert::IsTrue(second);
		}

		TEST_METHOD(isCritical) {
			using Entropy::Hecate::Check;

			Check::Result first(-5, 10, 96, 5, {});
			Check::Result second(-5, 10, 50, 5, {});
			Check::Result third(10, 10, 4, 5, {});
			Check::Result fourth(5, 10, 5, 5, {});

			Assert::IsTrue(first.isCritical());
			Assert::IsFalse(second.isCritical());
			Assert::IsTrue(third.isCritical());
			Assert::IsFalse(fourth.isCritical());
		}

		TEST_METHOD(Values) {
			using Entropy::Hecate::Check;

			Check::Result empty(10, 10, 10, 5, {});

			Assert::AreEqual(empty.Value(), 10);
			Assert::AreEqual(empty.Chance(), 10);
			Assert::AreEqual(empty.Luck(), 5);

			stat v = 10;
			ModifierList l;

			l.Add(Modifier(10));
			l.Add(Modifier(v));
			l.Add(Modifier(v, negative));

			Check::Result result(5, 5, 5, 5, l);

			Assert::AreEqual(result.Value(), 5);
			Assert::AreEqual(result.Chance(), 5);
			Assert::AreEqual(result.Luck(), 5);
		}

		TEST_METHOD(Luck) {
			using Entropy::Hecate::Check;

			Check::Result res1(10, 10, 10, 5, {});
			Check::Result res2(10, 10, 10, 10, {});

			Assert::AreEqual(res1.Luck(), 5);
			Assert::AreEqual(res2.Luck(), 10);
		}

		TEST_METHOD(Iterate) {
			using Entropy::Hecate::Check;

			Check::Result empty(10, 10, 10, 5, {});
			vector<Modifier> empty_list;

			for (auto &&i : empty) {
				empty_list.push_back(i.modifier);
			}

			Assert::AreEqual(empty_list.size(), 0u);

			stat s = 10;
			skill k(5, s);
			Check::Result result(5, 5, 5, 5, ModifierList({
				Modifier(10),
				Modifier(s),
				Modifier(k),
				Modifier(k, negative)
			}));
			vector<Modifier> result_list;

			for (auto &i : result) {
				result_list.push_back(i.modifier);
			}

			Assert::AreEqual(result_list.size(), 4u);
		}

		TEST_METHOD(Reference) {
			using Entropy::Hecate::Check;

			Modifier t(5);
			Check::Result res(10, 10, 10, 5, { t });

			Assert::AreEqual(res.begin()->modifier.Value(), 5);
			Assert::AreEqual(res.begin()->current, 5);

			t.Raw() = 10;
			Assert::AreEqual(res.begin()->modifier.Value(), 10);
			Assert::AreEqual(res.begin()->current, 5);
		}
	};
}