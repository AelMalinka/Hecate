/*	Michael Thomas (malinka) <AelMalinka@gmail.com>
	2012-12-14
*/

#if !defined ENTROPY_HECATE_PERCENTAGE_INC
#	define ENTROPY_HECATE_PERCENTAGE_INC

#	include <boost/operators.hpp>

	namespace Entropy
	{
		namespace Hecate
		{
			class Percentage :
				boost::totally_ordered<Percentage>,
				boost::integer_arithmetic<Percentage>,
				boost::incrementable<Percentage>,
				boost::decrementable<Percentage>,
				boost::less_than_comparable<Percentage, unsigned short>,
				boost::equality_comparable<Percentage, unsigned short>,
				boost::integer_arithmetic<Percentage, unsigned short>
			{
				public:
					Percentage();
					Percentage(const Percentage &);
					Percentage(Percentage &&);
					Percentage(const unsigned short &);
					virtual ~Percentage();
					Percentage &operator = (const Percentage &);
					bool operator < (const Percentage &) const;
					bool operator == (const Percentage &) const;
					Percentage &operator ++();
					Percentage &operator --();
					Percentage &operator +=(const Percentage &);
					Percentage &operator -=(const Percentage &);
					Percentage &operator *=(const Percentage &);
					Percentage &operator /=(const Percentage &);
					Percentage &operator %=(const Percentage &);
					bool operator < (const unsigned short &) const;
					bool operator == (const unsigned short &) const;
					Percentage &operator +=(const unsigned short &);
					Percentage &operator -=(const unsigned short &);
					Percentage &operator *=(const unsigned short &);
					Percentage &operator /=(const unsigned short &);
					Percentage &operator %=(const unsigned short &);
				protected:
				private:
					unsigned short _val;
			};
		}
	}
#endif
