/*	Copyright 2012 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_HECATE_STAT_PROTOTYPE_INC
#	define ENTROPY_HECATE_STAT_PROTOTYPE_INC

#	include <string>
#	include <set>

#	include "Entropy/Exception.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			ENTROPY_EXCEPTION_BASE(HecateException, "Hecate Exception");
			ENTROPY_EXCEPTION(InvalidStatPrototype, "Invalid Stat Prototype", HecateException);
			ENTROPY_ERROR_INFO(StatName, std::string);

			class StatPrototype
			{
				public:
					StatPrototype();
					StatPrototype(const std::string &);
					virtual ~StatPrototype();
					bool operator == (const StatPrototype &) const;
					bool operator == (const std::string &) const;
					const std::string &Value() const;
					operator std::string() const;
					static StatPrototype &&create(const std::string &);
					static void clear();
				private:
					const std::string *_name;
					static std::set<std::string> _protos;
			};
		}
	}

#endif
