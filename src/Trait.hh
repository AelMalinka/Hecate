/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_TRAIT_INC
#	define ENTROPY_HECATE_TRAIT_INC

#	include "Exception.hh"
#	include "Event.hh"

#	include <functional>

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename Character>
			class Trait
			{
				public:
					Trait();
					Trait(const std::string &, const CostType, const std::function<void(Event &, Character &)> &);
					Trait(const Trait<Character> &) = default;
					template<typename U>
					Trait(const Trait<U> &);
					Trait(Trait<Character> &&) = default;
					~Trait() = default;
					void operator () (Event &, Character &);
					const std::string &Name() const;
					CostType Cost() const;
					const std::function<void(Event &, Character &)> &Function() const;
					Trait<Character> &operator = (const Trait<Character> &) = default;
				private:
					typedef Trait<Character> Base;
					std::function<void(Event &, Character &)> _func;
					std::string _name;
					CostType _cost;
			};
		}
	}

#	include "Trait.impl.hh"

#endif
