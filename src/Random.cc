/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Random.hh"

#ifdef HAVE_CONFIG_H
#	include "config.h"
#endif

#ifndef HAVE___ATTRIBUTE__
#	define __attribute__(x)
#endif

#include <random>
#include "pcg_random.hpp"

using namespace Entropy::Hecate;
using namespace std;

pcg_extras::seed_seq_from<random_device> _seed;
pcg32 _generator(_seed);
uniform_int_distribution<PercentType> _distribution(0, 99);

function<PercentType()> Entropy::Hecate::Roll(bind(_distribution, _generator));
