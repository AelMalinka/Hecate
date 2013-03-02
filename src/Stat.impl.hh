/*	Copyright 2012 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_HECATE_STAT_IMPL
#	define ENTROPY_HECATE_STAT_IMPL

#	include "Stat.hh"

#	include <utility>

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType>::Stat()
				: _val(0)
			{}

			template<typename stat_tag, typename PercentageType> Stat<stat_tag, PercentageType>::Stat(const Stat<stat_tag, PercentageType> &) = default;
			template<typename stat_tag, typename PercentageType> Stat<stat_tag, PercentageType>::Stat(Stat<stat_tag, PercentageType> &&) = default;
			template<typename stat_tag, typename PercentageType> Stat<stat_tag, PercentageType>::~Stat() = default;

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType>::Stat(const PercentageType &o)
				: _val(o)
			{}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType>::Stat(PercentageType &&o)
				: _val(std::move(o))
			{}

			template<typename stat_tag, typename PercentageType> Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator = (const Stat<stat_tag, PercentageType> &) = default;

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator = (const PercentageType &o)
			{
				_val = o;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			bool Stat<stat_tag, PercentageType>::operator < (const Stat<stat_tag, PercentageType> &o) const
			{
				return _val < o._val;
			}

			template<typename tag1, typename tag2, typename perc1, typename perc2>
			bool operator == (const Stat<tag1, perc1> &, const Stat<tag2, perc2> &)
			{
				return false;
			}

			template<typename stat_tag, typename perc1, typename perc2>
			bool operator == (const Stat<stat_tag, perc1> &a, const Stat<stat_tag, perc2> &b)
			{
				return a._val == b._val;
			}

			template<typename tag1, typename tag2, typename perc1, typename perc2>
			bool operator != (const Stat<tag1, perc1> &, const Stat<tag2, perc2> &)
			{
				return true;
			}

			template<typename stat_tag, typename perc1, typename perc2>
			bool operator != (const Stat<stat_tag, perc1> &a, const Stat<stat_tag, perc2> &b)
			{
				return !operator ==(a, b);
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator ++()
			{
				++_val;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator --()
			{
				--_val;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator +=(const Stat<stat_tag, PercentageType> &o)
			{
				_val += o._val;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator -=(const Stat<stat_tag, PercentageType> &o)
			{
				_val -= o._val;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator *=(const Stat<stat_tag, PercentageType> &o)
			{
				_val *= o._val;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator /=(const Stat<stat_tag, PercentageType> &o)
			{
				_val /= o._val;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator %=(const Stat<stat_tag, PercentageType> &o)
			{
				_val %= o._val;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			bool Stat<stat_tag, PercentageType>::operator < (const PercentageType &o) const
			{
				return _val < o;
			}

			template<typename stat_tag, typename PercentageType>
			bool Stat<stat_tag, PercentageType>::operator == (const PercentageType &o) const
			{
				return _val == o;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator +=(const PercentageType &o)
			{
				_val += o;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator -=(const PercentageType &o)
			{
				_val -= o;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator *=(const PercentageType &o)
			{
				_val *= o;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator /=(const PercentageType &o)
			{
				_val /= o;
				return *this;
			}

			template<typename stat_tag, typename PercentageType>
			Stat<stat_tag, PercentageType> &Stat<stat_tag, PercentageType>::operator %=(const PercentageType &o)
			{
				_val %= o;
				return *this;
			}
		}
	}

#endif
