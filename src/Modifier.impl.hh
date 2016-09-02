/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_MODIFIER_IMPL
#	define ENTROPY_HECATE_MODIFIER_IMPL

#	include "Modifier.hh"

	namespace Entropy
	{
		namespace Hecate
		{
			class Check;

			namespace detail
			{
				template<typename T>
				ModifierHolder<T>::ModifierHolder(T &t)
					: _value(&t), _clean(false)
				{}

				template<typename T>
				ModifierHolder<T>::ModifierHolder(T &&t)
					: _value(new T(t)), _clean(true)
				{}

				template<typename T>
				ModifierHolder<T>::~ModifierHolder()
				{
					if(_clean)
						delete _value;
				}

				template<typename T>
				ModifierType ModifierHolder<T>::Value() const
				{
					return _value->Value();
				}

				template<typename T>
				ModifierType &ModifierHolder<T>::Raw()
				{
					return reinterpret_cast<ModifierType &>(_value->Raw());
				}

				template<>
				class ModifierHolder<ModifierType> :
					public ModifierHolderBase
				{
					public:
						ModifierHolder(ModifierType &);
						ModifierHolder(ModifierType &&);
						~ModifierHolder();
						ModifierType Value() const;
						ModifierType &Raw();
					private:
						ModifierType *_value;
						bool _clean;
				};

				template<>
				class ModifierHolder<Percent> :
					public ModifierHolderBase
				{
					public:
						ModifierHolder(Percent &);
						ModifierHolder(Percent &&);
						~ModifierHolder();
						ModifierType Value() const;
						ModifierType &Raw();
					private:
						Percent *_value;
						bool _clean;
				};

				template<>
				class ModifierHolder<Check> :
					public ModifierHolderBase
				{
					public:
						ModifierHolder(Check &);
						ModifierHolder(Check &&);
						~ModifierHolder();
						ModifierType Value() const;
						ModifierType &Raw();
					private:
						Check *_value;
						bool _clean;
				};
			}

			template<typename T>
			Modifier::Modifier(T &t, const std::string &r, const detail::negative_t &p)
				: _value(std::make_shared<detail::ModifierHolder<T>>(t)), _reason(r), _negate(p)
			{}

			template<typename T>
			Modifier::Modifier(T &&t, const std::string &r, const detail::negative_t &p)
				: _value(std::make_shared<detail::ModifierHolder<T>>(std::move(t))), _reason(r), _negate(p)
			{}
		}
	}

#	include "Check.hh"

#endif
