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
				boost::less_than_comparable<Percentage, short>,
				boost::equality_comparable<Percentage, short>,
				boost::integer_arithmetic<Percentage, short>
			{
				public:
					Percentage();
					Percentage(const Percentage &);
					Percentage(Percentage &&);
					Percentage(const short &);
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
					bool operator < (const short &) const;
					bool operator == (const short &) const;
					Percentage &operator +=(const short &);
					Percentage &operator -=(const short &);
					Percentage &operator *=(const short &);
					Percentage &operator /=(const short &);
					Percentage &operator %=(const short &);
				protected:
				private:
					short _val;
			};
		}
	}
#endif
