/*	Michael Thomas (malinka) <AelMalinka@gmail.com>
	2012-12-15
*/

#if !defined ENTROPY_HECATE_STAT_INC
#	define ENTROPY_HECATE_STAT_INC

#	include <string>
#	include <boost/flyweight.hpp>
#	include <boost/flyweight/key_value.hpp>
#	include <boost/flyweight/no_tracking.hpp>

#	include "Percentage.hh"

	namespace Entropy 
	{
		namespace Hecate
		{
			class StatPrototype;

			template<typename T = StatPrototype>
			class Stat :
				public boost::flyweight<
					boost::flyweights::key_value<
						std::string,
						T,
						typename T::extractor
					>,
					boost::flyweights::no_tracking
				>,
				public Percentage
			{
				public:
					Stat();
					explicit Stat(const std::string &);
					Stat(const std::string &, const unsigned short);
					Stat<T> &operator = (const unsigned short);
					virtual ~Stat();
				protected:
					typedef typename T::extractor extractor;
					typedef boost::flyweights::key_value<std::string, T, extractor> holder;
					typedef boost::flyweight<holder, boost::flyweights::no_tracking> container;
			};

			class StatPrototype
			{
				public:
					StatPrototype();
					StatPrototype(const std::string &);
					virtual ~StatPrototype();
					bool operator == (const std::string &) const;
					struct extractor {	// 2012-12-19 AMR TODO: explore gcc failing to friend
						const std::string &operator () (const StatPrototype &) const;
					};
				private:
					std::string _name;
			};
		}
	}

	namespace Entropy
	{
		namespace Hecate
		{
			template<typename T>
			Stat<T>::Stat()
				: container(), Percentage()
			{}

			template<typename T>
			Stat<T>::Stat(const std::string &n)
				: container(n), Percentage()
			{}

			template<typename T>
			Stat<T>::Stat(const std::string &n, const unsigned short v)
				: container(n), Percentage(v)
			{}

			template<typename T>
			Stat<T>::~Stat() = default;

			template<typename T>
			Stat<T> &Stat<T>::operator = (const unsigned short o)
			{
				Percentage::operator = (o);
				return *this;
			}
		}
	}

#endif
