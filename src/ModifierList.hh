/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_MODIFIERLIST_INC
#	define ENTROPY_HECATE_MODIFIERLIST_INC

#	include <map>
#	include <vector>
#	include <initializer_list>

#	include "Modifier.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			class ModifierList
			{
				public:
					ModifierList();
					ModifierList(std::initializer_list<Modifier>);
					explicit ModifierList(const std::vector<Modifier> &);
					PercentType Value() const;
					void Add(const Modifier &);
					std::vector<Modifier> &operator [] (const ModifierType &);
					std::map<ModifierType, std::vector<Modifier>>::iterator begin();
					std::map<ModifierType, std::vector<Modifier>>::iterator end();
					std::size_t size() const;
					const std::vector<Modifier> &operator [] (const ModifierType &) const;
					std::map<ModifierType, std::vector<Modifier>>::const_iterator begin() const;
					std::map<ModifierType, std::vector<Modifier>>::const_iterator end() const;
				private:
					std::map<ModifierType, std::vector<Modifier>> _modifiers;
			};
		}
	}

#endif
