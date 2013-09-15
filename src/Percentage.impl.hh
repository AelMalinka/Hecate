/*	Copyright 2012 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
*/

#if !defined ENTROPY_HECATE_PERCENTAGE_IMPL
#	define ENTROPY_HECATE_PERCENTAGE_IMPL

#	include "Percentage.hh"

#	include <utility>

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename PercentageType>
			Percentage<PercentageType>::Percentage()
				: _val(0)
			{}

			template<typename PercentageType> Percentage<PercentageType>::Percentage(const Percentage<PercentageType> &) = default;
			template<typename PercentageType> Percentage<PercentageType>::Percentage(Percentage<PercentageType> &&) = default;
			template<typename PercentageType> Percentage<PercentageType>::~Percentage() = default;

			template<typename PercentageType>
			Percentage<PercentageType>::Percentage(const PercentageType &o)
				: _val(o)
			{}

			template<typename PercentageType>
			Percentage<PercentageType>::Percentage(PercentageType &&o)
				: _val(std::move(o))
			{}

			template<typename PercentageType> Percentage<PercentageType> &Percentage<PercentageType>::operator = (const Percentage<PercentageType> &) = default;

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator = (const PercentageType &o)
			{
				_val = o;
				return *this;
			}

			template<typename PercentageType>
			bool Percentage<PercentageType>::operator < (const Percentage<PercentageType> &o) const
			{
				return _val < o._val;
			}

			template<typename PercentageType>
			bool Percentage<PercentageType>::operator == (const Percentage<PercentageType> &o) const
			{
				return _val == o._val;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator ++()
			{
				++_val;
				return *this;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator --()
			{
				--_val;
				return *this;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator +=(const Percentage<PercentageType> &o)
			{
				_val += o._val;
				return *this;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator -=(const Percentage<PercentageType> &o)
			{
				_val -= o._val;
				return *this;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator *=(const Percentage<PercentageType> &o)
			{
				_val *= o._val;
				return *this;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator /=(const Percentage<PercentageType> &o)
			{
				_val /= o._val;
				return *this;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator %=(const Percentage<PercentageType> &o)
			{
				_val %= o._val;
				return *this;
			}

			template<typename PercentageType>
			bool Percentage<PercentageType>::operator < (const PercentageType &o) const
			{
				return _val < o;
			}

			template<typename PercentageType>
			bool Percentage<PercentageType>::operator == (const PercentageType &o) const
			{
				return _val == o;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator +=(const PercentageType &o)
			{
				_val += o;
				return *this;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator -=(const PercentageType &o)
			{
				_val -= o;
				return *this;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator *=(const PercentageType &o)
			{
				_val *= o;
				return *this;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator /=(const PercentageType &o)
			{
				_val /= o;
				return *this;
			}

			template<typename PercentageType>
			Percentage<PercentageType> &Percentage<PercentageType>::operator %=(const PercentageType &o)
			{
				_val %= o;
				return *this;
			}
		}
	}

#endif
