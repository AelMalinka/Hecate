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
			class ModifierImpl<T, typename std::enable_if<std::is_class<T>::value>::type> :
				public Modifier
			{
				public:
					ModifierImpl(T &t, const std::string &s)
						: Modifier(s), _value(t)
					{}
					ModifierImpl(T &t, const std::string &s, const negative_t &n)
						: Modifier(s, n), _value(t)
					{}
					ModifierImpl(const ModifierImpl<T, typename std::enable_if<std::is_class<T>::value>::type> &) = default;
					unsigned short Value() const
					{
						return _value.Value();
					}
				private:
					T &_value;
			};

			template<>
			class ModifierImpl<unsigned short, void> :
				public Modifier
			{
				public:
					ModifierImpl(unsigned short t, const std::string &s)
						: Modifier(s), _value(t)
					{}
					ModifierImpl(unsigned short t, const std::string &s, const negative_t &n)
						: Modifier(s, n), _value(t)
					{}
					ModifierImpl(const ModifierImpl<unsigned short, void> &) = default;
					unsigned short Value() const
					{
						return _value;
					}
					void setValue(unsigned short v)
					{
						_value = v;
					}
				private:
					unsigned short _value;
			};

			template<typename charT>
			std::basic_ostream<charT> &operator << (std::basic_ostream<charT> &os, const Modifier &m)
			{
				os << m.Reason() << ": " << (m.Negative() ? "-" : "") << m.Value();
				return os;
			}

			template<typename charT>
			std::basic_ostream<charT> &operator << (std::basic_ostream<charT> &os, const std::shared_ptr<Modifier> &m)
			{
				os << *m;
				return os;
			}

			template<typename T>
			std::shared_ptr<Modifier> make_modifier(T &v, const std::string &r)
			{
				return std::make_shared<ModifierImpl<T>>(v, r);
			}

			template<typename T>
			std::shared_ptr<Modifier> make_modifier(T &v, const std::string &r, const negative_t &n)
			{
				return std::make_shared<ModifierImpl<T>>(v, r, n);
			}
		}
	}

#endif
