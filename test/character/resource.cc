/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "Resource.hh"

using namespace std;
using namespace testing;
using namespace Entropy::Hecate;

namespace {
	struct Ht_tag{}; using Ht = Stat<Ht_tag, Linear<2>>;
	struct Health_tag{}; using Health = Resource<Health_tag, Linear<10>, Linear<1>, Ht>;

	TEST(Resource, Create) {
		Ht ht = 10;

		Health hp(0, ht);

		EXPECT_EQ(hp.Current(), 100);
		EXPECT_EQ(hp.Max(), 100);
		EXPECT_EQ(hp.Value(), 100);
		EXPECT_EQ(hp.Raw(), 0);
		EXPECT_EQ(hp.Cost(), 0);

		hp.Current() = 0;
		EXPECT_EQ(hp.Current(), 0);
		EXPECT_EQ(hp.Max(), 100);
		EXPECT_EQ(hp.Value(), 100);
		EXPECT_EQ(hp.Raw(), 0);
		EXPECT_EQ(hp.Cost(), 0);
	}
}
