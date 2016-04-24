/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_SKILL_INC
#	define ENTROPY_HECATE_SKILL_INC

#	include "Stat.hh"

#	ifndef ENTROPY_HECATE_DEFINE_SKILL
#		define ENTROPY_HECATE_DEFINE_SKILL(name, ...) struct name ## _tag {}; typedef Skill<name ## _tag, tuple< __VA_ARGS__ & > > name;
#	endif

	namespace Entropy
	{
		namespace Hecate
		{
			template<
				typename tag,
				typename bases,
				typename type = unsigned short
			>
			class Skill
			{
				public:
					Skill() = delete;
					template<typename ...T>
					Skill(const type &, T & ...);
					~Skill();
					type Value() const;
					void setValue(const type &);
				private:
					bases _base_skills;
					type _value;
			};
		}
	}

#	include "Skill.impl.hh"

#endif
