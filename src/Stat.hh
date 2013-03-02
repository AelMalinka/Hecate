/*	Copyright 2012 Michael Thomas (malinka) <malinka@entropy-development.com>
	Distributed under the terms of the GNU Lesser General Public License v3
	Stat
*/

#if !defined ENTROPY_HECATE_STAT_INC
#	define ENTROPY_HECATE_STAT_INC

#	include <boost/operators.hpp>

	namespace Entropy
	{
		namespace Hecate
		{
			template<
				typename stat_tag,
				typename PercentageType = unsigned short
			>
			class Stat :
				public boost::totally_ordered<Stat<stat_tag, PercentageType>>,
				public boost::integer_arithmetic<Stat<stat_tag, PercentageType>>,
				public boost::incrementable<Stat<stat_tag, PercentageType>>,
				public boost::decrementable<Stat<stat_tag, PercentageType>>,
				public boost::less_than_comparable<Stat<stat_tag, PercentageType>, PercentageType>,
				public boost::equality_comparable<Stat<stat_tag, PercentageType>, PercentageType>,
				public boost::integer_arithmetic<Stat<stat_tag, PercentageType>, PercentageType>
			{
				public:
					Stat();
					Stat(const Stat<stat_tag, PercentageType> &);
					Stat(Stat<stat_tag, PercentageType> &&);
					Stat(const PercentageType &);
					Stat(PercentageType &&);
					virtual ~Stat();
					Stat<stat_tag, PercentageType> &operator = (const Stat<stat_tag, PercentageType> &);
					Stat<stat_tag, PercentageType> &operator = (const PercentageType &);
					bool operator < (const Stat<stat_tag, PercentageType> &) const;
					template<typename tag1, typename perc1, typename perc2> friend bool operator == (const Stat<tag1, perc1> &, const Stat<tag1, perc2> &);
					Stat<stat_tag, PercentageType> &operator ++();
					Stat<stat_tag, PercentageType> &operator --();
					Stat<stat_tag, PercentageType> &operator +=(const Stat<stat_tag, PercentageType> &);
					Stat<stat_tag, PercentageType> &operator -=(const Stat<stat_tag, PercentageType> &);
					Stat<stat_tag, PercentageType> &operator *=(const Stat<stat_tag, PercentageType> &);
					Stat<stat_tag, PercentageType> &operator /=(const Stat<stat_tag, PercentageType> &);
					Stat<stat_tag, PercentageType> &operator %=(const Stat<stat_tag, PercentageType> &);
					bool operator < (const PercentageType &) const;
					bool operator == (const PercentageType &) const;
					Stat<stat_tag, PercentageType> &operator +=(const PercentageType &);
					Stat<stat_tag, PercentageType> &operator -=(const PercentageType &);
					Stat<stat_tag, PercentageType> &operator *=(const PercentageType &);
					Stat<stat_tag, PercentageType> &operator /=(const PercentageType &);
					Stat<stat_tag, PercentageType> &operator %=(const PercentageType &);
				protected:
				private:
					PercentageType _val;
			};

			template<typename tag1, typename tag2, typename perc1, typename perc2>
			bool operator == (const Stat<tag1, perc1> &, const Stat<tag2, perc2> &);
			
			template<typename tag1, typename tag2, typename perc1, typename perc2>
			bool operator != (const Stat<tag1, perc1> &, const Stat<tag2, perc2> &);
		}
	}

#	include "Stat.impl.hh"

#endif
