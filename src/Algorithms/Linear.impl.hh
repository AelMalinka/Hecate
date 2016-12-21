/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_ALGORITHMS_LINEAR_IMPL
#	define ENTROPY_HECATE_ALGORITHMS_LINEAR_IMPL

	namespace Entropy
	{
		namespace Hecate
		{
			template<CostType Multiplier>
			CostType Linear<Multiplier>::operator () (const PercentType val)
			{
				return val * Multiplier;
			}
		}
	}

#endif
