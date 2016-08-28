/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHECK_IMPL
#	define ENTROPY_HECATE_CHECK_IMPL

#	include "Random.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename ...Mods>
			Check::Result Check::operator () (const Mods &... mods) const
			{
				int chance = 0; 
				for(auto &modifier : _modifiers)
				{
					if(modifier->Negative())
						chance -= modifier->Value();
					else
						chance += modifier->Value();
				}

				std::list<std::shared_ptr<Modifier>> t{mods...};
				for(auto &modifier : t)
				{
					if(modifier->Negative())
						chance -= modifier->Value();
					else
						chance += modifier->Value();
				}

				if(chance > 100 - _luck)
					chance = 100 - _luck;
				if(chance < default_luck)
					chance = default_luck;

				int value = chance - Roll();
				Result ret(value, _luck, _modifiers);

				return ret;
			}
		}
	}

#endif
