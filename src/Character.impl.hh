/*	Copyright 2016 (c) Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Affero General Public License v3
*/

#if !defined ENTROPY_HECATE_CHARACTER_IMPL
#	define ENTROPY_HECATE_CHARACTER_IMPL

#	include <type_traits>

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename Stats>
			template<typename ...stats>
			Character<Stats>::Character(const stats &... s)
				: _stats(s...)
			{}

			template<typename Stats> Character<Stats>::~Character() = default;

			template<typename Stats>
			template<typename tag>
			Stat<tag> &Character<Stats>::get(Stat<tag> &s)
			{
				using std::get;
				using std::remove_reference;

				s = get<typename remove_reference<decltype(s)>::type>(_stats);

				return s;
			}
		}
	}

#endif
