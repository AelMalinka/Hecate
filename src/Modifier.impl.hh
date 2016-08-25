/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_MODIFIER_IMPL
#	define ENTROPY_HECATE_MODIFIER_IMPL

#	include "Modifier.hh"

#	include <type_traits>

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename T>
			class Modifier<T, typename std::enable_if<std::is_class<T>::value>::type> :
				public BaseModifier
			{
				public:
					Modifier(T &t, const std::string &s)
						: BaseModifier(s), _value(t)
					{}
					Modifier(T &t, const std::string &s, const negative_t &n)
						: BaseModifier(s, n), _value(t)
					{}
					unsigned short &Value()
					{
						return _value.Value();
					}
					const unsigned short &Value() const
					{
						return _value.Value();
					}
				private:
					T &_value;
					std::string _reason;
			};

			template<>
			class Modifier<unsigned short, void> :
				public BaseModifier
			{
				public:
					Modifier(unsigned short t, const std::string &s)
						: BaseModifier(s), _value(t)
					{}
					Modifier(unsigned short t, const std::string &s, const negative_t &n)
						: BaseModifier(s, n), _value(t)
					{}
					unsigned short &Value()
					{
						return _value;
					}
					const unsigned short &Value() const
					{
						return _value;
					}
				private:
					unsigned short _value;
			};

			template<typename charT>
			std::basic_ostream<charT> &operator << (std::basic_ostream<charT> &os, const BaseModifier &m)
			{
				os << m.Reason() << ": " << (m.Negative() ? "-" : "") << m.Value();
				return os;
			}

			template<typename T>
			Modifier<T> make_modifier(T &v, const std::string &r)
			{
				Modifier<T> ret(v, r);
				return ret;
			}

			template<typename T>
			Modifier<T> make_modifier(T &v, const std::string &r, const negative_t &n)
			{
				Modifier<T> ret(v, r, n);
				return ret;
			}
		}
	}

#endif
