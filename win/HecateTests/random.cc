/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

namespace Tests
{
	using Entropy::Hecate::Roll;

	TEST_CLASS(Random) {
		TEST_METHOD(RollMethod) {
			for (auto x = 0; x < 10000; x++) {
				Assert::IsTrue(Roll() >= 0);
				Assert::IsTrue(Roll() < 100);
			}
		}

		TEST_METHOD(PCG) {
			pcg_extras::seed_seq_from<random_device> seed_source;
			pcg32 rng(seed_source);
			uniform_int_distribution<unsigned short> dist(0, 99);

			auto roll = bind(dist, rng);

			for (auto x = 0; x < 100000; x++)
				roll();
		}
	};
}