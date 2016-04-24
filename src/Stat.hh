/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_STAT_INC
#	define ENTROPY_HECATE_STAT_INC

#	ifndef ENTROPY_HECATE_DEFINE_STAT
#		define ENTROPY_HECATE_DEFINE_STAT(name) struct name ## _tag {}; typedef Stat<name ## _tag> name;
#	endif

	namespace Entropy
	{
		namespace Hecate
		{
			template<
				typename tag,
				typename type = unsigned short
			>
			class Stat
			{
				public:
					Stat();
					Stat(const type &);
					~Stat();
					type &Value();
					const type &Value() const;
				private:
					type _value;
			};
		}
	}

#	include "Stat.impl.hh"

#endif
