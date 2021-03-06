/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include <random>
#include <functional>
#include <gtest/gtest.h>

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#ifndef HAVE___ATTRIBUTE__
#	define __attribute__(x)
#endif

#include <pcg_random.hpp>

using namespace std;
using namespace testing;

namespace {
	// 2016-04-26 AMR TODO: statistically analyze rng
	TEST(PCG, Generate) {
		pcg_extras::seed_seq_from<random_device> seed_source;
		pcg32 rng(seed_source);
		uniform_int_distribution<unsigned short> dist(0, 99);

		auto roll = bind(dist, rng);

		for(auto x = 0; x < 100000; x++)
			roll();
	}
}
