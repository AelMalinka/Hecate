/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_MODIFIER_INC
#	define ENTROPY_HECATE_MODIFIER_INC

#	include <string>
#	include <iostream>

	namespace Entropy
	{
		namespace Hecate
		{
			struct negative_t {};
			extern const negative_t negative;

			class BaseModifier
			{
				public:
					BaseModifier(const std::string &);
					BaseModifier(const std::string &, const negative_t &);
					BaseModifier(const BaseModifier &);
					virtual ~BaseModifier();
					const std::string &Reason() const;
					const bool &Negative() const;
					virtual unsigned short &Value() = 0;
					virtual const unsigned short &Value() const = 0;
				private:
					std::string _reason;
					bool _negate;
			};

			template<
				typename T,
				typename = void
			>
			class Modifier :
				public BaseModifier
			{};

			template<typename charT>
			std::basic_ostream<charT> &operator << (std::basic_ostream<charT> &, const BaseModifier &);

			template<typename T>
			Modifier<T> make_modifier(T &, const std::string &);
			template<typename T>
			Modifier<T> make_modifier(T &, const std::string &, const negative_t &);

			Modifier<unsigned short> make_modifier(unsigned short, const std::string &);
			Modifier<unsigned short> make_modifier(unsigned short, const std::string &, const negative_t &);
		}
	}

#	include "Modifier.impl.hh"

#endif
