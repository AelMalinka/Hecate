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
				PercentType ModifierHolder<T>::Value() const
				{
					return _value->Value();
				}

				template<typename T>
				PercentType &ModifierHolder<T>::Raw()
				{
					return reinterpret_cast<PercentType &>(_value->Raw());
				}

				template<>
				class ModifierHolder<PercentType> :
					public ModifierHolderBase
				{
					public:
						ModifierHolder(PercentType &);
						ModifierHolder(PercentType &&);
						~ModifierHolder();
						PercentType Value() const;
						PercentType &Raw();
					private:
						PercentType *_value;
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
						PercentType Value() const;
						PercentType &Raw();
					private:
						Check *_value;
						bool _clean;
				};
			}

			template<typename T>
			Modifier::Modifier(T &t, const ModifierType &type)
				: _value(std::make_shared<detail::ModifierHolder<T>>(t)), _type(type), _negate(detail::positive)
			{}

			template<typename T>
			Modifier::Modifier(T &&t, const ModifierType &type)
				: _value(std::make_shared<detail::ModifierHolder<T>>(std::move(t))), _type(type), _negate(detail::positive)
			{}

			template<typename T>
			Modifier::Modifier(T &t, const detail::negative_t &p, const ModifierType &type)
				: _value(std::make_shared<detail::ModifierHolder<T>>(t)), _type(type), _negate(p)
			{}

			template<typename T>
			Modifier::Modifier(T &&t, const detail::negative_t &p, const ModifierType &type)
				: _value(std::make_shared<detail::ModifierHolder<T>>(std::move(t))), _type(type), _negate(p)
			{}
		}
	}

#endif
