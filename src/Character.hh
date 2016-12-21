/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHARACTER_INC
#	define ENTROPY_HECATE_CHARACTER_INC

#	include "Skill.hh"
#	include "Check.hh"
#	include "Trait.hh"
#	include "Template.hh"

#	include <typeindex>
#	include <unordered_map>
#	include <map>

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
					void Add(const Template<Character<stats>> &);
					void Remove(const Trait<Character<stats>> &);
					void Remove(const Template<Character<stats>> &);
					void operator () (Event &);
				public:
					stats &Stats();
					const stats &Stats() const;
					template<typename tag, typename CostF>
					Stat<tag, CostF> &get(Stat<tag, CostF> &);
					template<typename tag, typename CostF>
					const Stat<tag, CostF> &get(Stat<tag, CostF> &) const;
					template<typename tag, typename CostF, typename ...sl>
					Skill<tag, CostF, sl...> &set(Skill<tag, CostF, sl...> &);
					template<typename tag, typename CostF, typename ...sl>
					Skill<tag, CostF, sl...> &get(Skill<tag, CostF, sl...> &);
					template<typename tag, typename CostF, typename ...sl>
					Skill<tag, CostF, sl...> get(Skill<tag, CostF, sl...> &) const;
				protected:
					template<typename ...Mods>
					Check _check(Mods ...mods);
					PercentType _luck;
				private:
					stats _stats;
					std::unordered_map<std::type_index, std::shared_ptr<Percent>> _skills;
					std::map<std::string, Trait<Character<stats>>> _traits;
					std::map<std::string, Template<Character<stats>>> _templates;
			};
		}
	}

#	include "Character.impl.hh"

#endif
