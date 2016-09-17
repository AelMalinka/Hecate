/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_PERCENT_INC
#	define ENTROPY_HECATE_PERCENT_INC

#	include "Exception.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			class Percent
			{
				public:
					virtual PercentType Value() const = 0;
					virtual PercentType &Raw() = 0;
					virtual const PercentType &Raw() const = 0;
					virtual CostType Cost() const = 0;
			};
		}
	}

#endif
