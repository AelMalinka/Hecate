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
				: _value(0)
			{}

			template<typename tag, CostType CostPer>
			Stat<tag, CostPer>::Stat(const PercentType v)
				: _value(v)
			{}

			template<typename tag, CostType CostPer> Stat<tag, CostPer>::~Stat() = default;

			template<typename tag, CostType CostPer>
			PercentType Stat<tag, CostPer>::Value() const
			{
				return _value;
			}

			template<typename tag, CostType CostPer>
			PercentType &Stat<tag, CostPer>::Raw()
			{
				return _value;
			}

			template<typename tag, CostType CostPer>
			const PercentType &Stat<tag, CostPer>::Raw() const
			{
				return _value;
			}

			template<typename tag, CostType CostPer>
			CostType Stat<tag, CostPer>::Cost() const
			{
				return _value * CostPer;
			}
		}
	}

#endif
