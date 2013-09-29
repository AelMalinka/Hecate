/*	Copyright 2013 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#include "Stat.hh"
#include "gtest/gtest.h"

using namespace std;
using namespace Entropy::Hecate;
using namespace testing;

struct tag_1 {};
struct tag_2 {};

struct Iq_tag {};
struct Magic_tag {};

TEST(StatTest, Creation) {
	Stat<tag_1> tag1;
	Stat<tag_2> tag2;

	unsigned short d = 12;
	Stat<Iq_tag> iq(d);

	Percentage<> p(d);
	Stat<Magic_tag> magic(p);


	SUCCEED() << "this just needs to compile";
}
