/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_STAT_IMPL
#	define ENTROPY_HECATE_STAT_IMPL

#	include "Stat.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename tag, CostType CostPer>
			Stat<tag, CostPer>::Stat()
				: Percent(0)
			{}

			template<typename tag, CostType CostPer>
			Stat<tag, CostPer>::Stat(const PercentType v)
				: Percent(v)
			{}

			template<typename tag, CostType CostPer> Stat<tag, CostPer>::~Stat() = default;

			template<typename tag, CostType CostPer>
			CostType Stat<tag, CostPer>::Cost() const
			{
				return Raw() * CostPer;
			}
		}
	}

#endif
