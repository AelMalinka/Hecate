/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_SKILL_INC
#	define ENTROPY_HECATE_SKILL_INC

#	include "Stat.hh"

#	ifndef ENTROPY_HECATE_DEFINE_SKILL
#		define ENTROPY_HECATE_DEFINE_SKILL(name, ...) struct name ## _tag {}; typedef Skill<name ## _tag,  __VA_ARGS__> name
#	endif

	namespace Entropy
	{
		namespace Hecate
		{
			using std::tuple;

			template<
				typename tag,
				typename ...skills
			>
			class Skill
			{
				public:
					template<typename ...Skills>
					Skill(const unsigned short, Skills &...);
					~Skill();
					unsigned short Value() const;
					void setValue(const unsigned short);
				private:
					unsigned short _value;
					tuple<skills &...> _base_skills;
			};
		}
	}

#	include "Skill.impl.hh"

#endif
