/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHARACTER_INC
#	define ENTROPY_HECATE_CHARACTER_INC

#	include "Skill.hh"

#	include <typeindex>
#	include <unordered_map>
#	include <boost/any.hpp>

#	ifndef ENTROPY_HECATE_DEFINE_CHARACTER
#		define ENTROPY_HECATE_DEFINE_CHARACTER(...) typedef ::Entropy::Hecate::Character<::Entropy::Hecate::tuple<__VA_ARGS__>> BaseCharacter
#	endif

	namespace Entropy
	{
		namespace Hecate
		{
			template<
				typename stats
			>
			class Character
			{
				public:
					template<typename ...sl>
					Character(const sl & ...);
					virtual ~Character();
					stats &Stats();
					const stats &Stats() const;
					template<typename tag>
					Stat<tag> &get(Stat<tag> &);
					template<typename tag>
					const Stat<tag> &get(Stat<tag> &) const;
					template<typename tag, typename ...sl>
					Skill<tag, sl...> &set(Skill<tag, sl...> &);
					template<typename tag, typename ...sl>
					Skill<tag, sl...> &get(Skill<tag, sl...> &);
					template<typename tag, typename ...sl>
					const Skill<tag, sl...> &get(Skill<tag, sl...> &) const;
				private:
					stats _stats;
					std::unordered_map<std::type_index, boost::any> _skills;
			};
		}
	}

#	include "Character.impl.hh"

#endif
