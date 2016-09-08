/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#include "Random.hh"

using namespace Entropy::Hecate;
using namespace std;

pcg_extras::seed_seq_from<random_device> detail::Random::_seed;
pcg32 detail::Random::Generator(_seed);
uniform_int_distribution<PercentType> detail::Random::Distribution(0, 99);
function<PercentType()> Entropy::Hecate::Roll(bind(detail::Random::Distribution, detail::Random::Generator));
