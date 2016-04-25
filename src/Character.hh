/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHARACTER_INC
#	define ENTROPY_HECATE_CHARACTER_INC

#	include "Skill.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<
				typename Stats
			>
			class Character
			{
				public:
					template<typename ...stats>
					Character(const stats & ...);
					virtual ~Character();
					template<typename tag, typename type = unsigned short>
					Stat<tag, type> &get(Stat<tag, type> &s);
				private:
					Stats _stats;
			};
		}
	}

#	include "Character.impl.hh"

#endif
