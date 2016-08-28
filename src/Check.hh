/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHECK_INC
#	define ENTROPY_HECATE_CHECK_INC

#	include <memory>
#	include <list>
#	include <initializer_list>

#	include "Modifier.hh"

#	ifndef ENTROPY_HECATE_DEFAULT_LUCK
#		define ENTROPY_HECATE_DEFAULT_LUCK 5
#	endif

	namespace Entropy
	{
		namespace Hecate
		{
			class Check
			{
				public:
					class Result
					{
						private:
							struct result_modifier
							{
								unsigned short current;
								std::shared_ptr<Modifier> modifier;
							};
						public:
							Result(const int, const unsigned short, const std::list<std::shared_ptr<Modifier>> &);
							int Value() const;
							unsigned short Luck() const;
							std::list<result_modifier>::iterator begin();
							std::list<result_modifier>::iterator end();
						private:
							int _value;
							unsigned short _luck;
							std::list<result_modifier> _modifiers;
					};
				public:
					Check(std::initializer_list<std::shared_ptr<Modifier>>);
					Check(unsigned short &, std::initializer_list<std::shared_ptr<Modifier>>);
					template<typename ...mods>
					Result operator () (const mods &...) const;
				private:
					static unsigned short default_luck;
					std::list<std::shared_ptr<Modifier>> _modifiers;
					unsigned short &_luck;
			};
		}
	}

#	include "Check.impl.hh"

#endif
