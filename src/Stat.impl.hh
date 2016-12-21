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
			template<typename tag, typename CostF>
			Stat<tag, CostF>::Stat()
				: Percent(0)
			{}

			template<typename tag, typename CostF>
			Stat<tag, CostF>::Stat(const PercentType v)
				: Percent(v)
			{}

			template<typename tag, typename CostF> Stat<tag, CostF>::~Stat() = default;

			template<typename tag, typename CostF>
			CostType Stat<tag, CostF>::Cost() const
			{
				return CostF()(Raw());
			}
		}
	}

#endif
