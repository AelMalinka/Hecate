/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHARACTER_IMPL
#	define ENTROPY_HECATE_CHARACTER_IMPL

#	include "Character.hh"
#	include "Trait.hh"

#	include <typeindex>
#	include <type_traits>

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename stats>
			template<typename ...sl>
			Character<stats>::Character(const sl &... s)
				: _luck(ENTROPY_HECATE_DEFAULT_LUCK), _stats(s...), _traits()
			{}

			template<typename stats> Character<stats>::~Character() = default;

			template<typename stats>
			void Character<stats>::operator () (Event &ev)
			{
				for(auto &trait : _traits) {
					trait.second(ev, *this);
				}
			}

			template<typename stats>
			void Character<stats>::Add(const Trait<Character<stats>> &trait)
			{
				_traits.insert(make_pair(trait.Name(), trait));
			}

			template<typename stats>
			void Character<stats>::Add(const Template<Character<stats>> &templ)
			{
				_templates.insert(make_pair(templ.Name(), templ));
				templ.Add(*this);
			}

			template<typename stats>
			void Character<stats>::Remove(const Trait<Character<stats>> &trait)
			{
				_traits.erase(trait.Name());
			}

			template<typename stats>
			void Character<stats>::Remove(const Template<Character<stats>> &templ)
			{
				_templates.erase(templ.Name());
				templ.Remove(*this);
			}

			template<typename stats>
			CostType Character<stats>::Cost() const
			{
				CostType ret = 0;

				detail::for_each(_stats, [&ret](auto &x) { ret += x.Cost(); });
				for(auto &i : _skills) {
					ret += i.second->Cost();
				}
				for(auto &t : _traits) {
					ret += t.second.Cost();
				}

				return ret;
			}

			template<typename stats>
			stats &Character<stats>::Stats()
			{
				return _stats;
			}

			template<typename stats>
			const stats &Character<stats>::Stats() const
			{
				return _stats;
			}

			template<typename stats>
			template<typename tag, typename CostF>
			Stat<tag, CostF> &Character<stats>::get(Stat<tag, CostF> &s)
			{
				using std::get;
				using std::remove_reference;

				s = get<typename remove_reference<decltype(s)>::type>(_stats);

				return get<typename remove_reference<decltype(s)>::type>(_stats);
			}

			template<typename stats>
			template<typename tag, typename CostF>
			const Stat<tag, CostF> &Character<stats>::get(Stat<tag, CostF> &s) const
			{
				using std::get;
				using std::remove_reference;

				s = get<typename remove_reference<decltype(s)>::type>(_stats);

				return get<typename remove_reference<decltype(s)>::type>(_stats);
			}

			template<typename stats>
			template<typename tag, typename CostF, typename ...sl>
			Skill<tag, CostF, sl...> &Character<stats>::set(Skill<tag, CostF, sl...> &s)
			{
				using std::dynamic_pointer_cast;
				using std::make_shared;

				_skills[typeid(s)] = make_shared<Skill<tag, CostF, sl...>>(s);

				return *dynamic_pointer_cast<Skill<tag, CostF, sl...>>(_skills[typeid(s)]);
			}

			template<typename stats>
			template<typename tag, typename CostF, typename ...sl>
			Skill<tag, CostF, sl...> &Character<stats>::get(Skill<tag, CostF, sl...> &s)
			{
				using std::dynamic_pointer_cast;
				using std::make_shared;

				if(_skills.find(typeid(s)) != _skills.end())
					s = *dynamic_pointer_cast<Skill<tag, CostF, sl...>>(_skills[typeid(s)]);
				else
					_skills[typeid(s)] = make_shared<Skill<tag, CostF, sl...>>(s);

				return *dynamic_pointer_cast<Skill<tag, CostF, sl...>>(_skills[typeid(s)]);
			}

			template<typename stats>
			template<typename tag, typename CostF, typename ...sl>
			Skill<tag, CostF, sl...> Character<stats>::get(Skill<tag, CostF, sl...> &s) const
			{
				using std::dynamic_pointer_cast;

				if(_skills.find(typeid(s)) != _skills.end())
					s = dynamic_pointer_cast<Skill<tag, CostF, sl...>>(*_skills.find(typeid(s)));

				return s;
			}

			template<typename stats>
			template<typename ...Mods>
			Check Character<stats>::_check(Mods ...mods)
			{
				return Check(_luck, {mods...});
			}
		}
	}

#endif
