/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_MODIFIER_INC
#	define ENTROPY_HECATE_MODIFIER_INC

#	include <memory>

#	include "Exception.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			namespace detail
			{
				class negative_t
				{
					public:
						negative_t();
						negative_t(const char);
						char Multiplier() const;
					private:
						char _multiplier;
				};

				extern const negative_t positive;

				class ModifierHolderBase
				{
					public:
						virtual PercentType Value() const = 0;
						virtual PercentType &Raw() = 0;
				};

				template<typename T>
				class ModifierHolder :
					public ModifierHolderBase
				{
					public:
						ModifierHolder(T &);
						ModifierHolder(T &&);
						~ModifierHolder();
						PercentType Value() const;
						PercentType &Raw();
					private:
						T *_value;
						bool _clean;
				};
			}

			extern const detail::negative_t negative;

			class Modifier
			{
				public:
					Modifier();
					template<typename T>
					Modifier(T &, const std::string &, const detail::negative_t & = detail::positive);
					template<typename T>
					Modifier(T &&, const std::string &, const detail::negative_t & = detail::positive);
					const std::string &Reason() const;
					PercentType Value() const;
					PercentType &Raw();
				private:
					std::shared_ptr<detail::ModifierHolderBase> _value;
					std::string _reason;
					detail::negative_t _negate;
			};
		}
	}

#	include "Modifier.impl.hh"

#endif
