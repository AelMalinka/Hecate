/*	Copyright 2012 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
	Percentage
*/

#if !defined ENTROPY_HECATE_PERCENTAGE_INC
#	define ENTROPY_HECATE_PERCENTAGE_INC

#	include <boost/operators.hpp>

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename PercentageType = unsigned short>
			class Percentage :
				boost::totally_ordered<Percentage<PercentageType>>,
				boost::integer_arithmetic<Percentage<PercentageType>>,
				boost::incrementable<Percentage<PercentageType>>,
				boost::decrementable<Percentage<PercentageType>>,
				boost::less_than_comparable<Percentage<PercentageType>, PercentageType>,
				boost::equality_comparable<Percentage<PercentageType>, PercentageType>,
				boost::integer_arithmetic<Percentage<PercentageType>, PercentageType>
			{
				public:
					Percentage();
					Percentage(const Percentage<PercentageType> &);
					Percentage(Percentage<PercentageType> &&);
					Percentage(const PercentageType &);
					Percentage(PercentageType &&);
					virtual ~Percentage();
					Percentage<PercentageType> &operator = (const Percentage<PercentageType> &);
					Percentage<PercentageType> &operator = (const PercentageType &);
					bool operator < (const Percentage<PercentageType> &) const;
					bool operator == (const Percentage<PercentageType> &) const;
					Percentage<PercentageType> &operator ++();
					Percentage<PercentageType> &operator --();
					Percentage<PercentageType> &operator +=(const Percentage<PercentageType> &);
					Percentage<PercentageType> &operator -=(const Percentage<PercentageType> &);
					Percentage<PercentageType> &operator *=(const Percentage<PercentageType> &);
					Percentage<PercentageType> &operator /=(const Percentage<PercentageType> &);
					Percentage<PercentageType> &operator %=(const Percentage<PercentageType> &);
					bool operator < (const PercentageType &) const;
					bool operator == (const PercentageType &) const;
					Percentage<PercentageType> &operator +=(const PercentageType &);
					Percentage<PercentageType> &operator -=(const PercentageType &);
					Percentage<PercentageType> &operator *=(const PercentageType &);
					Percentage<PercentageType> &operator /=(const PercentageType &);
					Percentage<PercentageType> &operator %=(const PercentageType &);
				protected:
				private:
					PercentageType _val;
			};
		}
	}

#	include "Percentage.impl.hh"

#endif
