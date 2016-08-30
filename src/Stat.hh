/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_STAT_INC
#	define ENTROPY_HECATE_STAT_INC

#	ifndef ENTROPY_HECATE_DEFINE_STAT
#		define ENTROPY_HECATE_DEFINE_STAT(name) struct name ## _tag {}; typedef ::Entropy::Hecate::Stat<name ## _tag> name
#	endif

	namespace Entropy
	{
		namespace Hecate
		{
			template<
				typename tag
			>
			class Stat
			{
				public:
					Stat();
					Stat(const unsigned short);
					~Stat();
					unsigned short Value() const;
					unsigned short &Raw();
				private:
					unsigned short _value;
			};
		}
	}

#	include "Stat.impl.hh"

#endif
