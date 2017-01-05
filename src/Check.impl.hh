/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHECK_IMPL
#	define ENTROPY_HECATE_CHECK_IMPL

#	include "Check.hh"

#	include "Random.hh"

#	include <utility>

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename ...Mods>
			Check::Result Check::operator () (const Mods &... mods) const
			{
				PercentType chance = 0; 
				std::vector<Modifier> t{mods...};
				std::vector<std::shared_ptr<Modifier>> modifiers(_modifiers);

				for(auto &i : t) {
					modifiers.push_back(std::make_shared<Modifier>(i));
				}

				for(auto &i : modifiers) {
					chance += i->Value();
				}

				if(chance > 100 - _luck)
					chance = 100 - _luck;
				if(chance < default_luck)
					chance = default_luck;

				// 2016-09-02 AMR NOTE: success if under not equal to the roll in question
				PercentType roll = Roll();
				PercentType value = chance - roll - 1;
				Result ret(value, roll, _luck, modifiers);

				for(auto &&f : _callbacks) {
					f(ret);
				}

				return ret;
			}
		}
	}

#endif
