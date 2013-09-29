/*	Copyright 2013 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
	Stat
*/

#if !defined ENTROPY_HECATE_STAT_INC
#	define ENTROPY_HECATE_STAT_INC

#	include "Percentage.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<
				typename tag,
				typename PercentageType = unsigned short
			>
			class Stat :
				public Percentage<PercentageType>
			{
				public:
					Stat();
					Stat(const Stat<tag, PercentageType> &);
					Stat(Stat<tag, PercentageType> &&);
					Stat(const Percentage<PercentageType> &);
					Stat(Percentage<PercentageType> &&);
					virtual ~Stat();
					Stat<tag, PercentageType> &operator = (const Stat<tag, PercentageType> &);
			};
		}
	}

#	include "Stat.impl.hh"

#endif
