/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <gtest/gtest.h>
#include "ModifierType.hh"

using namespace std;
using namespace testing;
using namespace Entropy::Hecate;

namespace {
	ModifierType mytype1;
	ModifierType mytype2(true);

	TEST(ModifierType, Create) {
		ModifierType a = Untyped;
		ModifierType b = mytype1;
		ModifierType c = mytype2;
		ModifierType d;
		ModifierType e = Untyped;

		EXPECT_EQ(a, Untyped);
		EXPECT_NE(a, mytype1);
		EXPECT_NE(a, mytype2);
		EXPECT_EQ(a, a);
		EXPECT_NE(a, b);
		EXPECT_NE(a, c);
		EXPECT_NE(a, d);
		EXPECT_EQ(a, e);

		EXPECT_NE(b, Untyped);
		EXPECT_EQ(b, mytype1);
		EXPECT_NE(b, mytype2);
		EXPECT_NE(b, a);
		EXPECT_EQ(b, b);
		EXPECT_NE(b, c);
		EXPECT_NE(b, d);
		EXPECT_NE(b, e);

		EXPECT_NE(c, Untyped);
		EXPECT_NE(c, mytype1);
		EXPECT_EQ(c, mytype2);
		EXPECT_NE(c, a);
		EXPECT_NE(c, b);
		EXPECT_EQ(c, c);
		EXPECT_NE(c, d);
		EXPECT_NE(c, e);

		EXPECT_NE(d, Untyped);
		EXPECT_NE(d, mytype1);
		EXPECT_NE(d, mytype2);
		EXPECT_NE(d, a);
		EXPECT_NE(d, b);
		EXPECT_NE(d, c);
		EXPECT_EQ(d, d);
		EXPECT_NE(d, e);

		EXPECT_EQ(e, Untyped);
		EXPECT_NE(e, mytype1);
		EXPECT_NE(e, mytype2);
		EXPECT_EQ(e, a);
		EXPECT_NE(e, b);
		EXPECT_NE(e, c);
		EXPECT_NE(e, d);
		EXPECT_EQ(e, e);
	}

	TEST(ModifierType, Stacking) {
		ModifierType a = Untyped;
		ModifierType b = mytype1;
		ModifierType c = mytype2;
		ModifierType d;
		ModifierType e = Untyped;

		EXPECT_TRUE(a.Stacking());
		EXPECT_FALSE(b.Stacking());
		EXPECT_TRUE(c.Stacking());
		EXPECT_FALSE(d.Stacking());
		EXPECT_TRUE(e.Stacking());
	}
}
