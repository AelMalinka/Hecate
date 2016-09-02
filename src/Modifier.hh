/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_MODIFIER_INC
#	define ENTROPY_HECATE_MODIFIER_INC

#	include <memory>

#	include "Skill.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			namespace detail
			{
				struct negative_t {
					negative_t(const char);
					const char multiplier;
				};

				extern const negative_t positive;

				class ModifierHolderBase
				{
					public:
						virtual ModifierType Value() const = 0;
						virtual ModifierType &Raw() = 0;
				};

				template<typename T>
				class ModifierHolder :
					public ModifierHolderBase
				{
					public:
						ModifierHolder(T &);
						ModifierHolder(T &&);
						~ModifierHolder();
						ModifierType Value() const;
						ModifierType &Raw();
					private:
						T *_value;
						bool _clean;
				};
			}

			extern const detail::negative_t negative;

			class Modifier
			{
				public:
					template<typename T>
					Modifier(T &, const std::string &, const detail::negative_t & = detail::positive);
					template<typename T>
					Modifier(T &&, const std::string &, const detail::negative_t & = detail::positive);
					const std::string &Reason() const;
					ModifierType Value() const;
					ModifierType &Raw();
				private:
					std::shared_ptr<detail::ModifierHolderBase> _value;
					std::string _reason;
					detail::negative_t _negate;
			};
		}
	}

#	include "Modifier.impl.hh"

#endif
