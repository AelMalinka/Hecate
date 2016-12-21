/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_ALGORITHMS_LINEAR_INC
#	define ENTROPY_HECATE_ALGORITHMS_LINEAR_INC

#	include "../Exception.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<
				CostType Multiplier
			>
			class Linear
			{
				public:
					CostType operator () (const PercentType);
			};
		}
	}

#	include "Linear.impl.hh"

#endif
