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
			template<
				typename PercentageType = unsigned short
			>
			class Percentage :
				public boost::totally_ordered<Percentage<PercentageType>>,
				public boost::integer_arithmetic<Percentage<PercentageType>>,
				public boost::incrementable<Percentage<PercentageType>>,
				public boost::decrementable<Percentage<PercentageType>>,
				public boost::less_than_comparable<Percentage<PercentageType>, PercentageType>,
				public boost::equality_comparable<Percentage<PercentageType>, PercentageType>,
				public boost::integer_arithmetic<Percentage<PercentageType>, PercentageType>
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

			template<typename perc1, typename perc2>
			bool operator == (const Percentage<perc1> &, const Percentage<perc2> &);

			template<typename perc1, typename perc2>
			bool operator != (const Percentage<perc1> &, const Percentage<perc2> &);
		}
	}

#	include "Percentage.impl.hh"

#endif
