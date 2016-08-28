/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTRPOY_HECATE_EXCEPTION_INC
#	define ENTRPOY_HECATE_EXCEPTION_INC

#	include <Entropy/Exception.hh>

	namespace Entropy
	{
		namespace Hecate
		{
			ENTROPY_EXCEPTION_BASE(Exception, "Hecate Exception");
		}
	}

#endif
