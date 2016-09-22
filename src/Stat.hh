/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_STAT_INC
#	define ENTROPY_HECATE_STAT_INC

#	include "Percent.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<
				typename tag,
				CostType CostPer
			>
			class Stat :
				public Percent
			{
				public:
					Stat();
					Stat(const PercentType);
					virtual ~Stat();
					PercentType Value() const;
					PercentType &Raw();
					const PercentType &Raw() const;
					CostType Cost() const;
				private:
					PercentType _value;
			};
		}
	}

#	include "Stat.impl.hh"

#endif
