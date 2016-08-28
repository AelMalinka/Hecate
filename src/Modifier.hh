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

			class Modifier
			{
				public:
					Modifier(const std::string &);
					Modifier(const std::string &, const negative_t &);
					Modifier(const Modifier &);
					virtual ~Modifier();
					const std::string &Reason() const;
					const bool &Negative() const;
					virtual unsigned short Value() const = 0;
				private:
					std::string _reason;
					bool _negate;
			};

			template<
				typename T,
				typename = void
			>
			class ModifierImpl :
				public Modifier
			{};

			template<typename charT>
			std::basic_ostream<charT> &operator << (std::basic_ostream<charT> &, const Modifier &);

			template<typename T>
			ModifierImpl<T> make_modifier(T &, const std::string &);
			template<typename T>
			ModifierImpl<T> make_modifier(T &, const std::string &, const negative_t &);

			ModifierImpl<unsigned short> make_modifier(unsigned short, const std::string &);
			ModifierImpl<unsigned short> make_modifier(unsigned short, const std::string &, const negative_t &);
		}
	}

#	include "Modifier.impl.hh"

#endif
