/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_TEMPLATE_INC
#	define ENTROPY_HECATE_TEMPLATE_INC

#	include <memory>
#	include <vector>

#	include "Percent.hh"
#	include "Trait.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename Character>
			class Template
			{
				public:
					class Holder
					{
						public:
							virtual void Add(Character &) const = 0;
							virtual void Remove(Character &) const = 0;
							virtual CostType Cost() const = 0;
					};
				public:
					Template(const std::string &, const std::vector<std::shared_ptr<Holder>> &);
					Template(const Template<Character> &);
					Template(Template<Character> &&);
					~Template();
					const std::string &Name() const;
					CostType Cost() const;
					void Add(Character &) const;
					void Remove(Character &) const;
					std::size_t size() const;
					auto begin() const;
					auto end() const;
				private:
					std::string _name;
					std::vector<std::shared_ptr<Holder>> _values;
			};

			template<typename Character, typename Skill>
			class SkillHolder :
				public Template<Character>::Holder
			{
				public:
					SkillHolder(const Skill &);
					SkillHolder(const SkillHolder<Character, Skill> &);
					SkillHolder(SkillHolder<Character, Skill> &&);
					~SkillHolder();
					void Add(Character &) const;
					void Remove(Character &) const;
					CostType Cost() const;
				private:
					Skill _value;
			};

			template<typename Character>
			class TraitHolder :
				public Template<Character>::Holder
			{
				public:
					TraitHolder(const Trait<Character> &);
					TraitHolder(const TraitHolder<Character> &);
					TraitHolder(TraitHolder<Character> &&);
					~TraitHolder();
					void Add(Character &) const;
					void Remove(Character &) const;
					CostType Cost() const;
				private:
					Trait<Character> _value;
			};
		}
	}

#	include "Template.impl.hh"

#endif
