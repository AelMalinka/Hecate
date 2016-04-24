/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_STAT_IMPL
#	define ENTROPY_HECATE_STAT_IMPL

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename tag, typename type>
			Stat<tag, type>::Stat()
				: _value(0)
			{}

			template<typename tag, typename type>
			Stat<tag, type>::Stat(const type &v)
				: _value(v)
			{}

			template<typename tag, typename type> Stat<tag, type>::~Stat() = default;

			template<typename tag, typename type>
			type &Stat<tag, type>::Value()
			{
				return _value;
			}

			template<typename tag, typename type>
			const type &Stat<tag, type>::Value() const
			{
				return _value;
			}
		}
	}

#endif
