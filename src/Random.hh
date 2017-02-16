/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_RANDOM_INC
#	define ENTROPY_HECATE_RANDOM_INC

#	include "Exception.hh"

#	include <functional>

	namespace Entropy
	{
		namespace Hecate
		{
			extern std::function<PercentType()> Roll;
		}
	}

#endif
