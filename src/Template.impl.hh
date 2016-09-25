/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_TEMPLATE_IMPL
#	define ENTROPY_HECATE_TEMPLATE_IMPL

#	include "Template.hh"
#	include "Trait.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename Character>
			Template<Character>::Template(const std::string &name, const std::vector<std::shared_ptr<Holder>> &v)
				: _name(name), _values(v)
			{}

			template<typename Character> Template<Character>::Template(const Template<Character> &) = default;
			template<typename Character> Template<Character>::Template(Template<Character> &&) = default;
			template<typename Character> Template<Character>::~Template() = default;

			template<typename Character>
			const std::string &Template<Character>::Name() const
			{
				return _name;
			}

			template<typename Character>
			CostType Template<Character>::Cost() const
			{
				CostType ret = 0;

				for(auto &v : _values) {
					ret += v->Cost();
				}

				return ret;
			}

			template<typename Character>
			void Template<Character>::Add(Character &c) const
			{
				for(auto &v : _values) {
					v->Add(c);
				}
			}

			template<typename Character>
			void Template<Character>::Remove(Character &c) const
			{
				for(auto &v : _values) {
					v->Remove(c);
				}
			}

			template<typename Character>
			std::size_t Template<Character>::size() const
			{
				return _values.size();
			}

			template<typename Character>
			auto Template<Character>::begin() const
			{
				return _values.begin();
			}

			template<typename Character>
			auto Template<Character>::end() const
			{
				return _values.end();
			}

			template<typename Character, typename Skill>
			SkillHolder<Character, Skill>::SkillHolder(const Skill &v)
				: _value(v)
			{}

			template<typename Character, typename Skill> SkillHolder<Character, Skill>::SkillHolder(const SkillHolder<Character, Skill> &) = default;
			template<typename Character, typename Skill> SkillHolder<Character, Skill>::SkillHolder(SkillHolder<Character, Skill> &&) = default;
			template<typename Character, typename Skill> SkillHolder<Character, Skill>::~SkillHolder() = default;

			template<typename Character, typename Skill>
			void SkillHolder<Character, Skill>::Add(Character &c) const
			{
				using namespace std;

				Skill temp(_value);
				c.get(temp).Raw() += _value.Raw();
			}

			template<typename Character, typename Skill>
			void SkillHolder<Character, Skill>::Remove(Character &c) const
			{
				Skill temp(_value);
				c.get(temp).Raw() -= _value.Raw();
			}

			template<typename Character, typename Skill>
			CostType SkillHolder<Character, Skill>::Cost() const
			{
				return _value.Cost();
			}

			template<typename Character>
			TraitHolder<Character>::TraitHolder(const Trait<Character> &v)
				: _value(v)
			{}

			template<typename Character> TraitHolder<Character>::TraitHolder(const TraitHolder<Character> &) = default;
			template<typename Character> TraitHolder<Character>::TraitHolder(TraitHolder<Character> &&) = default;
			template<typename Character> TraitHolder<Character>::~TraitHolder() = default;

			template<typename Character>
			void TraitHolder<Character>::Add(Character &c) const
			{
				c.Add(_value);
			}

			template<typename Character>
			void TraitHolder<Character>::Remove(Character &) const
			{
			}

			template<typename Character>
			CostType TraitHolder<Character>::Cost() const
			{
				return _value.Cost();
			}
		}
	}

#endif
