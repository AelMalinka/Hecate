/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHARACTER_INC
#	define ENTROPY_HECATE_CHARACTER_INC

#	include "Skill.hh"
#	include "Check.hh"
#	include "Trait.hh"

#	include <typeindex>
#	include <unordered_map>
#	include <map>

#	ifndef ENTROPY_HECATE_DEFINE_CHARACTER
#		define ENTROPY_HECATE_DEFINE_CHARACTER(...) typedef ::Entropy::Hecate::Character<::Entropy::Hecate::tuple<__VA_ARGS__>> BaseCharacter
#	endif

#	ifndef ENTROPY_HECATE_STAT_ACCESSOR
#		define ENTROPY_HECATE_STAT_ACCESSOR(NAME, STAT) \
			STAT &NAME() { return ::std::get<STAT>(Stats()); } \
			const STAT &NAME() const { return ::std::get<STAT>(Stats()); }
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
					CostType Cost() const;
					void Add(const Trait<Character<stats>> &);
					void operator () (Event &);
				public:
					stats &Stats();
					const stats &Stats() const;
					template<typename tag, CostType CostPer>
					Stat<tag, CostPer> &get(Stat<tag, CostPer> &);
					template<typename tag, CostType CostPer>
					const Stat<tag, CostPer> &get(Stat<tag, CostPer> &) const;
					template<typename tag, CostType CostPer, typename ...sl>
					Skill<tag, CostPer, sl...> &set(Skill<tag, CostPer, sl...> &);
					template<typename tag, CostType CostPer, typename ...sl>
					Skill<tag, CostPer, sl...> &get(Skill<tag, CostPer, sl...> &);
					template<typename tag, CostType CostPer, typename ...sl>
					Skill<tag, CostPer, sl...> get(Skill<tag, CostPer, sl...> &) const;
				protected:
					template<typename ...Mods>
					Check _check(Mods ...mods);
					PercentType _luck;
				private:
					stats _stats;
					std::unordered_map<std::type_index, std::shared_ptr<Percent>> _skills;
					std::map<std::string, Trait<Character<stats>>> _traits;
			};
		}
	}

#	include "Character.impl.hh"

#endif
