/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Random.hh"

using namespace Entropy::Hecate;
using namespace testing;
using namespace std;

namespace {
	TEST(Random, Roll) {
		for(auto x = 0; x < 10000; x++) {
			EXPECT_GE(Roll(), 0);
			EXPECT_LT(Roll(), 100);
		}
	}
}
