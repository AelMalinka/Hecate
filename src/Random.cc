/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Random.hh"

using namespace Entropy::Hecate::detail;
using namespace std;

pcg_extras::seed_seq_from<random_device> Random::_seed;
pcg32 Random::Generator(_seed);
uniform_int_distribution<unsigned short> Random::Distribution(0, 99);
function<unsigned short()> Entropy::Hecate::Roll(bind(Random::Distribution, Random::Generator));
