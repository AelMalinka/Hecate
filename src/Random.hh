/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_RANDOM_INC
#	define ENTROPY_HECATE_RANDOM_INC

#	include <random>
#	include <functional>
#	include "pcg_random.hpp"

	namespace Entropy
	{
		namespace Hecate
		{
			namespace detail
			{
				class Random
				{
					private:
						static pcg_extras::seed_seq_from<std::random_device> _seed;
					public:
						static pcg32 Generator;
						static std::uniform_int_distribution<unsigned short> Distribution;
				};
			}

			extern std::function<unsigned short()> Roll;
		}
	}

#endif
