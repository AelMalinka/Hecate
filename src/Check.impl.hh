/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHECK_IMPL
#	define ENTROPY_HECATE_CHECK_IMPL

#	include "Check.hh"

#	include "Random.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename ...Mods>
			Check::Result Check::operator () (const Mods &... mods) const
			{
				int chance = 0; 
				std::list<std::shared_ptr<Modifier>> t{mods...};
				std::list<std::shared_ptr<Modifier>> modifiers(_modifiers);

				for(auto &i : t) {
					modifiers.push_back(i);
				}

				for(auto &i : modifiers) {
					if(i->Negative())
						chance -= i->Value();
					else
						chance += i->Value();
				}

				if(chance > 100 - _luck)
					chance = 100 - _luck;
				if(chance < default_luck)
					chance = default_luck;

				int value = chance - Roll();
				Result ret(value, _luck, modifiers);

				return ret;
			}
		}
	}

#endif
