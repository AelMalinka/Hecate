/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTRPOY_HECATE_EXCEPTION_INC
#	define ENTRPOY_HECATE_EXCEPTION_INC

#	include <Entropy/Exception.hh>

#	ifndef ENTROPY_HECATE_PERCENT_TYPE
#		define ENTROPY_HECATE_PERCENT_TYPE int
#	endif

#	ifndef ENTROPY_HECATE_COST_TYPE
#		define ENTROPY_HECATE_COST_TYPE unsigned int
#	endif

	namespace Entropy
	{
		namespace Hecate
		{
			ENTROPY_EXCEPTION_BASE(Exception, "Hecate Exception");

			typedef ENTROPY_HECATE_PERCENT_TYPE PercentType;
			typedef ENTROPY_HECATE_COST_TYPE CostType;
		}
	}

#endif
