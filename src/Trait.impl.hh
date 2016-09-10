/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_TRAIT_IMPL
#	define ENTROPY_HECATE_TRAIT_IMPL

#	include "Trait.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename Character>
			Trait<Character>::Trait()
				: _func(), _name(), _cost(0)
			{}

			template<typename Character>
			Trait<Character>::Trait(const std::string &name, const CostType cost, const std::function<void(Event &, Character & )> &func)
				: _func(func), _name(name), _cost(cost)
			{}

			template<typename Character>
			template<typename U>
			Trait<Character>::Trait(const Trait<U> &o)
				: _func(o.Function()), _name(o.Name()), _cost(o.Cost())
			{}

			template<typename Character>
			void Trait<Character>::operator () (Event &ev, Character &ch)
			{
				if(_func)
					_func(ev, ch);
			}

			template<typename Character>
			const std::string &Trait<Character>::Name() const
			{
				return _name;
			}

			template<typename Character>
			CostType Trait<Character>::Cost() const
			{
				return _cost;
			}
		}
	}

#endif
