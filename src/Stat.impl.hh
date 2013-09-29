/*	Copyright 2013 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_HECATE_STAT_IMPL
#	define ENTROPY_HECATE_STAT_IMPL

#	include "Stat.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename tag, typename PercentageType> Stat<tag, PercentageType>::Stat() = default;
			template<typename tag, typename PercentageType> Stat<tag, PercentageType>::Stat(const Stat<tag, PercentageType> &) = default;
			template<typename tag, typename PercentageType> Stat<tag, PercentageType>::Stat(Stat<tag, PercentageType> &&) = default;
			template<typename tag, typename PercentageType> Stat<tag, PercentageType>::~Stat() = default;
			template<typename tag, typename PercentageType> Stat<tag, PercentageType> &Stat<tag, PercentageType>::operator = (const Stat<tag, PercentageType> &) = default;

			template<typename tag, typename PercentageType>
			Stat<tag, PercentageType>::Stat(const Percentage<PercentageType> &o)
				: Percentage<PercentageType>(o)
			{}

			template<typename tag, typename PercentageType>
			Stat<tag, PercentageType>::Stat(Percentage<PercentageType> &&o)
				: Percentage<PercentageType>(o)
			{}
		}
	}

#endif
