/*	Copyright 2017 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_MODIFIERTYPE_INC
#	define ENTROPY_HECATE_MODIFIERTYPE_INC

#	include <cstddef>

	namespace Entropy
	{
		namespace Hecate
		{
			class ModifierType
			{
				public:
					explicit ModifierType(const bool = false, const std::size_t = 0);
					bool Stacking() const;
					bool operator == (const ModifierType &) const;
					bool operator != (const ModifierType &) const;
					bool operator < (const ModifierType &) const;
				private:
					std::size_t _type;
					bool _stacking;
					static std::size_t _next;
			};

			extern const ModifierType Untyped;
		}
	}

#endif
