/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_STAT_IMPL
#	define ENTROPY_HECATE_STAT_IMPL

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename tag>
			Stat<tag>::Stat()
				: _value(0)
			{}

			template<typename tag>
			Stat<tag>::Stat(const unsigned short v)
				: _value(v)
			{}

			template<typename tag> Stat<tag>::~Stat() = default;

			template<typename tag>
			unsigned short Stat<tag>::Value() const
			{
				return _value;
			}

			template<typename tag>
			unsigned short &Stat<tag>::Raw()
			{
				return _value;
			}
		}
	}

#endif
